#ifndef FSM_H
#define FSM_H

// Parking gate states.
typedef enum {
    DOWN,
    RAISING,
    UP,
    LOWERING,
    BLOCKED
} state_t;

typedef enum {
    TICKET_PAID,
    CAR_DETECTED,
    CAR_LEFT,
    RAISE_DONE,
    LOWER_DONE,
    WAIT_DONE,
    BLOCK_DONE
} event_t;
// Actions for the parking gate.
typedef enum {
    MOTOR_OFF,
    MOTOR_UP,
    MOTOR_DOWN
} action_t;

// One FSM transition.
typedef struct {
    state_t next;
    action_t action;
} transition_t;

state_t fsm_next_state(state_t current, event_t event);
void fsm_print_action(state_t state);
#endif
