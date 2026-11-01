#include "fsm.h"
#include "iom361_r4.h"
/* Each cell is {next state, motor action}. The motor action is
   the action of the next state, so it stays on during motion. */
#define D {DOWN,MOTOR_OFF}
#define R {RAISING,MOTOR_UP}
#define U {UP,MOTOR_OFF}
#define L {LOWERING,MOTOR_DOWN}
#define B {BLOCKED,MOTOR_OFF}
static const transition_t table[STATE_COUNT][EVENT_COUNT]={
    {R,D,D,D,D,D,D},
    {R,R,R,U,R,R,R},
    {U,U,U,U,U,L,U},
    {L,B,L,L,D,L,L},
    {B,B,B,B,B,B,R}
};
transition_t fsm_transition(state_t s,event_t e){transition_t unchanged={s,MOTOR_OFF};if(s<DOWN||s>=STATE_COUNT)return unchanged;if(e<0||e>=EVENT_COUNT){unchanged.action=s==RAISING?MOTOR_UP:(s==LOWERING?MOTOR_DOWN:MOTOR_OFF);return unchanged;}return table[s][e];}
state_t fsm_next_state(state_t s,event_t e){return fsm_transition(s,e).next;}
const char *fsm_state_name(state_t s){static const char *names[]={"DOWN","RAISING","UP","LOWERING","BLOCKED"};return s>=DOWN&&s<STATE_COUNT?names[s]:"UNKNOWN";}
uint32_t fsm_leds(state_t s){if(s==RAISING)return 1u;if(s==LOWERING)return 2u;if(s==UP)return 4u;return 0u;}
uint32_t fsm_rgb(state_t s){switch(s){case DOWN:return build_rgb_reg(1,255,0,0);case RAISING:return build_rgb_reg(1,255,165,0);case UP:return build_rgb_reg(1,0,255,0);case LOWERING:return build_rgb_reg(1,0,0,255);case BLOCKED:return build_rgb_reg(1,255,0,255);default:return 0;}}
