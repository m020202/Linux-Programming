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

int init_sem(key_t semkey) {
    int semid;
    int status;
    if ((semid = semget(semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1) {
        if (errno == EEXIST) {
            semid = semget(semkey, 1, 0);
        }
    } else {
        semun arg;
        arg.val = 1;
        status = semctl(semid, 0, SETVAL, arg);
    }

    if (semid == -1 || status == -1) {
        perror("initsem failed");
        return -1;
    }

    return semid;
}

int p (int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        perror("p(semid) failed");
        exit(1);
    }

    return 0;
}

int v (int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        perror("v(semid) failed");
        exit(1);
    }

    return 0;
}

void handlesem(key_t key) {
    int semid;
    pid_t pid = getpid();

    if ((semid = init_sem(key)) == -1) exit(1);

    printf("\n%d before \n", pid);
    p(semid);

    printf("%d in c.s\n", pid);
    sleep(1);

    printf("%d leaving\n", pid);
    v(semid);

    printf("process %d out c.s\n", pid);

    exit(1);
}

int main() {
    key_t semkey = 0x200;
    for (int i = 0; i < 2; ++i) {
        if (fork() == 0)
            handlesem(semkey);
    }
    return 0;
}