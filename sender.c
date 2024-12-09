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
    int shmId;
    SHM_INFO *shmInfo = NULL;

    if ((shmId = shmget((key_t) 3836, sizeof(SHM_INFO) * 4, 0600 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((shmInfo = (SHM_INFO *) shmat(shmId, 0, SHM_RND)) == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        for (int i = 0; i < 4; ++i) {
            snprintf(shmInfo[i].str_ip, sizeof(shmInfo[i].str_ip), "1.1.1.%d", i);
            shmInfo[i].int_ip = 12891010 + i;
            shmInfo[i].int_id = 128 + i;
        }
    }
}