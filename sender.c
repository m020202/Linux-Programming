#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"
static int time_out;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\nDo not SIGINT!\n");
    }
    else if (signo == SIGALRM) {
        time_out = 1;
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGALRM, &act, NULL);

    time_out = 0;
    alarm(5);
    while (!time_out) {
        pause();
    }

    printf("Finish!!");
    return 0;
}