#include "istack.h"
#include <stdio.h>
#include <stdlib.h>

static int is_open(int c) { return c == '(' || c == '[' || c == '{'; }
static int is_close(int c) { return c == ')' || c == ']' || c == '}'; }
static int matching(int c) {
    if (c == '(') return ')';
    if (c == '[') return ']';
    return '}';
}
int main(void) {
    istack_t *s = istack_create();
    if (!s) { fprintf(stderr, "out of memory\n"); return 1; }
    size_t line = 1, column = 0, pairs = 0, deepest = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') { line++; column = 0; continue; }
        column++;
        if (is_open(c)) {
            if (istack_push(s, c) != 0) {
                fprintf(stderr, "out of memory\n");
                istack_destroy(s);
                return 1;
            }
            if (istack_count(s) > deepest) deepest = istack_count(s);
        } else if (is_close(c)) {
            int top;
            if (istack_is_empty(s)) {
                printf("line %zu, column %zu: found '%c', nothing open\n", line, column, c);
                istack_destroy(s);
                return 1;
            }
            istack_peek(s, &top);
            if (matching(top) != c) {
                printf("line %zu, column %zu: found '%c', expected '%c'\n", line, column, c, matching(top));
                istack_destroy(s);
                return 1;
            }
            istack_pop(s, NULL);
            pairs++;
        }
    }
    if (!istack_is_empty(s)) {
        int top;
        istack_peek(s, &top);
        printf("end of input: %zu still open, innermost '%c'\n", istack_count(s), top);
        istack_destroy(s);
        return 1;
    }
    printf("balanced: %zu pairs, deepest %zu\n", pairs, deepest);
    istack_destroy(s);
    return 0;
}
