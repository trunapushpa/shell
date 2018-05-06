#include "headers.h"

void overkill() {
    int i;
    for (i = 0; i < num_jobs; i++) {
        if (table[i].active == 1) {
            if (kill(table[i].pid, SIGKILL) < 0)                           /* Kill all jobs */
                perror("Error killing process!\n");
        }
    }
}