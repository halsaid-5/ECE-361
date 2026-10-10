#include <stdio.h>
#include <stdlib.h>
#include "reading.h"
#include "stats.h"
#include "histogram.h"

int main(int argc, char *argv[]) {
    int ticks[MAX_READINGS];
    float temps[MAX_READINGS];
    float hums[MAX_READINGS];

    int count;
    int skipped = 0;
    float threshold = 30.0f;

    /* Read threshold */
    if (argc > 2) {
        fprintf(stderr,
                "usage: %s [threshold] < readings.txt\n",
                argv[0]);
        return 1;
    }

    if (argc == 2) {
        char *end;
        threshold = strtof(argv[1], &end);

        if (*end != '\0') {
            fprintf(stderr,
                    "error: threshold '%s' is not a number\n",
                    argv[1]);
            return 1;
        }
    }

    /* Read data */
    count = reading_read(stdin, ticks, temps, hums,
                         MAX_READINGS, &skipped);

    printf("readings: %d\n", count);
    printf("skipped:  %d\n", skipped);

    if (count == 0) {
        printf("no readings, no summary\n");
        return 0;
    }

    /* Calculate statistics */
    Stats temp_stats = stats_calculate(temps, count);
    Stats hum_stats = stats_calculate(hums, count);

    printf("temperature: min %6.1f  max %6.1f  mean %6.2f C\n",
           temp_stats.min, temp_stats.max,
           temp_stats.mean);

    printf("humidity:    min %6.1f  max %6.1f  mean %6.2f %%RH\n",
           hum_stats.min, hum_stats.max,
           hum_stats.mean);

    /* Find longest run */
    int start_index;
    int best = stats_longest_run_above(temps, count,
                                       threshold, &start_index);

    if (best == 0) {
        printf("above %.1f C: never\n", threshold);
    } else {
        printf("above %.1f C: longest run %d readings, from tick %d to tick %d\n",
               threshold, best,
               ticks[start_index],
               ticks[start_index + best - 1]);
    }

    /* Print histogram */
    print_histogram(temps, count);

    return 0;
}