#include <stdio.h>
#include "fsm.h"

// Transition table indexed by state and event.
static const state_t transitions[5][7] = {
    // DOWN
    {RAISING, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN},

    // RAISING
    {RAISING, RAISING, RAISING, UP, RAISING, RAISING, RAISING},

    // UP
    {UP, UP, UP, UP, UP, LOWERING, UP},

    // LOWERING
    {LOWERING, BLOCKED, LOWERING, LOWERING, DOWN, LOWERING, LOWERING},

    // BLOCKED
    {BLOCKED, BLOCKED, BLOCKED, BLOCKED, BLOCKED, BLOCKED, RAISING}
};

// Return the next state.
state_t fsm_next_state(state_t current, event_t event)
{
    if (current < DOWN || current > BLOCKED ||
        event < TICKET_PAID || event > BLOCK_DONE) {
        return current;
    }

    return transitions[current][event];
}
// Print the motor action for each state.
void fsm_print_action(state_t state)
{
    if (state == RAISING) {
        printf("Motor: UP\n");
    }
    else if (state == LOWERING) {
        printf("Motor: DOWN\n");
    }
    else {
        printf("Motor: OFF\n");
    }
}
