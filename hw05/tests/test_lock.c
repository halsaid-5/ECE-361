#include <stdio.h>
#include "lock.h"

static int passed = 0;
static int failed = 0;

// Print PASS or FAIL for each test.
void result(const char *name, int condition)
{
    if (condition) {
        printf("PASS: %s\n", name);
        passed++;
    } else {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

// Test one transition.
void check(state_t start, event_t event,
           state_t expected_state, action_t expected_action)
{
    action_t action = A_UNDEFINED;
    state_t next = lock_step(start, event, &action);

    char name[100];
    snprintf(name, sizeof(name), "%s + %s",
             state_name(start), event_name(event));

    result(name, next == expected_state &&
                 action == expected_action);
}

// Test character conversion.
void check_event(state_t state, char c, int expected)
{
    char name[100];
    snprintf(name, sizeof(name), "Event %s + %c",
             state_name(state), c);

    result(name, lock_event(state, c) == expected);
}

// Run a complete input sequence.
void check_sequence(const char *name, const char *input,
                    state_t expected_state, int expected_unlock)
{
    state_t state = LOCKED;
    action_t action = A_NONE;
    int unlocked = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        int event = lock_event(state, input[i]);

        if (event == -1)
            continue;

        state = lock_step(state, (event_t)event, &action);

        if (action == A_UNLOCK)
            unlocked = 1;
    }

    result(name, state == expected_state &&
                 unlocked == expected_unlock);
}

int main(void)
{
    // Test all 16 transitions.
    check(LOCKED, E_RIGHT, GOT1, A_NONE);
    check(LOCKED, E_WRONG, LOCKED, A_BEEP);
    check(LOCKED, E_CLOSE, LOCKED, A_NONE);
    check(LOCKED, E_TIMEOUT, LOCKED, A_NONE);

    check(GOT1, E_RIGHT, GOT2, A_NONE);
    check(GOT1, E_WRONG, LOCKED, A_BEEP);
    check(GOT1, E_CLOSE, GOT1, A_NONE);
    check(GOT1, E_TIMEOUT, LOCKED, A_NONE);

    check(GOT2, E_RIGHT, OPEN, A_UNLOCK);
    check(GOT2, E_WRONG, LOCKED, A_BEEP);
    check(GOT2, E_CLOSE, GOT2, A_NONE);
    check(GOT2, E_TIMEOUT, LOCKED, A_NONE);

    check(OPEN, E_RIGHT, OPEN, A_NONE);
    check(OPEN, E_WRONG, OPEN, A_NONE);
    check(OPEN, E_CLOSE, LOCKED, A_LOCK);
    check(OPEN, E_TIMEOUT, LOCKED, A_LOCK);

    // Test lock_event in each state.
    check_event(LOCKED, '3', E_RIGHT);
    check_event(LOCKED, '1', E_WRONG);

    check_event(GOT1, '1', E_RIGHT);
    check_event(GOT1, '3', E_WRONG);

    check_event(GOT2, '4', E_RIGHT);
    check_event(GOT2, '1', E_WRONG);

    check_event(OPEN, '3', E_WRONG);
    check_event(OPEN, '4', E_WRONG);

    // Test close and timeout.
    check_event(LOCKED, 'c', E_CLOSE);
    check_event(GOT1, 'c', E_CLOSE);
    check_event(GOT2, 't', E_TIMEOUT);
    check_event(OPEN, 't', E_TIMEOUT);

    // Test invalid characters.
    check_event(LOCKED, 'x', -1);
    check_event(GOT1, '!', -1);
    check_event(OPEN, 'x', -1);

    // Test complete sequences.
    check_sequence("314 opens", "314", OPEN, 1);
    check_sequence("3314 does not open", "3314", LOCKED, 0);
    check_sequence("31t4 does not open", "31t4", LOCKED, 0);
    check_sequence("314c locks again", "314c", LOCKED, 1);

    // Print summary.
    printf("\nPassed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}
