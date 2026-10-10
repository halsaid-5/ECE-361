#include "stats.h"

/* Finds the maximum using recursion.
 * Takes an array and its count.
 * Returns the maximum value.
 * Assumes count is at least 1.
 */
float stats_max(const float values[], int count) {
    if (count == 1)
        return values[0];

    float max = stats_max(values, count - 1);

    if (values[count - 1] > max)
        return values[count - 1];

    return max;
}

/* Calculates minimum, maximum, and mean.
 * Takes an array and its count.
 * Returns a Stats structure.
 * Assumes count is at least 1.
 */
Stats stats_calculate(const float values[], int count) {
    Stats result;

    result.min = values[0];
    result.max = stats_max(values, count);

    float sum = 0.0f;

    for (int i = 0; i < count; i++) {
        if (values[i] < result.min)
            result.min = values[i];

        sum += values[i];
    }

    result.mean = sum / count;

    return result;
}

/* Finds the longest run above a threshold.
 * Takes temperatures, count, threshold, and start index.
 * Returns the longest run length.
 * Sets start_index to -1 if no run is found.
 */
int stats_longest_run_above(const float temps[], int count,
                            float threshold, int *start_index) {

    int run = 0;
    int best = 0;
    int start = 0;

    *start_index = -1;

    for (int i = 0; i < count; i++) {
        if (temps[i] > threshold) {
            if (run == 0)
                start = i;

            run++;

            if (run > best) {
                best = run;
                *start_index = start;
            }
        } else {
            run = 0;
        }
    }

    return best;
}
