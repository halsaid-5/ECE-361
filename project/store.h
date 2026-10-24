#ifndef STORE_H
#define STORE_H

#include <stddef.h>
#include <stdint.h>
#include "sensor.h"
#include "fsm.h"

// One record from the parking gate.
typedef struct {
    reading_t reading;
    state_t state;
    uint32_t status;
} record_t;

// Store details are hidden in store.c.
typedef struct store store_t;

// Compare records by temperature.
int record_compare(const record_t *a, const record_t *b);

// Store functions.
store_t *store_create(void);
int store_insert(store_t *store, record_t record);
const record_t *store_find(const store_t *store, float temp);
size_t store_count(const store_t *store);
size_t store_height(const store_t *store);
void store_walk(const store_t *store,
                void (*visit)(const record_t *, void *),
                void *context);
void store_destroy(store_t *store);

#endif
