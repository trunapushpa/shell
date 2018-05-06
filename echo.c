#include "headers.h"

void echo(char **cmd_tokens, int tokens, char *cmd) {
    if (tokens > 1 && cmd_tokens[1][0] == '-') {
        run_cmd(cmd_tokens);
        return;
    }
    int i, len = 0, in_quote = 0, flag = 0;
    char buf[MAX_BUF_LEN] = "\0";
    for (i = 0; isspace(cmd[i]); i++);
    if (i == 0) i = 5;
    else i += 4;
    for (; cmd[i] != '\0'; i++) {
        if (cmd[i] == '"') {
            in_quote = 1 - in_quote;
        } else if (in_quote == 0 && (isspace(cmd[i])) && flag == 0) {
            flag = 1;
            if (len > 0) buf[len++] = ' ';
        } else if (in_quote == 1 || !isspace(cmd[i])) buf[len++] = cmd[i];
        if (!isspace(cmd[i]) && flag == 1) flag = 0;
    }
    if (in_quote == 1) {
        fprintf(stderr, "Missing quotes\n");
        return;
    } else printf("%s\n", buf);
}