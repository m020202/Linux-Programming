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


int main() {
    int semid;

    if ((semid = semget((key_t) 3836, 1, 0600 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    } else {
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    }
    return 0;
}