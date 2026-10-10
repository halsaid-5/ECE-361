#include <stdio.h>
#include "histogram.h"

#define NUM_BINS 20
#define BIN_WIDTH 5.0f

/* Prints a temperature histogram.
 * Takes an array of temperatures and its count.
 * Returns nothing.
 * Assumes count is zero or greater.
 */
void print_histogram(const float temps[], int count) {
    int bins[NUM_BINS] = {0};

    /* Count temperatures in each bin */
    for (int i = 0; i < count; i++) {
        int b = (int)(temps[i] / BIN_WIDTH);

        if (temps[i] < 0.0f)
            b = 0;

        if (b >= NUM_BINS)
            b = NUM_BINS - 1;

        bins[b]++;
    }

    printf("histogram:\n");

    /* Print bins that have readings */
    for (int b = 0; b < NUM_BINS; b++) {
        if (bins[b] == 0)
            continue;

        printf("  %5.1f to %5.1f C | ",
               b * BIN_WIDTH, (b + 1) * BIN_WIDTH);

        for (int k = 0; k < bins[b]; k++)
            putchar('*');

        printf(" %d\n", bins[b]);
    }
}
