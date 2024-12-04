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
#include "share_memory.h"

int main() {
    int shmId;
    int i;
    struct SHM_INFOS *shm_inf = NULL;

    shmId = shmget((key_t) 3836, sizeof(struct SHM_INFOS) * SHM_INFO_COUNT, 0666 | IPC_CREAT);
    if (shmId == -1) {
        perror("shmget failed: ");
        exit(0);
    }

    shm_inf = (struct SHM_INFOS *) shmat(shmId, 0, 0);
    if (shm_inf == -1) {
        perror("shmat attach is failed: ");
        exit(0);
    }


    while (1) {
        for (i = 0; i < SHM_INFO_COUNT; ++i) {
            fprintf(stderr, "--- [%d] shared info ---\n", i);
            fprintf(stderr, "String IP[%s]\n", shm_inf[i].str_ip);
            fprintf(stderr, "String IP[%u]\n", shm_inf[i].int_ip);
            fprintf(stderr, "String IP[%u]\n", shm_inf[i].int_id);
        }

        sleep(1);
    }

}