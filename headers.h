#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include <wait.h>
#include <ctype.h>
#include <wait.h>

#define MAX_BUF_LEN 1024
#define CMD_DELIMS " \t\n"
#define FNAME_LEN 20

#define BLACK  "\x1B[30m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[1;32m"
#define YELLOW  "\x1B[1;33m"
#define BLUE  "\x1B[1;34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define RESET "\x1B[0m"


void check_bg_finish();

void add_proc(int pid, char *name);

void rem_proc(int pid);

char *read_cmdline();

int parse_cmd_line(char *cmd, char **cmds);

int parse_cmd(char *cmd, char **cmd_tokens);

int parse_for_redi(char *cmd, char **cmd_tokens);

void parse_for_piping(char *cmd);

void set_prompt();

void get_home_dir();

void print_prompt();

int run_cmd(char **cmd_tokens);

void mod_cwd_rel(char *cwd);

int cd_cmd(char **cmd_tokens, char *cwd, char *base_dir);

int run_bg_cmd(char **cmd_tokens, int tokens);

void echo(char **cmd_tokens, int tokens, char *cmd);

void pwd(char **cmd_tokens);

void ls(int tokens, char **cmd_tokens);

void get_prompt_vars();

int pinfo(char **cmd_tokens);

int open_infile();

int open_outfile();

void normal_cmd(int tokens, char **cmd_tokens, char *copy);

int check_for_pipe(char *cmd);

void redi_and_pipi_cmd(char *cmd);

void jobs();

void kjob(int tokens, char **cmd_tokens);

void overkill();

void initializer();

void signal_handler(int signum);

void fg(int tokens, char **cmd_tokens);

void normal_cmd(int tokens, char **cmd_tokens, char *cmd_copy);

void redi_and_pipi_cmd(char *cmd);


struct proc_fields {
    int pid, pgid;
    char *name;
    int active;
};

typedef struct proc_fields proc_fields;

int num_jobs;

proc_fields table[MAX_BUF_LEN];

char user[MAX_BUF_LEN];
char hostname[MAX_BUF_LEN];
char base_dir[MAX_BUF_LEN];
char *pipe_cmds[MAX_BUF_LEN];
char cwd[MAX_BUF_LEN];

char *infile;
char *outfile;

int shell, shell_pgid;

int last, num_pipe;

int piping, input_redi, output_redi;

char **input_cmd_tokens;
char **output_cmd_tokens;
char **input_redi_cmd;
char **output_redi_cmd;

pid_t my_pid, my_pgid, fgpid;

int is_bg, idxi, idxo;
