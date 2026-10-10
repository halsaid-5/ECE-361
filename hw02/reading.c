#include "reading.h"

#define LINE_LEN 128

/* Reads sensor data from a file.
 * Takes a file, arrays, maximum size, and skipped count.
 * Returns the number of valid readings.
 * Assumes the arrays have enough space.
 */
int reading_read(FILE *input, int ticks[],
                 float temps[], float hums[],
                 int max_readings, int *skipped) {

    char line[LINE_LEN];
    int count = 0;
    *skipped = 0;

    while (fgets(line, sizeof line, input) != NULL) {
        int i = 0;

        /* Skip spaces at the beginning */
        while (line[i] == ' ' || line[i] == '\t')
            i++;

        /* Ignore empty lines and comments */
        if (line[i] == '\n' || line[i] == '\0'
            || line[i] == '#')
            continue;

        /* Stop when the arrays are full */
        if (count == max_readings) {
            fprintf(stderr,
                    "warning: more than %d readings, the rest are ignored\n",
                    max_readings);
            break;
        }

        /* Read three numbers */
        if (sscanf(line, "%d %f %f",
                   &ticks[count], &temps[count],
                   &hums[count]) == 3) {
            count++;
        } else {
            (*skipped)++;
        }
    }

    return count;
}
