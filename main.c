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

void handler(int signo) {
    printf("\nCATCHINT: signo = %d\n", signo);
    printf("CATCHINT: returning\n\n");
}

int main() {
    struct sigaction act, oact;
    act.sa_handler = handler;
    sigfillset(&act.sa_mask);
    sigaction(SIGINT, &act, &oact);

    printf("sleep call #1\n");
    sleep(2);
    printf("sleep call #2\n");
    sleep(2);

    sigaction(SIGINT, &oact, NULL);
    printf("sleep call #3\n");
    sleep(2);
    return 0;
}