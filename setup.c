#include "headers.h"

void mod_cwd_rel(char *cwd) {
    int i, j;
    for (i = 0; cwd[i] == base_dir[i] && cwd[i] != '\0' && base_dir[i] != '\0'; i++);
    if (base_dir[i] == '\0') {
        cwd[0] = '~';
        for (j = 1; cwd[i] != '\0'; j++) {
            cwd[j] = cwd[i++];
        }
        cwd[j] = '\0';
    }
}

void signal_handler(int signum) {
    if (signum == SIGINT) {
        signal(SIGINT, SIG_IGN);
        signal(SIGINT, signal_handler);
    } else if (signum == SIGCHLD) {
        int i, status, die_pid;
        while ((die_pid = waitpid(-1, &status, WNOHANG)) > 0) {
            for (i = 0; i < num_jobs; i++) {
                if (table[i].active == 0) continue;
                else if (table[i].pid == die_pid)
                    break;
            }
            if (i != num_jobs) {
                if (WIFEXITED(status))
                    fprintf(stdout, "\n%s with pid %d exited normally\n", table[i].name, table[i].pid);
                else if (WIFSIGNALED(status))
                    fprintf(stdout, "\n%s with pid %d has exited with signal\n", table[i].name, table[i].pid);
                table[i].active = 0;
            }
        }
    }
}
