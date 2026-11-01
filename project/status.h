#ifndef STATUS_H
#define STATUS_H
#include <stdint.h>
#include "fsm.h"
uint32_t status_pack(state_t state,uint32_t leds,int car);
void status_unpack(uint32_t word,state_t *state,uint32_t *leds,int *car);
#endif
