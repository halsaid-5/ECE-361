#ifndef PTR_H
#define PTR_H

// Swaps the values of two floats.
void swap_float(float *a, float *b);

// Finds the minimum and maximum values.
// Returns 0 on success and -1 for invalid input.
int minmax(const float *a, int n, float *min, float *max);

// Finds the first value greater than threshold.
// Returns NULL if no value is found.
const float *find_above(const float *a, int n, float threshold);

// Reverses the order of an array.
void reverse(float *a, int n);

#endif