#include "aux.h"

// Returns how long each action takes.
int aux_get_ticks(int action)
{
    if (action == 1) {
        return 4; // Opening
    }

    if (action == 2) {
        return 4; // Closing
    }

    if (action == 3) {
        return 3; // Waiting after car leaves
    }

    if (action == 4) {
        return 2; // Blocked
    }

    return 0;
}
