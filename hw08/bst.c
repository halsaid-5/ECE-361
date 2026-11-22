#include "bst.h"
#include <stdlib.h>

struct node {
    int data;
    struct node *leftChild;
    struct node *rightChild;
};

struct bst {
    struct node *root;
    size_t count;
};

/* New tree wrapper; the original used one global root instead. */
bst_t *bst_create(void)
{
    return calloc(1, sizeof(bst_t));
}

/* Recursive cleanup added because the original had no destroy function. */
static void free_nodes(struct node *current)
{
    if (current == NULL) return;
    free_nodes(current->leftChild);
    free_nodes(current->rightChild);
    free(current);
}

void bst_destroy(bst_t *t)
{
    if (t == NULL) return;
    free_nodes(t->root);
    free(t);
}

/* Adapted from original insert(): use t->root, report allocation errors,
   and count inserted nodes. Equal keys still go to the right. */
int bst_insert(bst_t *t, int key)
{
    if (t == NULL) return -1;
    struct node *tempNode = malloc(sizeof(*tempNode));
    if (tempNode == NULL) return -1;
    tempNode->data = key;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    if (t->root == NULL) {
        t->root = tempNode;
    } else {
        struct node *current = t->root;
        struct node *parent = NULL;
        while (1) {
            parent = current;
            if (key < parent->data) {
                current = current->leftChild;
                if (current == NULL) {
                    parent->leftChild = tempNode;
                    break;
                }
            } else {
                current = current->rightChild;
                if (current == NULL) {
                    parent->rightChild = tempNode;
                    break;
                }
            }
        }
    }
    t->count++;
    return 0;
}

/* Adapted from original search(): check current before reading its data.
   The original loop read current->data before checking current != NULL. */
bool bst_contains(const bst_t *t, int key, size_t *visits)
{
    size_t compared = 0;
    const struct node *current = (t == NULL) ? NULL : t->root;
    while (current != NULL) {
        compared++;
        if (current->data == key) {
            if (visits != NULL) *visits = compared;
            return true;
        }
        if (key < current->data)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    if (visits != NULL) *visits = compared;
    return false;
}

size_t bst_size(const bst_t *t)
{
    return (t == NULL) ? 0 : t->count;
}

static size_t node_height(const struct node *current)
{
    if (current == NULL) return 0;
    size_t left = node_height(current->leftChild);
    size_t right = node_height(current->rightChild);
    return 1 + (left > right ? left : right);
}

size_t bst_height(const bst_t *t)
{
    return (t == NULL) ? 0 : node_height(t->root);
}
