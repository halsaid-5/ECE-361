#ifndef AUX_H
#define AUX_H
#include <stddef.h>
typedef struct {long tick;char name[32];} history_event_t;
typedef struct aux aux_t;
aux_t *aux_create(void);
int aux_push(aux_t *stack,history_event_t event);
int aux_pop(aux_t *stack,history_event_t *event);
int aux_peek(const aux_t *stack,history_event_t *event);
size_t aux_count(const aux_t *stack);
int aux_is_empty(const aux_t *stack);
void aux_destroy(aux_t *stack);
#endif
