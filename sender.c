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
#include "pv.h"

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