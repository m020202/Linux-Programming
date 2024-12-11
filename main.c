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
#include <setjmp.h>
#include "shared_memory.h"
#define MAXSIZE 64

int time_out;

void sig_handler(int signo) {
    if (signo == SIGALRM) {
        time_out = 1;
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGALRM, &act, NULL);

    char buf[10];

    for (int i = 0; i < 3; ++i) {
        printf("COUNT #%d\n", i);
        time_out = 0;
        alarm(2);
        scanf("%s", buf);
        alarm(0);
        if (!time_out) {
            break;
        }
    }

    if (!time_out)
        printf("%s\n", buf);
    else
        printf("TIME OUT !!\n");

    return 0;
}
