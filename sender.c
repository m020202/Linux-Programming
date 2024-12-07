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

int main() {
    int shmid;
    SHM_INFOS *shmInfos = NULL;

    if ((shmid = shmget((key_t) 3836, sizeof(SHM_INFOS) * 4, IPC_CREAT | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }

    void *shared_mem = NULL;
    if ((shared_mem = shmat(shmid, 0, SHM_RND)) ==  (void *)-1) {
        perror("shmat");
        exit(1);
    }

    shmInfos = (SHM_INFOS *) shared_mem;

    while (1) {
        for (int i = 0; i < SHM_INFO_COUNT; ++i) {
            snprintf(shmInfos[i].str_ip, sizeof(shmInfos[i].str_ip), "1.1.1.%d", i);
            shmInfos[i].int_ip = 12891010 + i;
            shmInfos[i].int_id = 128 + i;
        }
    }
}