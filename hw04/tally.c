#include "tally.h"
#include <string.h>

// One name and its count.
typedef struct {
    char name[TALLY_LEN + 1];
    int count;
} entry_t;

// The tally details are hidden here.
struct tally {
    entry_t entries[TALLY_NAMES];
    int size;
    int in_use;
};

// Static pool of 4 tallies.
static tally_t pool[TALLY_MAX];
// Create a new tally.
tally_t *tally_create(void)
{
    for (int i = 0; i < TALLY_MAX; i++)
    {
        if (pool[i].in_use == 0)
        {
            pool[i].in_use = 1;
            pool[i].size = 0;
            return &pool[i];
        }
    }

    return NULL;
}
// Release a tally.
void tally_destroy(tally_t *tally)
{
    if (tally != NULL)
    {
        tally->in_use = 0;
        tally->size = 0;
    }
}

 // Add a name to the tally.
int tally_add(tally_t *t, const char *name)
{
    if (t == NULL || name == NULL || !t->in_use)
        return -1;

    if (strlen(name) == 0 || strlen(name) > TALLY_LEN)
        return -1;

    // Check if the name already exists.
    for (int i = 0; i < t->size; i++)
    {
        if (strcmp(t->entries[i].name, name) == 0)
        {
            t->entries[i].count++;
            return t->entries[i].count;
        }
    }
    // Check if the tally is full.
if (t->size >= TALLY_NAMES)
{
    return -1;
}

    
    // Find the correct position for the new name.
    int pos = 0;

    while (pos < t->size &&
           strcmp(t->entries[pos].name, name) < 0) {
        pos++;
    }

    // Move names to make space.
    for (int i = t->size; i > pos; i--) {
        t->entries[i] = t->entries[i - 1];
    }

    // Add the new name.
    strcpy(t->entries[pos].name, name);
    t->entries[pos].count = 1;
    t->size++;

    return 1;

}

// Return the count of a name.
int tally_count(const tally_t *t, const char *name)
{
    if (t == NULL || name == NULL || !t->in_use)
        return 0;

    for (int i = 0; i < t->size; i++)
    {
        if (strcmp(t->entries[i].name, name) == 0)
        {
            return t->entries[i].count;
        }
    }

    return 0;
}

 // Return the number of different names.
int tally_size(const tally_t *t)
{
    if (t == NULL || !t->in_use)
    {
        return 0;
    }

    return t->size;
}

 // Print names in alphabetical order.
void tally_print(const tally_t *t, FILE *out)
{
    if (t == NULL || out == NULL || !t->in_use)
        return;

    int order[TALLY_NAMES];

    for (int i = 0; i < t->size; i++)
        order[i] = i;

    // Sort names alphabetically.
    for (int i = 0; i < t->size; i++)
    {
        for (int j = i + 1; j < t->size; j++)
        {
            if (strcmp(t->entries[order[i]].name,
                       t->entries[order[j]].name) > 0)
            {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    // Print each name and its count.
    for (int i = 0; i < t->size; i++)
    {
        int k = order[i];
        fprintf(out, "%s %d\n",
                t->entries[k].name,
                t->entries[k].count);
    }
}
