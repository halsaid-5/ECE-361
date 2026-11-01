#ifndef STORE_H
#define STORE_H
#include "sensor.h"
#include "fsm.h"
#include <stddef.h>
typedef struct {reading_t reading;state_t state;uint32_t status;} record_t;
typedef struct store store_t;
typedef void (*record_visit_fn)(const record_t *record,void *context);
int record_compare(const record_t *a,const record_t *b);
store_t *store_create(void);
int store_insert(store_t *store,record_t record);
const record_t *store_find(const store_t *store,float temperature);
void store_walk(const store_t *store,record_visit_fn visit,void *context);
size_t store_count(const store_t *store);
size_t store_height(const store_t *store);
void store_destroy(store_t *store);
#endif
