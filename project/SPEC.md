# Project 10 - Parking gate design

## Goal
A paid ticket opens the exit gate. A car loop tells us when a car passes. The gate stops if a car is under it during closing. Freezing rain blocks a new ticket.

## States and events
- DOWN: gate closed; RAISING: motor goes up; UP: gate open; LOWERING: motor goes down; BLOCKED: stopped after a car is detected while lowering.
- Events: TICKET_PAID, CAR_DETECTED, CAR_LEFT, RAISE_DONE, LOWER_DONE, WAIT_DONE, BLOCK_DONE.
- Action in the table means the motor action **after** the transition: OFF, UP, DOWN.

| Current | Event | Next | Action |
|---|---|---|---|
| DOWN | TICKET_PAID | RAISING | UP |
| RAISING | RAISE_DONE | UP | OFF |
| UP | WAIT_DONE | LOWERING | DOWN |
| LOWERING | CAR_DETECTED | BLOCKED | OFF |
| LOWERING | LOWER_DONE | DOWN | OFF |
| BLOCKED | BLOCK_DONE | RAISING | UP |

All other combinations keep the current state and its motor action. The full table is in `fsm.c`.

## State drawing
```
DOWN --ticket--> RAISING --4 ticks--> UP
 ^                                |   |
 |                                |   +-- car leaves, 3 ticks --> LOWERING
 +------------ 4 ticks -----------+                              |      |
                                                               car     4 ticks
                                                                |        |
                                                                v        v
                                                              BLOCKED   DOWN
                                                                |
                                                              2 ticks
                                                                |
                                                                +--> RAISING
```

## Decisions where the rules were silent
- A ticket is counted only when switch 0 changes from 0 to 1. A second ticket while the gate is not DOWN is refused and recorded.
- CAR_LOOP on while DOWN does not open the gate.
- The gate stays UP until a car has been seen and then leaves. This prevents closing before a car passes.
- If CAR_LOOP is already on when the arm starts lowering, it enters BLOCKED immediately.
- A new ticket is refused if temperature <= 0.5 C **and** humidity >= 90% RH. The boundary values count as freezing rain.
- Freezing rain while the gate is already moving or UP does not interrupt that cycle; stopping midway could trap a car. New tickets are refused while unsafe. This is a design choice, not a given rule.
- After BLOCKED lasts 2 ticks, the gate raises again. If the car is still present when UP is reached, the controller waits for it to leave.
- Each scenario row takes effect at its tick; values hold until the next row. The last row is included.
- The last 5 event history entries are printed only in trace mode. `--report` prints only the report.

## Data structures
`record_t` contains a `reading_t` (UTC timestamp, temperature, humidity), the current state, and a packed 32-bit status word.

The store is a binary search tree. The temperature key is `lroundf(temp_c * 2)`, meaning nearest 0.5 C. For example, 21.2 is 21.0, and 21.4 is 21.5. Duplicate keys are stored in a linked list attached to that tree node, preserving all records. The in-order walk visits keys from low to high. Count includes duplicates; height counts tree nodes, not duplicate-list entries. In the worst case, a plain BST can have height n.

The event history is a stack backed by a dynamic array. It starts with space for 8 events and doubles its capacity (8, 16, 32, ...). `push` and `pop` are O(1) on average, with an occasional O(n) resize. A linked-list stack is another choice: push/pop are O(1), but each push allocates a node and needs an extra pointer. The array uses less memory per event and is simpler here.

## Report definition
The report counts one tick for every stored sample, including the final sample. The records are read only through `store_walk`, then sorted by timestamp because the tree is ordered by temperature, not time. The five states appear in enum order, even if the count is zero. Percentage = 100 * state ticks / total ticks. An empty run has 0.0% for each state.

## Status bits
- 0-2: state (3 bits)
- 3: MOTOR_UP
- 4: MOTOR_DOWN
- 5: GO
- 6: car present
- 7-31: unused and zero

The project calls HW1 `get_field` and `set_field` for packing and unpacking.

## RGB colors
DOWN = red; RAISING = orange; UP = green; LOWERING = blue; BLOCKED = magenta.

## Events and software layout
`main.c` detects switch edges and timer events. This keeps the scenario replay, timing, and event history in one place. `fsm.c` holds only the transition table and LED/RGB mapping. `sensor.c` only reads and converts registers. The `iom361_r4` files are unchanged.

## The 2038 problem
If `time_t` is a signed 32-bit integer, it overflows on 19 January 2038 at 03:14:08 UTC. The device could show a wrong date and calculate wrong durations. A 64-bit `time_t` avoids this for practical use.

## Are the five states useful?
The five states are easy to understand and test. BLOCKED is important because it makes the stopped motor different from ordinary lowering. One weakness is that the states alone do not remember whether a car has already passed; the program needs `seen_car` and `car_left_at` as extra variables.
