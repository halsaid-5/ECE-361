#include <stdio.h>
#include "bits.h"

void print_binary(uint32_t x, int width)
{
    for (int i = width - 1; i >= 0; i--)
    {
        printf("%u", (x >> i) & 1u);

        if (i > 0 && i % 4 == 0)
        {
            printf(" ");
        }
    }

    printf("\n");
}

uint32_t get_field(uint32_t word, int pos, int width)
{
    if (width < 1 || width > 32 ||
        pos < 0 || pos > 31 ||
        pos + width > 32)
    {
        return 0;
    }

    uint32_t mask;

    if (width == 32)
    {
        mask = 0xFFFFFFFFu;
    }
    else
    {
        mask = (1u << width) - 1u;
    }

    return (word >> pos) & mask;
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value)
{
    if (width < 1 || width > 32 ||
        pos < 0 || pos > 31 ||
        pos + width > 32)
    {
        return word;
    }

    uint32_t mask;

    if (width == 32)
    {
        mask = 0xFFFFFFFFu;
    }
    else
    {
        mask = (1u << width) - 1u;
    }

    word &= ~(mask << pos);
    word |= (value & mask) << pos;

    return word;
}

int32_t sign_extend(uint32_t value, int width)
{
    int32_t result = (int32_t)value;
    int shift = 32 - width;

    if (shift > 0)
    {
        result <<= shift;
        result >>= shift;
    }

    return result;
}