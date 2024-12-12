#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"
#define BUFSIZE 64

int count;
void sig_handler(int signo) {
    printf("write blocked after %d characters\n", count);
    exit(1);
}

int main(int argc, char **argv) {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGALRM, &act, NULL);

    int p[2];

    if (pipe(p) == -1) {
        perror("pipe");
        exit(1);
    }

    int buf_size = fpathconf(p[1], _PC_PIPE_BUF);
    printf("MAX SIZE OF BUF: %d\n", buf_size);

    char c = 'x';
    while (1) {
        alarm(3);
        write(p[1], &c, 1);
        alarm(0);
        count++;
        if ((count % 1024) == 0) {
            printf("%d charcters in pipe\n", count);
        }
    }
    return 0;
}