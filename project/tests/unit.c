#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fsm.h"
#include "store.h"
#include "aux.h"
#include "sensor.h"
#include "report.h"
#include "status.h"
#include "iom361_r4.h"
static int passed=0,failed=0;
#define CHECK(x) do{if(x)passed++;else{failed++;fprintf(stderr,"FAIL %s:%d: %s\n",__FILE__,__LINE__,#x);}}while(0)
static record_t rec(float temp,int t,state_t state){record_t r={0};r.reading.temp_c=temp;r.reading.timestamp=t;r.state=state;return r;}
static void visit(const record_t *r,void *p){int *n=p;(*n)++;(void)r;}
int main(void){
 CHECK(fsm_next_state(DOWN,TICKET_PAID)==RAISING);
 CHECK(fsm_next_state(RAISING,RAISE_DONE)==UP);
 CHECK(fsm_next_state(UP,WAIT_DONE)==LOWERING);
 CHECK(fsm_next_state(LOWERING,CAR_DETECTED)==BLOCKED);
 CHECK(fsm_next_state(BLOCKED,BLOCK_DONE)==RAISING);
 CHECK(fsm_leds(RAISING)==1&&fsm_leds(LOWERING)==2&&fsm_leds(UP)==4);
 record_t a=rec(21.2f,0,DOWN),b=rec(21.1f,1,DOWN),c=rec(21.4f,2,DOWN),d=rec(21.5f,3,DOWN);
 CHECK(record_compare(&a,&b)==0);CHECK(record_compare(&a,&c)<0);CHECK(record_compare(&c,&d)==0);CHECK(record_compare(&a,&d)<0);
 store_t *s=store_create();CHECK(s!=NULL);CHECK(store_count(s)==0&&store_height(s)==0);
 CHECK(store_insert(s,a)==0);CHECK(store_count(s)==1&&store_height(s)==1);
 CHECK(store_insert(s,b)==0);CHECK(store_count(s)==2&&store_height(s)==1);
 CHECK(store_insert(s,c)==0);CHECK(store_insert(s,d)==0);
 CHECK(store_find(s,21.0f)!=NULL);CHECK(store_find(s,35.0f)==NULL);
 int n=0;store_walk(s,visit,&n);CHECK(n==4);
 report_t report;report_calculate(s,&report);CHECK(report.total==4&&report.ticks[DOWN]==4&&report.ticks[UP]==0);
 store_destroy(s);s=store_create();report_calculate(s,&report);CHECK(report.total==0);store_destroy(s);
 s=store_create();for(int i=0;i<100;i++)CHECK(store_insert(s,rec((float)i,100-i,DOWN))==0);
 CHECK(store_count(s)==100&&store_height(s)>1);store_destroy(s);
 aux_t *stack=aux_create();history_event_t e={0};CHECK(aux_pop(stack,&e)!=0);CHECK(aux_peek(stack,&e)!=0);
 for(int i=0;i<20;i++){e.tick=i;CHECK(aux_push(stack,e)==0);}CHECK(aux_count(stack)==20);
 for(int i=19;i>=0;i--){CHECK(aux_pop(stack,&e)==0&&e.tick==i);}CHECK(aux_is_empty(stack));aux_destroy(stack);
 uint32_t w=status_pack(BLOCKED,7,1),leds=0;state_t state=DOWN;int car=0;
 status_unpack(w,&state,&leds,&car);CHECK(state==BLOCKED&&leds==7&&car==1&&!(w&~127u));
 int rc=0;uint32_t *base=iom361_initialize(2,3,&rc);iom361_set_display(false);CHECK(base&&rc==0);
 reading_t r;_iom361_set_sensor1(0,90);CHECK(sensor_read(base,0,&r)==0&&fabsf(r.temp_c)<0.01f&&r.rh_pct==90.0f);
 _iom361_set_sensor1(100,75);CHECK(sensor_read(base,1,&r)==0&&r.temp_c==100.0f);
 _iom361_set_sensor1(0.5f,90);CHECK(sensor_read(base,2,&r)==0&&r.temp_c==0.5f);
 CHECK(sensor_read(NULL,0,&r)!=0);
 printf("Unit tests: %d passed, %d failed\n",passed,failed);
 return failed?1:0;
}
