#ifndef FSM_H
#define FSM_H
#include <stdint.h>
typedef enum {DOWN,RAISING,UP,LOWERING,BLOCKED,STATE_COUNT} state_t;
typedef enum {TICKET_PAID,CAR_DETECTED,CAR_LEFT,RAISE_DONE,LOWER_DONE,WAIT_DONE,BLOCK_DONE,EVENT_COUNT} event_t;
typedef enum {MOTOR_OFF,MOTOR_UP,MOTOR_DOWN} action_t;
typedef struct {state_t next; action_t action;} transition_t;
state_t fsm_next_state(state_t current,event_t event);
transition_t fsm_transition(state_t current,event_t event);
const char *fsm_state_name(state_t state);
uint32_t fsm_leds(state_t state);
uint32_t fsm_rgb(state_t state);
#endif
