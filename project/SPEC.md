
# ECE 361 Project 10 - Parking Garage Exit Gate

## 1. Project Description

This project is a parking garage exit gate system written in C.

When a driver pays for a ticket, the gate opens. The system uses a sensor to check if a car is passing. The gate does not close while a car is under it.

The system also checks temperature and humidity. In freezing rain, it refuses to open the gate for safety.

## 2. States

The system has five states:

- DOWN: The gate is closed.
- RAISING: The gate is opening.
- UP: The gate is open.
- LOWERING: The gate is closing.
- BLOCKED: The gate stops because a car is under it.

## 3. Events

The system responds to these events:

- TICKET_PAID: The driver pays for a ticket.
- CAR_DETECTED: A car is over the sensor loop.
- CAR_LEFT: The car leaves the sensor loop.
- RAISE_DONE: The gate finishes opening after 4 ticks.
- LOWER_DONE: The gate finishes closing after 4 ticks.
- WAIT_DONE: The gate waits 3 ticks after the car leaves.
- BLOCK_DONE: The gate waits 2 ticks after being blocked.

## 4. Operating Rules

- The gate starts in the DOWN state.
- A paid ticket starts opening the gate.
- Opening and closing each take 4 ticks.
- The gate waits 3 ticks after the car leaves before closing.
- If a car is detected while closing, the gate stops for 2 ticks and then opens again.
- If the temperature is 0.5 C or lower and humidity is 90% or higher, the gate refuses a paid ticket.

## 5. State Transition Table

| Current State | Event | Next State | Action |
|---|---|---|---|
| DOWN | TICKET_PAID | RAISING | Start motor up |
| RAISING | RAISE_DONE | UP | Stop motor up |
| UP | CAR_DETECTED | UP | Keep gate open |
| UP | CAR_LEFT | UP | Start 3-tick wait |
| UP | WAIT_DONE | LOWERING | Start motor down |
| LOWERING | CAR_DETECTED | BLOCKED | Stop motor |
| BLOCKED | BLOCK_DONE | RAISING | Start motor up |
| LOWERING | LOWER_DONE | DOWN | Stop motor |

If freezing rain is detected (temperature <= 0.5 C
and humidity >= 90%), the gate refuses a paid ticket
while DOWN.

For events not listed in the table, the gate stays
in its current state.

## 6. State Machine Diagram

```text
DOWN
  |
  | TICKET_PAID
  v
RAISING
  |
  | RAISE_DONE
  v
 UP <------------------- RAISING
  |                        ^
  | WAIT_DONE              |
  v                        |
LOWERING                   |
  |                        |
  | CAR_DETECTED           |
  v                        |
BLOCKED -------------------+
       BLOCK_DONE

LOWERING
  |
  | LOWER_DONE
  v
DOWN
```

## 7. Status Word

The status word is a 32-bit unsigned integer.

| Field | Bit Position | Width |
|---|---|---|
| State | 0 | 3 |
| MOTOR_UP | 3 | 1 |
| MOTOR_DOWN | 4 | 1 |
| GO | 5 | 1 |
| Car present | 6 | 1 |

Unused bits are set to 0.




