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
#include <time.h>

int init_sem(key_t key) {
    int status = 0, semid;

    if ((semid = semget(key, 1, 0660 | IPC_CREAT)) == -1) {
        perror("semget failed");
        return -1;
    }
    else {
        union semun arg;
        arg.val = 1;
        status = semctl(semid, 0, SETVAL, arg);
    }

    return semid;
}

int main(int argc, char **argv) {

    return 0;
}