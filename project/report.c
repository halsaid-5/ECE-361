#include "report.h"
#include <stdlib.h>
#include <string.h>
typedef struct {record_t *items;size_t used,cap;} records_t;
static void collect(const record_t *r,void *ctx){records_t *v=ctx;if(v->used==v->cap){size_t next=v->cap?v->cap*2:32;record_t *p=realloc(v->items,next*sizeof(*p));if(!p)return;v->items=p;v->cap=next;}v->items[v->used++]=*r;}
static int by_time(const void *a,const void *b){const record_t *x=a,*y=b;return (x->reading.timestamp>y->reading.timestamp)-(x->reading.timestamp<y->reading.timestamp);}
void report_calculate(const store_t *s,report_t *out){if(!out)return;memset(out,0,sizeof(*out));records_t v={0};store_walk(s,collect,&v);qsort(v.items,v.used,sizeof(record_t),by_time);for(size_t i=0;i<v.used;i++){/* Each sample represents one tick, including the last sample. */state_t state=v.items[i].state;if(state>=DOWN&&state<STATE_COUNT){out->ticks[state]++;out->total++;}}free(v.items);}
void report_print(FILE *out,const report_t *r){if(!out||!r)return;fprintf(out,"State report: %ld ticks\n",r->total);for(int s=DOWN;s<STATE_COUNT;s++){double pct=r->total?100.0*r->ticks[s]/r->total:0.0;fprintf(out,"%s: %ld ticks (%.1f%%)\n",fsm_state_name((state_t)s),r->ticks[s],pct);}}
