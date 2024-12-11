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

typedef union _semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arr;
} semun;

int initsem(key_t semkey) {
    int semid;

    if ((semid = semget(semkey, 1, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
        if (errno == EEXIST)
            semid = semget(semkey, 1, 0);
        else {
            perror("semget");
            return -1;
        }
    }
    else {
        semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    }

    return semid;
}

int P (int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return 0;
}

int V (int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return 0;
}


int main(int argc, char** argv) {
    int shmid;
    int semid;
    key_t key = (key_t) 0x200;

    if ((semid = initsem(key)) == -1) {
        exit(1);
    }

    if ((shmid = shmget((key_t) 0x20, sizeof(SHM_INFOS) * SHM_INFO_COUNT, 0600 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    SHM_INFOS *shmInfos = NULL;

    shmInfos = (SHM_INFOS *) shmat(shmid, 0, SHM_RND);
    if (shmInfos == (SHM_INFOS *) -1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        for (int i = 0; i < SHM_INFO_COUNT; ++i) {
            P(semid);
            snprintf(shmInfos[i].str_ip, sizeof(shmInfos[i].str_ip), "1.1.1.%d", i);
            shmInfos[i].int_ip = 12891010 + i;
            shmInfos[i].int_id = 128 + i;
            V(semid);
        }
    }

    return 0;
}