#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sensor.h"
#include "panel.h"
#include "scenario.h"
#include "iom361_r4.h"

static int failures = 0;
#define TEST(name, expr) do { \
    if (expr) printf("PASS %s\n", name); \
    else { printf("FAIL %s\n", name); failures++; } \
} while (0)

static void write_text(const char *path, const char *text) {
    FILE *f = fopen(path, "w");
    if (f) { fputs(text, f); fclose(f); }
}

int main(void) {
    int rc;
    uint32_t *base = iom361_initialize(4, 4, &rc);
    iom361_set_display(false);
    TEST("initialize", base != NULL && rc == 0);
    reading_t r = {123, -10.0f, -10.0f};
    _iom361_set_sensor1(91.0f, 75.0f);
    TEST("91 degrees rounds correctly", sensor_read(base, 5, &r) == 0 && r.temp_c == 91.0f && r.t == 5);
    reading_t old = r;
    TEST("failed read changes nothing", sensor_read(NULL, 6, &r) != 0 && memcmp(&r, &old, sizeof(r)) == 0);
    TEST("press", panel_pressed(0x1, 0x0) == 0x1);
    TEST("release", panel_released(0x0, 0x1) == 0x1);
    TEST("held switch", panel_pressed(0x1, 0x1) == 0 && panel_released(0x1, 0x1) == 0);
    TEST("invalid LED", panel_led(base, -1, 1) == -1 && panel_toggle(base, 32) == -1);
    TEST("LED 0 on", panel_led(base, 0, 1) == 0);
    TEST("LED 1 on", panel_led(base, 1, 1) == 0);
    TEST("LED 0 off keeps LED 1", panel_led(base, 0, 0) == 0 && iom361_readReg(base, LEDS_REG, &rc) == 2);
    TEST("toggle LED 2 keeps LED 1", panel_toggle(base, 2) == 0 && iom361_readReg(base, LEDS_REG, &rc) == 6);
    TEST("toggle LED 2 again", panel_toggle(base, 2) == 0 && iom361_readReg(base, LEDS_REG, &rc) == 2);
    scenario_t s;
    TEST("load comments and blank lines", scenario_load("scenarios/basic.txt", &s) == 0 && s.count == 8);
    const scenario_line_t *row = scenario_at(&s, 3);
    TEST("values hold", row != NULL && row->tick == 3 && scenario_at(&s, 2)->tick == 2);
    write_text("tests/invalid.tmp", "0 10 20 0x1\n");
    TEST("missing start", scenario_load("tests/invalid.tmp", &s) == 1);
    write_text("tests/invalid.tmp", "start 1791273600\n0 10 20\n");
    TEST("missing field", scenario_load("tests/invalid.tmp", &s) == 2);
    write_text("tests/invalid.tmp", "start 1791273600\n0 10 20 0x0\n0 11 30 0x1\n");
    TEST("ticks not increasing", scenario_load("tests/invalid.tmp", &s) == 3);
    remove("tests/invalid.tmp");
    printf("Unit tests: %s\n", failures == 0 ? "PASS" : "FAIL");
    return failures != 0;
}
