
#include <stdio.h>
#include "iom361_r4.h"

int main(void)
{
    int rc;

    uint32_t *base = iom361_initialize(2, 3, &rc);

    if (base == NULL || rc != 0) {
        printf("Initialization failed.\n");
        return 1;
    }

    printf("Parking Garage Exit Gate\n");

    return 0;
}
