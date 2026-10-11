
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
