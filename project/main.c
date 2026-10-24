#include <stdio.h>
#include "iom361_r4.h"
#include "fsm.h"
#include "aux.h"
#include "sensor.h"
#include <time.h>
#include "../hw01/bits.h"

int main(void)
{
    int rc;

    uint32_t *base = iom361_initialize(2, 3, &rc);

    if (base == NULL || rc != 0) {
        printf("Initialization failed.\n");
        return 1;
    }
    // Test freezing rain conditions.
_iom361_set_sensor1(23.5f, 75.0f);

    printf("Parking Garage Exit Gate\n");

    // Gate starts closed.
    state_t state = DOWN;
    printf("Initial state: DOWN\n");


    // Read temperature and humidity.
    reading_t reading;

    if (sensor_read(base, time(NULL), &reading) != 0) {
        printf("Sensor reading failed.\n");
        return 1;
    }

    printf("Temperature: %.2f C\n", reading.temp_c);
    printf("Humidity: %.2f%%\n", reading.rh_pct);

    // Check for freezing rain.
    if (reading.temp_c <= 0.5f && reading.rh_pct >= 90.0f) {
        printf("Freezing rain detected. Gate stays DOWN.\n");
        return 0;
    }


    // Driver pays for a ticket.
    state = fsm_next_state(state, TICKET_PAID);
    fsm_print_action(state);
    printf("After payment: RAISING (state = %d)\n", state);

    // Gate takes 4 ticks to open.
    int ticks = aux_get_ticks(1);

    for (int i = 1; i <= ticks; i++) {
        printf("Opening tick %d\n", i);
    }

    // Gate finishes opening.
    state = fsm_next_state(state, RAISE_DONE);
    printf("After opening: UP (state = %d)\n", state);
    // Car is detected under the gate.
    state = fsm_next_state(state, CAR_DETECTED);
    printf("Car detected: UP (state = %d)\n", state);

    // Car leaves the gate.
    state = fsm_next_state(state, CAR_LEFT);
    printf("Car left: UP (state = %d)\n", state);

    // Wait 3 ticks before closing.
    ticks = aux_get_ticks(3);

    for (int i = 1; i <= ticks; i++) {
        printf("Waiting tick %d\n", i);
    }

    // Gate starts closing.
    state = fsm_next_state(state, WAIT_DONE);
    fsm_print_action(state);
    printf("After waiting: LOWERING (state = %d)\n", state);
        // Car detected while gate is closing.
    state = fsm_next_state(state, CAR_DETECTED);
    fsm_print_action(state);
    printf("Car detected while closing: BLOCKED (state = %d)\n", state);

    // Gate stays blocked for 2 ticks.
    ticks = aux_get_ticks(4);

    for (int i = 1; i <= ticks; i++) {
        printf("Blocked tick %d\n", i);
    }

    
// Gate starts opening again.
state = fsm_next_state(state, BLOCK_DONE);
fsm_print_action(state);
printf("After blocked: RAISING (state = %d)\n", state);

// Wait 4 ticks for opening.
ticks = aux_get_ticks(1);

for (int i = 1; i <= ticks; i++) {
    printf("Opening again tick %d\n", i);
}

// Gate finishes opening again.
state = fsm_next_state(state, RAISE_DONE);
printf("After reopening: UP (state = %d)\n", state);

// Car leaves and gate waits.
state = fsm_next_state(state, CAR_LEFT);

ticks = aux_get_ticks(3);

for (int i = 1; i <= ticks; i++) {
    printf("Waiting again tick %d\n", i);
}

// Gate starts closing.
state = fsm_next_state(state, WAIT_DONE);
fsm_print_action(state);
printf("After waiting again: LOWERING (state = %d)\n", state);


// Gate takes 4 ticks to close.
ticks = aux_get_ticks(2);

for (int i = 1; i <= ticks; i++) {
    printf("Closing tick %d\n", i);
}

// Gate finishes closing.
state = fsm_next_state(state, LOWER_DONE);
fsm_print_action(state);
printf("After closing: DOWN (state = %d)\n", state);

    // Create the status word.
    uint32_t status = 0;

    status = set_field(status, 0, 3, state);
    status = set_field(status, 3, 1, state == RAISING);
    status = set_field(status, 4, 1, state == LOWERING);
    status = set_field(status, 5, 1, state == UP);
    status = set_field(status, 6, 1, 0);

    printf("Status word: 0x%08X\n", status);
    printf("State from status: %u\n",
           get_field(status, 0, 3));
    uint32_t test_status = 0;

test_status = set_field(test_status, 0, 3, RAISING);
test_status = set_field(test_status, 3, 1, 1);

printf("RAISING test: 0x%08X\n", test_status);
printf("Motor up: %u\n", get_field(test_status, 3, 1));


return 0;
}
