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

void goback() {
    printf("\nInterrupted\n");
    siglongjmp(position, 1);
}
int main() {
    struct sigaction act;
    if (sigsetjmp(position, 1) == 0) {
        act.sa_handler = goback;
        sigaction(SIGINT, &act, NULL);
    }

    sleep(4);


    return 0;
}