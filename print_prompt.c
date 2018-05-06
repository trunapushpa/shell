#include "headers.h"

void print_prompt() {
    fprintf(stdout, YELLOW "<" RESET);
    fprintf(stdout, GREEN "%s@%s:" RESET, user, hostname);
    fprintf(stdout, BLUE "%s" RESET, cwd);
    fprintf(stdout, YELLOW "> " RESET);
}