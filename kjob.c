#include "headers.h"

void kjob(int tokens, char **cmd_tokens) {
    if (tokens != 3) {
        fprintf(stderr, "Invalid usage of kjob!\n");
        return;
    }
    int job_num = atoi(cmd_tokens[1]);
    if (table[job_num].active == 1) {
        if (kill(table[job_num].pid, atoi(cmd_tokens[2])) <
            0)                 /* For sending signal mentioned to job mentioned */
            fprintf(stderr, "Signal not sent!\n");
    } else fprintf(stderr, "Job not found\n");
}