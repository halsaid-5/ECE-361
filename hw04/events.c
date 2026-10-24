
#include <stdio.h>
#include <string.h>
#include "tally.h"

int main(void)
{
    tally_t *t = tally_create();

    if (t == NULL) {
        printf("Could not create tally\n");
        return 1;
    }

    char line[256];
    int skipped = 0;

    // Read names from input.
    while (fgets(line, sizeof(line), stdin) != NULL) {

        // Remove newline.
        line[strcspn(line, "\n")] = '\0';

        // Ignore blank lines and comments.
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        // Count each name.
        if (tally_add(t, line) == -1) {
            skipped++;
        }
    }

    tally_print(t, stdout);
    printf("names: %d, lines skipped: %d\n",
           tally_size(t), skipped);

    tally_destroy(t);
    return 0;
}
