#include "headers.h"

void checkUsrPerms(struct stat a);

void checkGroupPerms(struct stat a);

void checkOthersPerms(struct stat a);

char r = 'r', w = 'w', x = 'x', d = '-', sp = ' ';

void ls(int tokens, char **cmd_tokens) {
    int i, l = 0, a = 0, dir = 0;
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    DIR *k;
    struct dirent *strk;
    struct stat b;
    char cur_fd[10000], prefix[10000];

    for (i = 1; cmd_tokens[i] != NULL; i++) {
        if (!strcmp(cmd_tokens[i], "-l"))
            l = 1;
        else if (!strcmp(cmd_tokens[i], "-a"))
            a = 1;
        else if (!strcmp(cmd_tokens[i], "-la") || !strcmp(cmd_tokens[i], "-al")) {
            l = 1;
            a = 1;
        } else {
            dir = i;
        }
    }

    if (dir != 0) {
        if (cmd_tokens[dir][0] != '/') {
            strcpy(prefix, cwd);
            strcat(prefix, "/");
            strcat(prefix, cmd_tokens[dir]);
            stat(prefix, &b);
            if (!S_ISDIR(b.st_mode)) {
                fprintf(stderr, RED "ERROR: No such file or directory\n" RESET);
                return;
            }
            k = opendir(prefix);
        } else {
            stat(prefix, &b);
            if (!S_ISDIR(b.st_mode)) {
                fprintf(stderr, RED "ERROR: No such file or directory\n" RESET);
                return;
            }
            k = opendir(cmd_tokens[dir]);
            strcpy(prefix, cmd_tokens[dir]);
        }
    } else {
        k = opendir(cwd);
        strcpy(prefix, cwd);
    }

    while ((strk = readdir(k)) != NULL) {
        if ((strk->d_name[0] != '.') || ((a == 1) && (strk->d_name[0] == '.'))) {
            strcpy(cur_fd, prefix);
            strcat(cur_fd, "/");
            strcat(cur_fd, strk->d_name);
            stat(cur_fd, &b);
            if (l == 1) {
                if (S_ISDIR(b.st_mode))
                    fprintf(stdout, "d");
                else if (S_ISREG(b.st_mode))
                    fprintf(stdout, "-");
                checkUsrPerms(b);
                checkGroupPerms(b);
                checkOthersPerms(b);
                printf("%5zu", b.st_nlink);
                struct passwd *pw = getpwuid(b.st_uid);
                struct group *gr = getgrgid(b.st_gid);
                printf("  %s  %s ", pw->pw_name, gr->gr_name);
                printf("%9zu  ", b.st_size);
                char *time = ctime(&b.st_mtime);
                time[strlen(time) - 1] = 0;
                printf("%s  ", time);
            }
            fprintf(stdout, "%s\n", strk->d_name);
        }
    }
}

void checkUsrPerms(struct stat a) {
    fprintf(stdout, "%c", (a.st_mode & S_IRUSR) ? r : d);
    fprintf(stdout, "%c", (a.st_mode & S_IRUSR) ? w : d);
    fprintf(stdout, "%c", (a.st_mode & S_IRUSR) ? x : d);
}

void checkGroupPerms(struct stat a) {
    fprintf(stdout, "%c", (a.st_mode & S_IRGRP) ? r : d);
    fprintf(stdout, "%c", (a.st_mode & S_IRGRP) ? w : d);
    fprintf(stdout, "%c", (a.st_mode & S_IRGRP) ? x : d);
}

void checkOthersPerms(struct stat a) {
    fprintf(stdout, "%c", (a.st_mode & S_IROTH) ? r : d);
    fprintf(stdout, "%c", (a.st_mode & S_IROTH) ? w : d);
    fprintf(stdout, "%c", (a.st_mode & S_IROTH) ? x : d);
    write(STDOUT_FILENO, &sp, 1);
}