#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include "lock.h"

// Check the FSM table and return the number of problems.
int fsm_check(
    const transition_t table[N_STATES][N_EVENTS],
    state_t start,
    FILE *out
);

#endif
