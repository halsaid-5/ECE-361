#include <stdio.h>
#include "../stats.h"

int main(void) {
    float values[] = {10.0f, 20.0f, 30.0f};
    Stats result = stats_calculate(values, 3);

    if (result.min != 10.0f ||
        result.max != 30.0f ||
        result.mean != 20.0f) {
        printf("FAIL: stats_calculate\n");
        return 1;
    }

    if (stats_max(values, 3) != 30.0f) {
        printf("FAIL: stats_max\n");
        return 1;
    }

    float temps[] = {20.0f, 31.0f, 32.0f, 25.0f};
    int start_index;
    int best = stats_longest_run_above(temps, 4, 30.0f,
                                       &start_index);

    if (best != 2 || start_index != 1) {
        printf("FAIL: longest run\n");
        return 1;
    }

    /* Test when no temperature is above threshold */
    float low[] = {20.0f, 25.0f, 30.0f};
    best = stats_longest_run_above(low, 3, 30.0f,
                                   &start_index);

    if (best != 0 || start_index != -1) {
        printf("FAIL: no run\n");
        return 1;
    }

    /* Test recursive maximum with 10000 values */
    float large[10000];

    for (int i = 0; i < 10000; i++) {
        large[i] = (float)i;
    }

    if (stats_max(large, 10000) != 9999.0f) {
        printf("FAIL: large recursive max\n");
        return 1;
    }

    printf("All stats tests passed!\n");
    return 0;
}