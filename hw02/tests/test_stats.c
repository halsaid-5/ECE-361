
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
        printf("FAIL: stats_longest_run_above\n");
        return 1;
    }

    printf("All stats tests passed!\n");
    return 0;
}
