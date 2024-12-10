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
    sigset_t set1, set2;

    sigfillset(&set1);
    sigfillset(&set2);
    sigdelset(&set2, SIGINT);
    sigdelset(&set2, SIGQUIT);

    sigprocmask(SIG_SETMASK, &set1, NULL);

    sigprocmask(SIG_UNBLOCK, &set2, NULL);

    sigprocmask(SIG_UNBLOCK, &set1, NULL);

    return 0;
}