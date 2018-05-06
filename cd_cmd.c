#include "headers.h"

int cd_cmd(char **cmd_tokens, char *cwd, char *base_dir) {
    if (cmd_tokens[1] == NULL || strcmp(cmd_tokens[1], "~\0") == 0 || strcmp(cmd_tokens[1], "~/\0") == 0) {
        chdir(base_dir);
        strcpy(cwd, base_dir);
        mod_cwd_rel(cwd);
    } else if (chdir(cmd_tokens[1]) == 0) {
        getcwd(cwd, MAX_BUF_LEN);
        mod_cwd_rel(cwd);
        return 0;
    } else {
        perror("Error executing cd command");
    }
}