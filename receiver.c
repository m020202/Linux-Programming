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
#include "shared_memory.h"

int main() {
    int shmid;
    SHM_INFO *shmInfo = NULL;

    if ((shmid = shmget((key_t) 3836, sizeof(SHM_INFO) * 4, 0600 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((shmInfo = (SHM_INFO *) shmat(shmid, 0, SHM_RND)) == -1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        for (int i = 0; i < 4; ++i) {
            printf("%d", i);
            printf("%s", shmInfo[i].str_ip);
            printf("%u", shmInfo[i].int_ip);
            printf("%u", shmInfo[i].int_id);

            sleep(1);
        }
    }
}