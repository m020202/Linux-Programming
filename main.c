#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shared_memory.h"

static int time_out;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n DO not ctrl C!!\n");
    }
    else if (signo == SIGALRM) {
        time_out = 1;
    }
}

int main() {
    int pid;
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);

    switch (pid = fork()) {
        case -1:
            perror("fork err");
            exit(1);
        case 0:
            printf("This is a child!\n");
            time_out = 0;
            alarm(5);
            while (!time_out) {
                pause();
            }
            break;
        default:
            act.sa_handler = SIG_IGN;
            sigaction(SIGINT, &act, NULL);
            wait(NULL);
            printf("This is a parent!\n");
            act.sa_handler = sig_handler;
            sigaction(SIGINT, &act, NULL);
            time_out = 0;
            alarm(2);
            while (!time_out) {
                pause();
            }
            break;
    }
    return 0;
}