#include "sensor.h"
#include "iom361_r4.h"

// Read temperature and humidity from the sensor.
int sensor_read(uint32_t *base, time_t timestamp, reading_t *reading)
{
    int rc;

    if (base == NULL || reading == NULL) {
        return -1;
    }

    // Read temperature.
    uint32_t temp_raw = iom361_readReg(base, TEMP_REG, &rc);

    if (rc != 0) {
        return -1;
    }

    // Read humidity.
    uint32_t humid_raw = iom361_readReg(base, HUMID_REG, &rc);

    if (rc != 0) {
        return -1;
    }

    // Convert the 20-bit sensor values.
    temp_raw = temp_raw & 0xFFFFF;
    humid_raw = humid_raw & 0xFFFFF;

    reading->timestamp = timestamp;
    reading->temp_c = (temp_raw / 1048576.0f) * 200.0f - 50.0f;
    reading->rh_pct = (humid_raw / 1048576.0f) * 100.0f;

    return 0;
}
