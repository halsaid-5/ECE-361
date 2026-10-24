
#include <stdio.h>
#include "tally.h"

static int passed = 0;
static int failed = 0;

void check(const char *name, int condition)
{
    if (condition) {
        printf("PASS: %s\n", name);
        passed++;
    } else {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

int main(void)
{
    tally_t *t = tally_create();

    check("Create tally", t != NULL);

    if (t == NULL) {
        return 1;
    }

    check("Empty tally", tally_size(t) == 0);
    check("Add Ali", tally_add(t, "Ali") == 1);
    check("Add Sara", tally_add(t, "Sara") == 1);
    check("Add Ali again", tally_add(t, "Ali") == 2);
    check("Count Ali", tally_count(t, "Ali") == 2);
    check("Count Sara", tally_count(t, "Sara") == 1);
    check("Unknown name", tally_count(t, "Omar") == 0);
    check("Total names", tally_size(t) == 2);
    check("NULL add", tally_add(NULL, "Ali") == -1);
check("NULL name", tally_add(t, NULL) == -1);
check("NULL count", tally_count(NULL, "Ali") == 0);
check("NULL size", tally_size(NULL) == 0);
check("Empty name", tally_add(t, "") == -1);
check("Long name", tally_add(t, "ABCDEFGHIJKLMNOP") == -1);
tally_t *full = tally_create();

check("Create second tally", full != NULL);

if (full != NULL) {
    char name[16];

    for (int i = 0; i < TALLY_NAMES; i++) {
        sprintf(name, "Name%d", i);
        tally_add(full, name);
    }

    check("Full tally size", tally_size(full) == 16);
    check("Reject 17th name", tally_add(full, "Extra") == -1);

    tally_destroy(full);
}

    tally_destroy(t);
    // Test the maximum number of tallies.
tally_t *a = tally_create();
tally_t *b = tally_create();
tally_t *c = tally_create();
tally_t *d = tally_create();
tally_t *e = tally_create();

check("Create 4 tallies",
      a != NULL && b != NULL && c != NULL && d != NULL);

check("Reject 5th tally", e == NULL);

tally_destroy(a);
tally_destroy(b);
tally_destroy(c);
tally_destroy(d);

    printf("\nPassed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}
