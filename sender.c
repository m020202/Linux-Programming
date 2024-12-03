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
#include "pv.h"

#define SEMPERM 0600
typedef union semun {
    int val;
    struct semtid_ds *buf;
    unsigned short *array;
};

int P(int semid) {
    struct sembuf p_buf;
    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;

    if (semop(semid, &p_buf, 1) == -1) {
        perror("semop failed: ");
        return -1;
    }

    return 0;

}

int V(int semid) {
    struct sembuf v_buf;
    v_buf.sem_num = 0;
    v_buf.sem_op = 1;
    v_buf.sem_flg = SEM_UNDO;

    if (semop(semid, &v_buf, 1) == -1) {
        perror("semop failed: ");
        return -1;
    }

    return 0;
}

int main() {
    int shmId;
    int i;
    struct SHM_INFOS *shm_info = NULL;

    if ((shmId = shmget((key_t) 3836, sizeof(struct SHM_INFOS) * SHM_INFO_COUNT, IPC_CREAT | 0666)) == -1) {
        perror("shmget failed: ");
        exit(0);
    }

    if ((shm_info = (struct SHM_INFOS *) shmat(shmId, 0, 0)) == NULL) {
        perror("shmat failed: ");
        exit(0);
    }

    while(1) {
        for(i = 0; i < SHM_INFO_COUNT; ++i) {
            snprintf(shm_info[i].str_ip, sizeof(shm_info[i].str_ip), "1.1.1.%d", i);
            shm_info[i].int_id = 128 + i;
            shm_info[i].int_ip = 12891010 + i;
        }
    }
}