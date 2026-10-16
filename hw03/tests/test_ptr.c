#include <stdio.h>
#include <stddef.h>
#include "../ptr.h"

int passed = 0;
int failed = 0;

void check(int condition, const char *name)
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
    // Test swap_float
    float x = 10.0f;
    float y = 20.0f;

    swap_float(&x, &y);
    check(x == 20.0f && y == 10.0f, "swap_float");

    // Test minmax
    float a[] = {5.0f, 2.0f, 9.0f, 1.0f};
    float min = 0.0f;
    float max = 0.0f;

    int result = minmax(a, 4, &min, &max);
    check(result == 0 && min == 1.0f && max == 9.0f,
          "minmax multiple values");

    // Test one value
    float one[] = {7.0f};
    result = minmax(one, 1, &min, &max);
    check(result == 0 && min == 7.0f && max == 7.0f,
          "minmax one value");

    // Test n = 0
    min = 100.0f;
    max = 200.0f;
    result = minmax(a, 0, &min, &max);
    check(result == -1 && min == 100.0f && max == 200.0f,
          "minmax n zero");

    // Test NULL
    result = minmax(NULL, 4, &min, &max);
    check(result == -1 && min == 100.0f && max == 200.0f,
          "minmax NULL");

    // Test find_above
    float b[] = {2.0f, 8.0f, 5.0f, 9.0f};

    const float *p = find_above(b, 4, 6.0f);
    check(p == &b[1], "find_above first match");

    p = find_above(b, 4, 10.0f);
    check(p == NULL, "find_above no match");

    float equal[] = {5.0f};
    p = find_above(equal, 1, 5.0f);
    check(p == NULL, "find_above equal threshold");

    // Test reverse even
    float even[] = {1.0f, 2.0f, 3.0f, 4.0f};
    reverse(even, 4);
    check(even[0] == 4.0f && even[1] == 3.0f &&
          even[2] == 2.0f && even[3] == 1.0f,
          "reverse even");

    // Test reverse odd
    float odd[] = {1.0f, 2.0f, 3.0f};
    reverse(odd, 3);
    check(odd[0] == 3.0f && odd[1] == 2.0f &&
          odd[2] == 1.0f, "reverse odd");

    printf("\nPassed: %d\n", passed);
    printf("Failed: %d\n", failed);

    return failed == 0 ? 0 : 1;
}