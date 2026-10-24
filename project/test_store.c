#include <stdio.h>
#include "store.h"

int main(void)
{
    store_t *store = store_create();

    if (store == NULL) {
        return 1;
    }

    record_t a = {0};
    record_t b = {0};
    record_t c = {0};

    a.reading.temp_c = 21.2f;
    b.reading.temp_c = 21.4f;
    c.reading.temp_c = 22.0f;

    printf("Compare a and b: %d\n",
           record_compare(&a, &b));

    printf("Compare a and c: %d\n",
           record_compare(&a, &c));

    store_insert(store, a);
    store_insert(store, b);
    store_insert(store, c);

    printf("Store count: %zu\n", store_count(store));

    const record_t *found = store_find(store, 21.2f);

    printf("Find 21.2: %s\n",
           found != NULL ? "Found" : "Not found");

    store_destroy(store);

    return 0;
}
