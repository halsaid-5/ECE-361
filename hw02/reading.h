#ifndef READING_H
#define READING_H

#include <stdio.h>

#define MAX_READINGS 1000

/* Reads sensor data from a file.
 * Takes a file, arrays, maximum size, and skipped count.
 * Returns the number of valid readings.
 * Assumes the arrays have enough space.
 */
int reading_read(FILE *input, int ticks[],
                 float temps[], float hums[],
                 int max_readings, int *skipped);

#endif
