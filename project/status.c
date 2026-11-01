#include "status.h"
#include "../hw01/bits.h"
uint32_t status_pack(state_t s,uint32_t leds,int car){uint32_t w=0;w=set_field(w,0,3,(uint32_t)s);w=set_field(w,3,1,leds&1u);w=set_field(w,4,1,(leds>>1)&1u);w=set_field(w,5,1,(leds>>2)&1u);w=set_field(w,6,1,car?1u:0u);return w;}
void status_unpack(uint32_t w,state_t *s,uint32_t *leds,int *car){if(s)*s=(state_t)get_field(w,0,3);if(leds)*leds=get_field(w,3,1)|(get_field(w,4,1)<<1)|(get_field(w,5,1)<<2);if(car)*car=(int)get_field(w,6,1);}
