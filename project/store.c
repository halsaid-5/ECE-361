#include "store.h"
#include <stdlib.h>
#include <math.h>

// Store records in a sorted array.
struct store {
    record_t *records;
    size_t count;
    size_t capacity;
};

// Group temperatures into 0.5 C intervals.
static int temp_key(float temp)
{
    return (int)floorf(temp * 2.0f);
}

// Compare two records by temperature key.
int record_compare(const record_t *a, const record_t *b)
{
    int key_a = temp_key(a->reading.temp_c);
    int key_b = temp_key(b->reading.temp_c);

    if (key_a < key_b) return -1;
    if (key_a > key_b) return 1;
    return 0;
}

// Create an empty store.
store_t *store_create(void)
{
    return calloc(1, sizeof(store_t));
}

// Insert a record in sorted order.
int store_insert(store_t *store, record_t record)
{
    if (store == NULL) return -1;

    if (store->count == store->capacity) {
        size_t new_capacity = store->capacity == 0 ? 8 : store->capacity * 2;

        record_t *new_records = realloc(
            store->records, new_capacity * sizeof(record_t));

        if (new_records == NULL) return -1;

        store->records = new_records;
        store->capacity = new_capacity;
    }

    size_t i = store->count;

    while (i > 0 &&
           record_compare(&record, &store->records[i - 1]) < 0) {
        store->records[i] = store->records[i - 1];
        i--;
    }

    store->records[i] = record;
    store->count++;

    return 0;
}

// Find a record using its temperature key.
const record_t *store_find(const store_t *store, float temp)
{
    if (store == NULL) return NULL;

    int key = temp_key(temp);

    for (size_t i = 0; i < store->count; i++) {
        if (temp_key(store->records[i].reading.temp_c) == key) {
            return &store->records[i];
        }
    }

    return NULL;
}

// Return the number of records.
size_t store_count(const store_t *store)
{
    return store == NULL ? 0 : store->count;
}

// Temporary height for the array version.
size_t store_height(const store_t *store)
{
    return store == NULL ? 0 : store->count;
}

// Visit records in sorted order.
void store_walk(const store_t *store,
                void (*visit)(const record_t *, void *),
                void *context)
{
    if (store == NULL || visit == NULL) return;

    for (size_t i = 0; i < store->count; i++) {
        visit(&store->records[i], context);
    }
}

// Free allocated memory.
void store_destroy(store_t *store)
{
    if (store == NULL) return;

    free(store->records);
    free(store);
}
