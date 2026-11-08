#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "iom361_r4.h"
#include "sensor.h"
#include "panel.h"
#include "scenario.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s scenario.txt\n", argv[0]);
        return 1;
    }
    scenario_t scenario;
    int error = scenario_load(argv[1], &scenario);
    if (error != 0) {
        fprintf(stderr, "Scenario error at line %d\n", error);
        return 1;
    }
    int rc;
    uint32_t *base = iom361_initialize(4, 4, &rc);
    if (base == NULL || rc != 0) return 1;
    iom361_set_display(false);
    uint32_t before = 0;
    long last_tick = scenario.lines[scenario.count - 1].tick;
    for (long tick = 0; tick <= last_tick; tick++) {
        const scenario_line_t *row = scenario_at(&scenario, tick);
        _iom361_set_sensor1(row->temp_c, row->rh_pct);
        _iom361_set_switches(row->switches);
        time_t now = scenario.start + (time_t)tick;
        reading_t reading;
        if (sensor_read(base, now, &reading) != 0) return 1;
        uint32_t switches = iom361_readReg(base, SWITCHES_REG, &rc);
        if (rc != 0) return 1;
        uint32_t pressed = panel_pressed(switches, before);
        for (int k = 0; k < 4; k++) {
            if (pressed & (1u << k)) {
                if (panel_toggle(base, k) != 0) return 1;
            }
        }
        uint32_t leds = iom361_readReg(base, LEDS_REG, &rc);
        if (rc != 0) return 1;
        char date[32];
        struct tm *utc = gmtime(&now);
        if (utc == NULL || strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", utc) == 0)
            return 1;
        printf("%s temp=%.1f rh=%.1f switches=0x%X pressed=0x%X leds=0x%X\n",
               date, reading.temp_c, reading.rh_pct, switches, pressed, leds);
        before = switches;
    }
    return 0;
}
