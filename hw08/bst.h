#ifndef BST_H
#define BST_H
#include <stdbool.h>
#include <stddef.h>

typedef struct bst bst_t; /* Opaque tree; its representation is private to bst.c. */

/* Create an empty tree. Returns NULL if allocation fails; no arguments. */
bst_t *bst_create(void);
/* Free every node and the tree. NULL is allowed and does nothing. */
void bst_destroy(bst_t *t);
/* Insert key (including duplicates, on the right). Returns 0 on success,
   -1 for NULL tree or allocation failure; on failure tree is unchanged. */
int bst_insert(bst_t *t, int key);
/* Search for key. Returns true if found, false otherwise. If visits is non-NULL,
   writes the number of compared nodes; NULL tree gives false and zero visits. */
bool bst_contains(const bst_t *t, int key, size_t *visits);
/* Number of stored keys, including duplicates. NULL or empty tree gives 0. */
size_t bst_size(const bst_t *t);
/* Number of nodes on longest root-to-leaf path. NULL/empty gives 0. */
size_t bst_height(const bst_t *t);
#endif
