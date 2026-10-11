#include <stdio.h>
#include "../stats.h"

int main(void) {
    /* Test statistics */
    float values[] = {10.0f, 20.0f, 30.0f};
    Stats result = stats_calculate(values, 3);

    if (result.min != 10.0f ||
        result.max != 30.0f ||
        result.mean != 20.0f) {
        printf("FAIL: stats_calculate\n");
        return 1;
    }
    printf("PASS: stats_calculate\n");

    /* Test one value */
    float single[] = {5.0f};

    if (stats_max(single, 1) != 5.0f) {
        printf("FAIL: single value\n");
        return 1;
    }
    printf("PASS: single value\n");

    /* Test maximum at the start */
    float first[] = {50.0f, 20.0f, 10.0f};

    if (stats_max(first, 3) != 50.0f) {
        printf("FAIL: max at start\n");
        return 1;
    }
    printf("PASS: max at start\n");

    /* Test maximum at the end */
    float last[] = {10.0f, 20.0f, 50.0f};

    if (stats_max(last, 3) != 50.0f) {
        printf("FAIL: max at end\n");
        return 1;
    }
    printf("PASS: max at end\n");

    /* Test longest run */
    float temps[] = {20.0f, 31.0f, 32.0f, 25.0f};
    int start_index;

    int best = stats_longest_run_above(
        temps, 4, 30.0f, &start_index);

    if (best != 2 || start_index != 1) {
        printf("FAIL: longest run\n");
        return 1;
    }
    printf("PASS: longest run\n");

    /* Test no values above threshold */
    float low[] = {20.0f, 25.0f, 30.0f};

    best = stats_longest_run_above(
        low, 3, 30.0f, &start_index);

    if (best != 0 || start_index != -1) {
        printf("FAIL: no run\n");
        return 1;
    }
    printf("PASS: no run\n");

    /* Test value equal to threshold */
    float equal[] = {31.0f, 30.0f, 32.0f};

    best = stats_longest_run_above(
        equal, 3, 30.0f, &start_index);

    if (best != 1 || start_index != 0) {
        printf("FAIL: equal threshold\n");
        return 1;
    }
    printf("PASS: equal threshold\n");

    /* Test recursive maximum with 10000 values */
    float large[10000];

    for (int i = 0; i < 10000; i++) {
        large[i] = (float)i;
    }

    if (stats_max(large, 10000) != 9999.0f) {
        printf("FAIL: large recursive max\n");
        return 1;
    }
    printf("PASS: large recursive max\n");

    printf("All stats tests passed!\n");

    return 0;
}
