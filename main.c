#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int docommand(char *command) {
    pid_t pid;

    if ((pid = fork()) < 0)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, NULL);
        perror("esxecl");
        exit(1);
    }

    wait(0);

    return 0;
}

int main() {
    docommand("echo hello world");
};

