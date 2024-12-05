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

static int shmid1, shmid2, semid;

void getseg(struct databuf **p1, struct databuf **p2) {
    if ((shmid1 = shmget(SHMKEY1, sizeof(struct databuf), IPC_CREAT | 0600 | IPC_EXCL)) == -1) {
        perror("semget");
        exit(1);
    }
    if ((shmid2 = shmget(SHMKEY2, sizeof(struct databuf), IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((*p1 = (struct databuf *) shmat(shmid1, 0, 0)) == (struct databuf *)-1) {
        perror("shmat");
        exit(1);
    }

    if ((*p2 = (struct databuf *) shmat(shmid2, 0, 0)) == (struct databuf *) -1) {
        perror("shmat");
        exit(1);
    }
}

int getsem() {
    semun x;
    x.val = 0;

    if ((semid = semget(SEMKEY, 2, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
        if (errno == EEXIST)
            semid = semget(SEMKEY, 1, 0);
    }
    else {
        semctl(semid, 0, SETVAL, x);
        semctl(semid, 1, SETVAL, x);
    }

    return semid;
}

void remobj() {
    if (shmctl(shmid1, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    if (shmctl(shmid2, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    if (shmctl(semid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}
int main() {
    union semun ar
    return 0;
}