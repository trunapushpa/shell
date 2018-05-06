#include "headers.h"

void jobs() {
    int i;
    for (i = 0; i < num_jobs; i++) {
        if (table[i].active == 1) {
            printf("[%d] %s [%d]\n", i, table[i].name, table[i].pid);
        }
    }
}