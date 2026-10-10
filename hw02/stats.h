#ifndef STATS_H
#define STATS_H

/* Store minimum, maximum, and mean */
typedef struct {
    float min;
    float max;
    float mean;
} Stats;

/* Calculates minimum, maximum, and mean.
 * Takes an array and its count.
 * Returns a Stats structure.
 * Assumes count is at least 1.
 */
Stats stats_calculate(const float values[], int count);

/* Finds the maximum using recursion.
 * Takes an array and its count.
 * Returns the maximum value.
 * Assumes count is at least 1.
 */
float stats_max(const float values[], int count);

/* Finds the longest run above a threshold.
 * Takes temperatures, count, threshold, and start index.
 * Returns the longest run length.
 * Sets start_index to -1 if no run is found.
 * Assumes count is zero or greater and start_index is valid.
 */
int stats_longest_run_above(const float temps[], int count,
                            float threshold, int *start_index);

#endif
