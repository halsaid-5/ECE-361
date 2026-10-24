#ifndef TALLY_H
#define TALLY_H

#include <stdio.h>

#define TALLY_MAX 4
#define TALLY_NAMES 16
#define TALLY_LEN 15

typedef struct tally tally_t;

// Create a new tally. Returns NULL if full.
tally_t *tally_create(void);

// Destroy a tally. NULL is allowed.
void tally_destroy(tally_t *t);

// Add a name and return its count, or -1 on error.
int tally_add(tally_t *t, const char *name);

// Return the count of a name, or 0 if not found.
int tally_count(const tally_t *t, const char *name);

// Return the number of different names.
int tally_size(const tally_t *t);

// Print names and counts in alphabetical order.
void tally_print(const tally_t *t, FILE *out);

#endif