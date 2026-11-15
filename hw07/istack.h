#ifndef ISTACK_H
#define ISTACK_H
#include <stdbool.h>
#include <stddef.h>
#define ISTACK_START 8
/* The stack's internal fields are private. */
typedef struct istack istack_t;
/* Create an empty stack with room for 8 ints; returns NULL on failure. */
istack_t *istack_create(void);
/* Free a stack and its array; accepts NULL. */
void istack_destroy(istack_t *s);
/* Add v on top; returns 0 or -1 on failure; failure leaves stack unchanged. */
int istack_push(istack_t *s, int v);
/* Remove top into *v if v != NULL; returns -1 if NULL/empty; leaves *v alone then. */
int istack_pop(istack_t *s, int *v);
/* Read top without removing it; returns -1 if NULL/empty; leaves *v alone then. */
int istack_peek(const istack_t *s, int *v);
/* Number of values; NULL returns 0. */
size_t istack_count(const istack_t *s);
/* Whether empty; NULL counts as empty. */
bool istack_is_empty(const istack_t *s);
/* Allocated number of int slots; NULL returns 0. */
size_t istack_capacity(const istack_t *s);
/* New bottom-first copy; caller frees it. NULL/empty/failure => NULL and *n=0. */
int *istack_to_array(const istack_t *s, size_t *n);
#endif
