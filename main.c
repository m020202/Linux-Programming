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

sigjmp_buf position;

void sig_handler(int signo) {
    printf("\nSIGINT caught\n");
    siglongjmp(position, 1);
}

int main() {
    struct sigaction act;
    act.sa_handler = sig_handler;

    sigaction(SIGINT, &act, NULL);
    printf("SIGINT start\n");

    int tmp = sigsetjmp(position, 1);
    printf("SIGSETJMP RETURN!!!\n");

    for (int i = 0; i < 4; ++i) {
        printf("sleep call #%d\n", i);
        sleep(2);
    }

    return 0;
}