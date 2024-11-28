#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define MSGSIZE 16

char *msg1 = "hello world #1";
char *msg2 = "hello world #2";
char *msg3 = "hello world #3";

int main() {
    char inBuf[MSGSIZE];
    int p[2];
    pid_t pid;

    if (pipe(p) == -1) {
        perror("pipe call: ");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork call: ");
            exit(1);
        case 0:
            close(p[0]);
            write(p[1], msg1, MSGSIZE);
            write(p[1], msg2, MSGSIZE);
            write(p[1], msg3, MSGSIZE);
            break;
        default:
            close(p[1]);
            for(int i =0; i < 3; ++i) {
                read(p[0], inBuf, MSGSIZE);
                printf("%s\n", inBuf);
            }
            wait(NULL);
    }

    return 0;
}