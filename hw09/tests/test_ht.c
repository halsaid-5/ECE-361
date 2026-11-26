#include "../ht.h"
#include <stdio.h>

static int failures = 0;
static int tests = 0;

static void check(int ok, const char *name)
{
    tests++;
    printf("%s %s\n", ok ? "PASS" : "FAIL", name);
    if (!ok)
        failures++;
}

static void test_basic(void)
{
    check(ht_create(0) == NULL, "zero buckets returns NULL");
    check(ht_create((size_t)-1) == NULL, "huge allocation returns NULL");
    check(ht_add(NULL, 5) == -1, "NULL add");
    check(ht_count(NULL, 5) == 0, "NULL count");
    check(ht_size(NULL) == 0, "NULL size");
    check(ht_longest_chain(NULL) == 0, "NULL longest chain");
    ht_destroy(NULL);
    check(1, "destroy NULL");

    ht_t *t = ht_create(10);
    if (t == NULL) {
        check(0, "create table");
        return;
    }
    check(ht_size(t) == 0 && ht_longest_chain(t) == 0 &&
          ht_count(t, 5) == 0, "empty table");

    check(ht_add(t, 5) == 0 && ht_add(t, 5) == 0 &&
          ht_add(t, 5) == 0 && ht_count(t, 5) == 3 &&
          ht_size(t) == 1, "one key three times");

    check(ht_add(t, 15) == 0 && ht_count(t, 15) == 1 &&
          ht_count(t, 5) == 3 && ht_count(t, 25) == 0 &&
          ht_size(t) == 2 && ht_longest_chain(t) == 2,
          "collision: 5 and 15 in bucket 5");
    ht_destroy(t);
    check(1, "destroy nonempty table");
}

static void test_row(size_t buckets, int step, size_t expected,
                     const char *name)
{
    ht_t *t = ht_create(buckets);
    if (t == NULL) {
        check(0, name);
        return;
    }
    int ok = 1;
    for (int i = 1; i <= 1000; i++) {
        if (ht_add(t, i * step) != 0)
            ok = 0;
    }
    for (int i = 1; i <= 1000; i++) {
        if (ht_count(t, i * step) != 1)
            ok = 0;
    }
    check(ok && ht_size(t) == 1000 &&
          ht_longest_chain(t) == expected, name);
    ht_destroy(t);
}

int main(void)
{
    test_basic();
    test_row(10, 1, 100, "1..1000 with 10 buckets: chain 100");
    test_row(1000, 1, 1, "1..1000 with 1000 buckets: chain 1");
    test_row(1000, 10, 10, "10..10000 with 1000 buckets: chain 10");
    test_row(1009, 10, 1, "10..10000 with 1009 buckets: chain 1");
    printf("Tests: %d, failed: %d\n", tests, failures);
    return failures == 0 ? 0 : 1;
}
