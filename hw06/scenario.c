#include "scenario.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scenario_load(const char *filename, scenario_t *scenario) {
    if (filename == NULL || scenario == NULL) return 1;
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 1;
    memset(scenario, 0, sizeof(*scenario));
    char text[256];
    int line_number = 0;
    int have_start = 0;
    long last_tick = -1;
    while (fgets(text, sizeof(text), file) != NULL) {
        line_number++;
        char *comment = strchr(text, '#');
        if (comment != NULL) *comment = '\0';
        char *p = text;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') continue;
        if (!have_start) {
            long long start;
            char extra;
            if (sscanf(p, "start %lld %c", &start, &extra) != 1) {
                fclose(file);
                return line_number;
            }
            scenario->start = (time_t)start;
            have_start = 1;
            continue;
        }
        scenario_line_t row;
        unsigned switches;
        char extra;
        if (sscanf(p, "%ld %f %f %x %c", &row.tick,
                   &row.temp_c, &row.rh_pct, &switches, &extra) != 4 ||
            row.tick <= last_tick || row.tick < 0 ||
            scenario->count == MAX_SCENARIO_LINES ||
            row.temp_c < -50.0f || row.temp_c > 150.0f ||
            row.rh_pct < 0.0f || row.rh_pct > 100.0f) {
            fclose(file);
            return line_number;
        }
        row.switches = switches;
        scenario->lines[scenario->count++] = row;
        last_tick = row.tick;
    }
    fclose(file);
    if (!have_start || scenario->count == 0 || scenario->lines[0].tick != 0)
        return line_number > 0 ? line_number : 1;
    return 0;
}
const scenario_line_t *scenario_at(const scenario_t *scenario, long tick) {
    if (scenario == NULL || scenario->count == 0 || tick < scenario->lines[0].tick)
        return NULL;
    const scenario_line_t *result = &scenario->lines[0];
    for (int i = 1; i < scenario->count; i++) {
        if (scenario->lines[i].tick > tick) break;
        result = &scenario->lines[i];
    }
    return result;
}
