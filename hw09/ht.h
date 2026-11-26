#ifndef HT_H
#define HT_H

#include <stddef.h>

typedef struct ht ht_t; /* opaque */

/* Takes a bucket count; returns an empty table or NULL on zero/failed allocation. */
ht_t *ht_create(size_t nbuckets);

/* Takes a table or NULL; frees all memory. NULL is allowed. */
void ht_destroy(ht_t *t);

/* Takes a table and nonnegative key; adds one occurrence. Returns 0 on success,
   -1 if table is NULL or allocation fails; on failure table is unchanged. */
int ht_add(ht_t *t, int key);

/* Takes a table or NULL and nonnegative key; returns occurrence count, or 0
   if the key is absent or table is NULL. */
size_t ht_count(const ht_t *t, int key);

/* Takes a table or NULL; returns number of different keys, or 0 for NULL. */
size_t ht_size(const ht_t *t);

/* Takes a table or NULL; returns longest bucket chain length, or 0 if empty/NULL. */
size_t ht_longest_chain(const ht_t *t);

#endif
