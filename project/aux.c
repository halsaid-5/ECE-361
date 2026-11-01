#include "aux.h"
#include <stdlib.h>
struct aux {history_event_t *items;size_t count,capacity;};
aux_t *aux_create(void){aux_t *s=calloc(1,sizeof(*s));if(!s)return NULL;s->capacity=8;s->items=malloc(s->capacity*sizeof(*s->items));if(!s->items){free(s);return NULL;}return s;}
int aux_push(aux_t *s,history_event_t e){if(!s)return -1;if(s->count==s->capacity){size_t newcap=s->capacity*2;history_event_t *p=realloc(s->items,newcap*sizeof(*p));if(!p)return -1;s->items=p;s->capacity=newcap;}s->items[s->count++]=e;return 0;}
int aux_pop(aux_t *s,history_event_t *e){if(!s||!s->count)return -1;if(e)*e=s->items[s->count-1];s->count--;return 0;}
int aux_peek(const aux_t *s,history_event_t *e){if(!s||!s->count||!e)return -1;*e=s->items[s->count-1];return 0;}
size_t aux_count(const aux_t *s){return s?s->count:0;}
int aux_is_empty(const aux_t *s){return aux_count(s)==0;}
void aux_destroy(aux_t *s){if(s){free(s->items);free(s);}}
