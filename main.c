#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int docommand(char *command) {
    pid_t pid;

    if ((pid = fork()) < 0)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", NULL);
        perror("esxecl");
        exit(1);
    }

    wait(0);

    return 0;
}

int fatal(char *s) {
    perror(s);
    exit(1);
}

int main() {
    pid_t pid;

    switch(pid = fork()) {
        case -1:
            fatal("fork failed");
            break;
        case 0:
            execl("/bin/ls", "ls", "-l", NULL);
            fatal("exec failed");
            break;
        default:
            wait(0);
            printf("ls completed\n");
            exit(0);
    }
};

