#include "check.h"

// Check the FSM transition table.
int fsm_check(const transition_t table[N_STATES][N_EVENTS],
              state_t start, FILE *out)
{
    int problems = 0;
    int visited[N_STATES] = {0};
    int queue[N_STATES];
    int front = 0;
    int back = 0;

    // Check missing entries and invalid next states.
    for (int s = 0; s < N_STATES; s++) {
        for (int e = 0; e < N_EVENTS; e++) {
            transition_t t = table[s][e];

            if (t.action == A_UNDEFINED) {
                fprintf(out, "Missing entry: %d, %d\n", s, e);
                problems++;
            }

            if (t.next < 0 || t.next >= N_STATES) {
                fprintf(out, "Invalid next state: %d, %d\n", s, e);
                problems++;
            }
        }
    }

    // Find reachable states using breadth-first search.
    if (start < 0 || start >= N_STATES) {
        fprintf(out, "Invalid start state\n");
        return problems + 1;
    }

    visited[start] = 1;
    queue[back++] = start;

    while (front < back) {
        int s = queue[front++];

        for (int e = 0; e < N_EVENTS; e++) {
            transition_t t = table[s][e];
            int next = t.next;

            if (t.action != A_UNDEFINED &&
                next >= 0 && next < N_STATES &&
                !visited[next]) {
                visited[next] = 1;
                queue[back++] = next;
            }
        }
    }

    // Check unreachable states.
    for (int s = 0; s < N_STATES; s++) {
        if (!visited[s]) {
            fprintf(out, "Unreachable state: %d\n", s);
            problems++;
        }
    }

       // Check states with no way out.
    for (int s = 0; s < N_STATES; s++) {
        int has_exit = 0;

        for (int e = 0; e < N_EVENTS; e++) {
            transition_t t = table[s][e];

            if (t.action != A_UNDEFINED &&
                t.next >= 0 && t.next < N_STATES &&
                (int)t.next != s) {
                has_exit = 1;
            }
        }

        if (!has_exit) {
            fprintf(out, "No way out of state: %d\n", s);
            problems++;
        }
    }

    return problems;
}