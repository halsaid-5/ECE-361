#ifndef PTR_H
#define PTR_H

// Takes two float pointers and swaps their values.
// Assumes both pointers are valid.
// Returns nothing.
void swap_float(float *a, float *b);

// Takes an array, its length, and two output pointers.
// Stores the minimum and maximum values.
// Returns 0 on success or -1 for invalid input.
// Assumes n >= 1 and all pointers are valid for success.
int minmax(const float *a, int n, float *min, float *max);

// Takes an array, its length, and a threshold.
// Returns a pointer to the first value above the threshold,
// or NULL if no value is found.
// Assumes a valid array and n >= 1 for searching.
const float *find_above(const float *a, int n, float threshold);

// Takes an array and its length.
// Reverses the array and returns nothing.
// Does nothing if a is NULL or n < 2.
void reverse(float *a, int n);

#endif