/* Temporary experiment: deliberately reproduces the original crash.
   Do not include this file in the final submission. */
#include <stddef.h>
#include <stdio.h>
struct node { int data; struct node *leftChild, *rightChild; };
static struct node *search(struct node *root, int data)
{
    struct node *current = root;
    while (current->data != data) { /* Original bug: NULL dereference. */
        if (current->data > data) current = current->leftChild;
        else current = current->rightChild;
        if (current == NULL) return NULL;
    }
    return current;
}
int main(void)
{
    puts("Testing original search on an empty tree");
    return search(NULL, 3) != NULL;
}
