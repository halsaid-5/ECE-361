#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <time.h>

// One sensor reading.
typedef struct {
    time_t timestamp;
    float temp_c;
    float rh_pct;
} reading_t;

// Reads temperature and humidity.
// Returns 0 on success, -1 on failure.
int sensor_read(uint32_t *base, time_t timestamp, reading_t *reading);

#endif