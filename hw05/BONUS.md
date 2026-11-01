# Bonus – FSM Checker

## Description
I created an FSM checker using `check.c` and `check.h`. It checks the transition table for missing entries, invalid next states, unreachable states, and states with no way out.

## Results

**Test 1: Missing Entry**
- Problems found: 5
- A missing entry can stop the lock from responding correctly. It also makes some states unreachable.

**Test 2: Invalid Next State**
- Problems found: 3
- An invalid next state can make the lock enter a state that does not exist.

**Test 3: No Way Out**
- Problems found: 2
- A state with no way out can cause the lock to get stuck.

## Testing
All 4 bonus tests passed with 0 failures.