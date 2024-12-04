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
    int shmid;
    shmid = shmget((key_t) 3836, sizeof(SHM_INFOS *) * SHM_INFO_COUNT, 0600 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget failed: ");
        exit(1);
    }
    SHM_INFOS *info = NULL;
    void *shared_memory = NULL;
    shared_memory = shmat(shmid, 0, 0);
    if (shared_memory == (void *) -1) {
        perror("shmat attach is failed: ");
        exit(1);
    }

    info = (SHM_INFOS *) shared_memory;

    while (1) {
        for (int i = 0; i < SHM_INFO_COUNT; ++i) {
            printf("---[%d] shared info ---", i);
            printf("String IP[%s]\n", info[i].str_ip);
            printf("String IP[%u]\n", info[i].int_ip);
            printf("String IP[%u]\n", info[i].int_id);
        }

        sleep(1);
    }
}