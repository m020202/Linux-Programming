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
#include <setjmp.h>
#include "shared_memory.h"

static int time_out;
static char answer[100];

void sig_handler(int signo) {
    time_out = 1;
}
int main() {
    int i;
    time_out = 0;
    struct sigaction act, oact;
    act.sa_handler = sig_handler;
    sigaction(SIGALRM, &act, &oact);
    time_out = 0;

    for (i = 0; i < 5; ++i) {
        printf("\nEnter the string: ");
        alarm(3);
        scanf("%s", answer);
        alarm(0);
        if (!time_out) break;
    }

    if (i == 5)
        printf("\nFALSE!!\n");
    else
        printf("\nTRUE!!\n");

    return 0;
}