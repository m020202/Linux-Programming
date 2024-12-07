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
    SHM_INFOS *shmInfos = NULL;

    shmid = shmget((key_t) 3836, sizeof(SHM_INFOS) * SHM_INFO_COUNT, 0600 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        return 0;
    }
    void *shared_memory = NULL;
    shared_memory = shmat(shmid, 0, SHM_RND);

    if (shared_memory == (void *) NULL) {
        perror("shmat");
        return 0;
    }

    shmInfos = (SHM_INFOS *) shared_memory;

    while(1) {
        for (int i = 0; i < SHM_INFO_COUNT; ++i) {
            printf("---[%d] shared info ---\n", i);
            printf("String IP[%s]\n", shmInfos[i].str_ip);
            printf("String IP[%u]\n", shmInfos[i].int_ip);
            printf("String IP[%u]\n", shmInfos[i].int_id);
            sleep(1);
        }
    }
}