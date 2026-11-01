#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "iom361_r4.h"
#include "sensor.h"
#include "fsm.h"
#include "store.h"
#include "aux.h"
#include "report.h"
#include "status.h"

typedef struct {long tick;float temp,humidity;unsigned switches;} change_t;
typedef struct {time_t start;change_t *changes;size_t count;} scenario_t;

static void scenario_free(scenario_t *s){free(s->changes);s->changes=NULL;}
static int scenario_load(const char *path,scenario_t *s){
    memset(s,0,sizeof(*s));FILE *f=fopen(path,"r");if(!f){perror(path);return -1;}
    char line[256];int have_start=0;long last=-1;
    while(fgets(line,sizeof(line),f)){
        char *comment=strchr(line,'#');if(comment)*comment='\0';
        char *p=line;while(*p==' '||*p=='\t')p++;if(!*p||*p=='\n')continue;
        if(!have_start){long long start;char extra;if(sscanf(p,"start %lld %c",&start,&extra)!=1){fprintf(stderr,"Invalid start line\n");goto bad;}s->start=(time_t)start;have_start=1;continue;}
        change_t c;char extra;int read=sscanf(p,"%ld %f %f %x %c",&c.tick,&c.temp,&c.humidity,&c.switches,&extra);
        if(read!=4||c.tick<=last||c.tick<0||c.switches>3u||c.temp< -50||c.temp>150||c.humidity<0||c.humidity>100){fprintf(stderr,"Invalid scenario row: %s\n",p);goto bad;}
        change_t *next=realloc(s->changes,(s->count+1)*sizeof(*next));if(!next)goto bad;
        s->changes=next;s->changes[s->count++]=c;last=c.tick;
    }
    fclose(f);
    if(!have_start||s->count==0||s->changes[0].tick!=0){fprintf(stderr,"Scenario needs start and tick 0\n");scenario_free(s);return -1;}
    return 0;
bad:fclose(f);scenario_free(s);return -1;
}
static int log_event(aux_t *history,long tick,const char *name){history_event_t e={0};e.tick=tick;snprintf(e.name,sizeof(e.name),"%s",name);return aux_push(history,e);}
static void print_recent(aux_t *history){history_event_t e;puts("Last events (newest first):");for(int i=0;i<5&&aux_pop(history,&e)==0;i++)printf("tick %ld: %s\n",e.tick,e.name);}
static void format_time(time_t t,char *buffer,size_t size){struct tm *utc=gmtime(&t);if(!utc||!strftime(buffer,size,"%Y-%m-%d %H:%M:%S",utc))snprintf(buffer,size,"INVALID_TIME");}
static int write_outputs(uint32_t *base,state_t state){int rc=0;iom361_writeReg(base,LEDS_REG,fsm_leds(state),&rc);if(rc)return -1;iom361_writeReg(base,RGB_LED_REG,fsm_rgb(state),&rc);return rc? -1:0;}
int main(int argc,char **argv){
    if(argc<2||argc>3||(argc==3&&strcmp(argv[2],"--report")!=0)){fprintf(stderr,"Usage: %s scenario.txt [--report]\n",argv[0]);return 1;}
    int report_only=argc==3;scenario_t scenario;if(scenario_load(argv[1],&scenario))return 1;
    int rc=0;uint32_t *base=iom361_initialize(2,3,&rc);if(!base||rc){scenario_free(&scenario);fprintf(stderr,"Hardware initialization failed\n");return 1;}
    iom361_set_display(false);
    store_t *store=store_create();aux_t *history=aux_create();if(!store||!history){fprintf(stderr,"Out of memory\n");store_destroy(store);aux_destroy(history);scenario_free(&scenario);return 1;}
    state_t state=DOWN;long state_since=0,car_left_at=-1;int seen_car=0;
    unsigned previous=0;size_t change_index=0;change_t input=scenario.changes[0];
    long final_tick=scenario.changes[scenario.count-1].tick;
    for(long tick=0;tick<=final_tick;tick++){
        if(change_index+1<scenario.count&&scenario.changes[change_index+1].tick==tick){change_index++;input=scenario.changes[change_index];}
        _iom361_set_sensor1(input.temp,input.humidity);_iom361_set_switches(input.switches);
        reading_t reading;if(sensor_read(base,scenario.start+(time_t)tick,&reading)){fprintf(stderr,"Sensor read failed\n");goto fail;}
        unsigned switches=iom361_readReg(base,SWITCHES_REG,&rc);if(rc){fprintf(stderr,"Switch read failed\n");goto fail;}
        int car=(switches&2u)!=0,old_car=(previous&2u)!=0;
        int paid=(switches&1u)&&!(previous&1u);
        int icy=reading.temp_c<=0.5f&&reading.rh_pct>=90.0f;
        if(paid){if(icy||state!=DOWN){if(log_event(history,tick,"TICKET_REFUSED"))goto fail;}else{if(log_event(history,tick,"TICKET_PAID"))goto fail;state=fsm_next_state(state,TICKET_PAID);state_since=tick;seen_car=0;car_left_at=-1;}}
        if(car&&!old_car){if(log_event(history,tick,"CAR_DETECTED"))goto fail;if(state==LOWERING){state=fsm_next_state(state,CAR_DETECTED);state_since=tick;car_left_at=-1;if(log_event(history,tick,"BLOCKED"))goto fail;}if(state==UP)seen_car=1;}
        if(!car&&old_car){if(log_event(history,tick,"CAR_LEFT"))goto fail;if(state==UP&&seen_car)car_left_at=tick;}
        /* Timing starts at the tick when the state is entered. */
        if(state==RAISING&&tick-state_since>=4){state=fsm_next_state(state,RAISE_DONE);state_since=tick;if(car)seen_car=1;}
        else if(state==LOWERING&&tick-state_since>=4){state=fsm_next_state(state,LOWER_DONE);state_since=tick;}
        else if(state==BLOCKED&&tick-state_since>=2){state=fsm_next_state(state,BLOCK_DONE);state_since=tick;seen_car=car;car_left_at=-1;}
        else if(state==UP&&car_left_at>=0&&tick-car_left_at>=3&&!car){state=fsm_next_state(state,WAIT_DONE);state_since=tick;car_left_at=-1;}
        /* If the car is already on the loop when lowering starts, stop. */
        if(state==LOWERING&&car){state=fsm_next_state(state,CAR_DETECTED);state_since=tick;if(log_event(history,tick,"BLOCKED"))goto fail;}
        if(write_outputs(base,state)){fprintf(stderr,"LED write failed\n");goto fail;}
        uint32_t leds=fsm_leds(state),status=status_pack(state,leds,car);
        record_t record={reading,state,status};if(store_insert(store,record)){fprintf(stderr,"Store insert failed\n");goto fail;}
        if(!report_only){char date[32];format_time(reading.timestamp,date,sizeof(date));printf("%s state=%s temp=%.1f rh=%.1f leds=0x%X status=0x%08X\n",date,fsm_state_name(state),reading.temp_c,reading.rh_pct,leds,status);}
        previous=switches;
    }
    if(report_only){report_t report;report_calculate(store,&report);report_print(stdout,&report);}else print_recent(history);
    aux_destroy(history);store_destroy(store);scenario_free(&scenario);return 0;
fail:aux_destroy(history);store_destroy(store);scenario_free(&scenario);return 1;
}
