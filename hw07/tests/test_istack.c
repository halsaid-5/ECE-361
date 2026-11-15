#include "../istack.h"
#include <stdio.h>
#include <stdlib.h>
static int failures = 0, tests = 0;
#define TEST(name, condition) do { \
    tests++; if (condition) printf("PASS %s\n", name); \
    else { printf("FAIL %s\n", name); failures++; } \
} while (0)
int main(void) {
    int v = 123;
    TEST("NULL count/empty/capacity", istack_count(NULL)==0 && istack_is_empty(NULL) && istack_capacity(NULL)==0);
    TEST("NULL push/pop/peek", istack_push(NULL,3)==-1 && istack_pop(NULL,&v)==-1 && istack_peek(NULL,&v)==-1 && v==123);
    size_t n=999;
    TEST("NULL to_array", istack_to_array(NULL,&n)==NULL && n==0);
    istack_destroy(NULL);
    istack_t *s=istack_create();
    if (!s) { puts("FAIL create"); return 1; }
    TEST("new stack", istack_is_empty(s) && istack_capacity(s)==8);
    TEST("empty pop keeps output", istack_pop(s,&v)==-1 && v==123);
    TEST("empty peek keeps output", istack_peek(s,&v)==-1 && v==123);
    n=999;
    TEST("empty array", istack_to_array(s,&n)==NULL && n==0);
    for (int i=0;i<8;i++) if (istack_push(s,i)!=0) return 1;
    TEST("eight fill capacity", istack_count(s)==8 && istack_capacity(s)==8);
    TEST("ninth doubles capacity", istack_push(s,8)==0 && istack_capacity(s)==16 && istack_count(s)==9);
    TEST("peek top", istack_peek(s,&v)==0 && v==8 && istack_count(s)==9);
    int *a=istack_to_array(s,&n);
    TEST("array bottom first", a && n==9 && a[0]==0 && a[8]==8);
    if (a) a[0]=900;
    TEST("array is copy", istack_pop(s,&v)==0 && v==8 && a && a[0]==900);
    free(a);
    for (int i=7;i>=0;i--) if (istack_pop(s,&v)!=0 || v!=i) { puts("FAIL LIFO"); failures++; break; }
    TEST("empty after pops", istack_is_empty(s));
    for (int i=0;i<1000;i++) if (istack_push(s,i)!=0) return 1;
    TEST("1000 pushes", istack_count(s)==1000 && istack_capacity(s)>=1000);
    for (int i=999;i>=0;i--) if (istack_pop(s,&v)!=0 || v!=i) { puts("FAIL 1000 LIFO"); failures++; break; }
    TEST("1000 pops", istack_is_empty(s));
    istack_t *other=istack_create();
    if (!other) return 1;
    istack_push(s,11); istack_push(other,22);
    TEST("independent stacks", istack_pop(s,&v)==0 && v==11 && istack_peek(other,&v)==0 && v==22);
    TEST("NULL output pointers", istack_peek(other,NULL)==0 && istack_pop(other,NULL)==0);
    istack_push(other,99);
    istack_destroy(other);
    istack_destroy(s);
    printf("Unit tests: %d tests, %d failed\n", tests, failures);
    return failures ? 1 : 0;
}
