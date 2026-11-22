#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int main(void)
{
    bst_t *tree = bst_create();
    if (tree == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }
    char token[128];
    size_t n = 0;
    int result = 0;
    while (scanf("%127s", token) == 1) {
        char *end;
        errno = 0;
        long number = strtol(token, &end, 10);
        if (token[0] == '\0' || *end != '\0' || errno == ERANGE ||
            number < INT_MIN || number > INT_MAX) {
            printf("not a number after %zu values\n", n);
            result = 1;
            break;
        }
        if (bst_insert(tree, (int)number) != 0) {
            fprintf(stderr, "out of memory\n");
            result = 1;
            break;
        }
        n++;
    }
    if (result == 0) {
        if (n == 0) printf("empty tree\n");
        else printf("n %zu, height %zu\n", bst_size(tree), bst_height(tree));
    }
    bst_destroy(tree);
    return result;
}
