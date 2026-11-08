#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>

int sensor_read(uint32_t *base, time_t now, reading_t *r) {
    if (r == NULL) return 1;
    int rc;
    uint32_t temp = iom361_readReg(base, TEMP_REG, &rc);
    if (rc != 0) return rc;
    uint32_t humid = iom361_readReg(base, HUMID_REG, &rc);
    if (rc != 0) return rc;

    temp &= 0xFFFFFu;
    humid &= 0xFFFFFu;
    float c = ((float)temp / 1048576.0f) * 200.0f - 50.0f;
    float h = ((float)humid / 1048576.0f) * 100.0f;
    reading_t value = {now, roundf(c * 10.0f) / 10.0f,
                            roundf(h * 10.0f) / 10.0f};
    *r = value;
    return 0;
}
