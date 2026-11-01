#ifndef REPORT_H
#define REPORT_H
#include "store.h"
#include <stdio.h>
typedef struct {long ticks[STATE_COUNT];long total;} report_t;
void report_calculate(const store_t *store,report_t *result);
void report_print(FILE *out,const report_t *report);
#endif
