#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


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

