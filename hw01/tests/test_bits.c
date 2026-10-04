#include <stdio.h>
#include <stdint.h>
#include "bits.h"
#include "status.h"

int passed = 0;
int failed = 0;

void check(const char *name, int condition)
{
    if (condition)
    {
        printf("PASS: %s\n", name);
        passed++;
    }
    else
    {
        printf("FAIL: %s\n", name);
        failed++;
    }
}

int main(void)
{
    /* print_binary */
    printf("print_binary test (should print 0010 1100): ");
    print_binary(0x2C, 8);

    /* get_field tests */
    check("get_field width 1",
          get_field(0x1, 0, 1) == 1);

    check("get_field width 32",
          get_field(0x12345678, 0, 32) == 0x12345678);

    check("get_field pos 31",
          get_field(0x80000000, 31, 1) == 1);

    /* get_field invalid arguments */
    check("get_field invalid width",
          get_field(0x12345678, 0, 0) == 0);

    check("get_field invalid range",
          get_field(0x12345678, 31, 2) == 0);

    /* set_field tests */
    check("set_field width 1",
          set_field(0, 0, 1, 1) == 1);

    check("set_field width 32",
          set_field(0, 0, 32, 0x12345678) == 0x12345678);

    check("set_field pos 31",
          set_field(0, 31, 1, 1) == 0x80000000);

    check("set_field value too wide",
          set_field(0, 4, 3, 0xF) == 0x70);

    /* set_field invalid arguments */
    check("set_field invalid width",
          set_field(0x12345678, 0, 0, 1) == 0x12345678);

    check("set_field invalid range",
          set_field(0x12345678, 31, 2, 1) == 0x12345678);

    /* sign_extend tests */
    check("sign_extend -8",
          sign_extend(0xF8, 8) == -8);

    check("sign_extend width 1 negative",
          sign_extend(1, 1) == -1);

    check("sign_extend most negative",
          sign_extend(0x80000000, 32) == INT32_MIN);

    /* status_unpack example from homework */
    status_t s1 = status_unpack(0x1631);

    check("status example setpoint", s1.setpoint == 22);
    check("status example mode", s1.mode == 3);
    check("status example heat", s1.heat == 1);
    check("status example cool", s1.cool == 0);
    check("status example fan", s1.fan == 0);
    check("status example fault", s1.fault == 0);
    check("status example reserved", s1.reserved == 0);

    /* second status word */
    status_t s2 = status_unpack(0x0000);

    check("status zero setpoint", s2.setpoint == 0);
    check("status zero mode", s2.mode == 0);
    check("status zero heat", s2.heat == 0);

    /* third status word: negative setpoint */
    status_t s3 = status_unpack(0xF800);

    check("status negative setpoint", s3.setpoint == -8);

    /* invalid mode */
    status_t s4 = status_unpack(0x0050);

    check("status invalid mode", s4.mode == 5);

    printf("\n%d passed, %d failed\n", passed, failed);

    if (failed != 0)
        return 1;

    return 0;
}