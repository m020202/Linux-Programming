#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define MSGSIZE 6

int join (char *com1[], char *com2[]) {
    int p[2], status;

    switch (fork()) {
        case -1:
            return -1;
        case 0:
            break;
        default:
            wait(&status);
            return status;
    }

    if (pipe(p) == -1)
        return -1;

    switch (fork()) {
        case -1:
            return -1;
        case 0:
            dup2(p[1], 1);
            close(p[0]);
            close(p[1]);
            execvp(com1[0], com1);
            return -1;
        default:
            dup2(p[0], 0);
            close(p[0]);
            close(p[1]);
            execvp(com2[0], com2);
            return -1;
    }
}

int main() {
    char *one[4] = {"ls", "-l", "/usr/lib", NULL};
    char *two[3] = {"grep", "^d", NULL};
    int ret;

    ret = join(one, two);
    printf("join returned %d\n", ret);
    exit(0);
}
