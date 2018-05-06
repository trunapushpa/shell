#include "headers.h"

void fg(int tokens, char **cmd_tokens) {
    if (tokens != 2) {
        fprintf(stderr, "Invalid usage of fg");
        return;
    }

    int i, job_num = atoi(cmd_tokens[1]), status;
    if (table[job_num].active == 0) {
        printf("No such job exists\n");
        return;
    }
    if (table[job_num].active == 1) {
        int pid = table[job_num].pid, pgid;
        pgid = getpgid(pid);
        tcsetpgrp(shell, pgid);

        fgpid = pgid;
        if (killpg(pgid, SIGCONT) < 0)
            perror("Can't get in foreground!\n");
        waitpid(pid, &status, WUNTRACED);
        if (!WIFSTOPPED(status)) {
            table[job_num].active = 0;
            fgpid = 0;
        }
        tcsetpgrp(shell, my_pid);
    } else fprintf(stderr, "No job found\n");
}
