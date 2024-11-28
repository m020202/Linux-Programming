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
    int p[2], i;
    pid_t pid;

    if (pipe(p) == -1) {
        perror("pipe call: ");
        exit(1);
    }

    write(p[1], msg1, MSGSIZE+1);
    write(p[1], msg2, MSGSIZE+1);
    write(p[1], msg3, MSGSIZE+1);

    for (i = 0; i < 3; ++i) {
        read(p[0], inBuf, MSGSIZE+1);
        printf("%s\n", inBuf);
    }

    return 0;
}