# HW05 - Combination Lock FSM

## Description
This program simulates a combination lock using a Finite State Machine (FSM). The correct code is 314.

A correct digit moves to the next state. A wrong digit resets the lock and makes a beep. The door locks again when it closes or the timer expires.

## How to Build and Run

Open the terminal in the `hw05` folder.

Build the program:

```text
make
```

Run the program:

```text
printf "314c" | ./lock
```

Run the tests:

```text
make test
```

Clean the compiled files:

```text
make clean
```

## States
- LOCKED: The door is locked.
- GOT1: The first digit is correct.
- GOT2: The second digit is correct.
- OPEN: The door is unlocked.

## State Diagram

```text
LOCKED --3--> GOT1 --1--> GOT2 --4--> OPEN
  ^             |            |           |
  |             |            |           |
  +-- wrong ----+-- wrong ---+           |
  |                                      |
  +------------- c or t ----------------+
```

A wrong digit returns to LOCKED with BEEP. A timeout while entering the code returns to LOCKED silently.

## Transition Table

| State | RIGHT | WRONG | CLOSE | TIMEOUT |
|---|---|---|---|---|
| LOCKED | GOT1, NONE | LOCKED, BEEP | LOCKED, NONE | LOCKED, NONE |
| GOT1 | GOT2, NONE | LOCKED, BEEP | GOT1, NONE | LOCKED, NONE |
| GOT2 | OPEN, UNLOCK | LOCKED, BEEP | GOT2, NONE | LOCKED, NONE |
| OPEN | OPEN, NONE | OPEN, NONE | LOCKED, LOCK | LOCKED, LOCK |

## Testing

The tests check correct digits, wrong digits, closing the door, timeouts, and state transitions.

All 35 regular tests passed with 0 failures. The 4 bonus tests also passed with 0 failures.

**Total: 39 tests passed, 0 failed.**

## Bonus – FSM Checker

The bonus adds an FSM checker using `check.c` and `check.h`.

The checker looks for:
- Missing entries in the transition table.
- Invalid next states.
- Unreachable states.
- States with no way out.

The bonus tests are in `tests/test_check.c`.

To run all tests:

```text
make test
```
**Bonus Results:**
- Passed: 4
- Failed: 0