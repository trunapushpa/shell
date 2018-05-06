#include "headers.h"

void pwd(char **cmd_tokens) {
    char pwd_dir[MAX_BUF_LEN];
    getcwd(pwd_dir, MAX_BUF_LEN - 1);
    if (cmd_tokens[1] == NULL) printf("%s\n", pwd_dir);
    else run_cmd(cmd_tokens);
}