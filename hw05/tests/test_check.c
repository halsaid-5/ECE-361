#include <stdio.h>
#include "check.h"

static int passed = 0;
static int failed = 0;

void test_table(const char *name,
                transition_t table[N_STATES][N_EVENTS],
                int expected)
{
    printf("\n%s:\n", name);

    int problems = fsm_check(table, LOCKED, stdout);

    if (problems == expected) {
        printf("PASS: Found %d problems\n", problems);
        passed++;
    } else {
        printf("FAIL: Expected %d, found %d\n",
               expected, problems);
        failed++;
    }
}

int main(void)
{
    transition_t table[N_STATES][N_EVENTS];

    // Test 1: Correct table
    for (int s = 0; s < N_STATES; s++) {
        for (int e = 0; e < N_EVENTS; e++) {
            table[s][e] = lock_table[s][e];
        }
    }
    test_table("Correct table", table, 0);

    // Test 2: Missing entry
    table[LOCKED][E_RIGHT].action = A_UNDEFINED;
    test_table("Missing entry", table, 5);

    // Restore the table
    table[LOCKED][E_RIGHT] = lock_table[LOCKED][E_RIGHT];

    // Test 3: Invalid next state
    table[GOT1][E_RIGHT].next = N_STATES;
    test_table("Invalid next state", table, 3);

    // Restore the table
    table[GOT1][E_RIGHT] = lock_table[GOT1][E_RIGHT];

    // Test 4: No way out
    for (int e = 0; e < N_EVENTS; e++) {
        table[GOT2][e].next = GOT2;
    }
    test_table("No way out", table, 2);

    printf("\nPassed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}
