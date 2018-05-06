#include "headers.h"

int main() {
    shell = STDERR_FILENO;

    num_jobs = 0;

    input_cmd_tokens = malloc((sizeof(char) * MAX_BUF_LEN) * MAX_BUF_LEN);
    output_cmd_tokens = malloc((sizeof(char) * MAX_BUF_LEN) * MAX_BUF_LEN);

    if (isatty(shell)) {
        while (tcgetpgrp(shell) != (shell_pgid = getpgrp()))
            kill(shell_pgid, SIGTTIN);
    }

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    my_pid = getpid();
    my_pgid = getpid();
    setpgid(my_pid, my_pgid);
    tcsetpgrp(shell, my_pgid);

    getlogin_r(user, MAX_BUF_LEN - 1);
    gethostname(hostname, MAX_BUF_LEN - 1);
    getcwd(base_dir, MAX_BUF_LEN - 1);
    strcpy(cwd, base_dir);
    mod_cwd_rel(cwd);
    while (1) {
        if (signal(SIGCHLD, signal_handler) == SIG_ERR)
            perror("can't catch SIGCHLD");
        if (signal(SIGINT, signal_handler) == SIG_ERR)
            perror("can't catch SIGINT!");

        print_prompt();

        int i, j;

        char **cmds = malloc((sizeof(char) * MAX_BUF_LEN) * MAX_BUF_LEN);

        for (j = 0; j < MAX_BUF_LEN; j++) {
            cmds[j] = '\0';
        }

        char *cmdline = read_cmdline();
        int num_cmds = parse_cmd_line(cmdline, cmds);

        for (i = 0; i < num_cmds; i++) {
            infile = outfile = NULL;
            is_bg = 0, num_pipe = 0;
            char *cmd_copy = strdup(cmds[i]);

            char **cmd_tokens = malloc((sizeof(char) * MAX_BUF_LEN) * MAX_BUF_LEN);
            for (j = 0; j < MAX_BUF_LEN; j++) cmd_tokens[j] = '\0';

            if (check_for_pipe(strdup(cmds[i])) == -1) {
                if (input_redi == 1 || output_redi == 1) {
                    normal_cmd(parse_for_redi(strdup(cmd_copy), cmd_tokens), cmd_tokens, cmd_copy);
                } else {
                    int tokens = parse_cmd(strdup(cmds[i]), cmd_tokens);
                    normal_cmd(tokens, cmd_tokens, cmd_copy);
                }
            } else redi_and_pipi_cmd(cmds[i]);
        }
        if (cmds) free(cmds);
        if (cmdline) free(cmdline);
    }
    return 0;
}
