#include "../bst.h"
#include <stdio.h>
#include <stdlib.h>

static int failures = 0;
static void check(int ok, const char *name)
{
    printf("%s %s\n", ok ? "PASS" : "FAIL", name);
    if (!ok) failures++;
}

int main(void)
{
    size_t visits = 999;
    check(!bst_contains(NULL, 5, &visits) && visits == 0, "NULL tree search");
    check(bst_size(NULL) == 0 && bst_height(NULL) == 0, "NULL size and height");
    check(bst_insert(NULL, 1) == -1, "NULL insert");
    bst_destroy(NULL);

    bst_t *empty = bst_create();
    if (!empty) return 1;
    visits = 999;
    check(!bst_contains(empty, 3, &visits) && visits == 0,
          "empty tree search (original crash case)");
    check(bst_size(empty) == 0 && bst_height(empty) == 0, "empty tree dimensions");
    bst_destroy(empty);

    bst_t *tree = bst_create();
    if (!tree) return 1;
    const int keys[] = {27, 14, 35, 10, 19, 31, 42};
    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        if (bst_insert(tree, keys[i]) != 0) return 1;
    }
    check(bst_size(tree) == 7, "seven keys size");
    check(bst_height(tree) == 3, "seven keys height");
    visits = 0;
    check(bst_contains(tree, 31, &visits) && visits == 3, "find 31 in 3 visits");
    visits = 0;
    check(!bst_contains(tree, 15, &visits) && visits == 3, "miss 15 in 3 visits");
    bst_destroy(tree);
    check(1, "destroy full tree");

    tree = bst_create();
    if (!tree) return 1;
    check(bst_insert(tree, 5) == 0 && bst_insert(tree, 5) == 0 &&
          bst_size(tree) == 2 && bst_height(tree) == 2, "duplicate goes right");
    bst_destroy(tree);

    tree = bst_create();
    if (!tree) return 1;
    for (int i = 1; i <= 100; i++) {
        if (bst_insert(tree, i) != 0) return 1;
    }
    check(bst_size(tree) == 100 && bst_height(tree) == 100, "increasing order height");
    bst_destroy(tree);
    printf("Tests: %d failed\n", failures);
    return failures ? 1 : 0;
}
