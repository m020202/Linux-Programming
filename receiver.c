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
int shmid;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\nGradeful Exit!\n");
        shmctl(shmid, IPC_RMID, 0);
        exit(1);
    }
}

int main(int argc, char **argv) {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);

    if ((shmid = shmget((key_t) 0x20, sizeof(SHM_INFOS) * SHM_INFO_COUNT, 0600 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    void *shared_memory = shmat(shmid, 0, SHM_RND);
    if (shared_memory == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    SHM_INFOS *shm_info = (SHM_INFOS *) shared_memory;

    while (1) {
        for (int i = 0; i < SHM_INFO_COUNT; ++i) {
            printf("---[%d]---\n", i);
            printf("String IP[%s]\n", shm_info[i].str_ip);
            printf("String IP[%u]\n", shm_info[i].int_id);
            printf("String IP[%u]\n", shm_info[i].int_ip);
            sleep(1);
        }
    }
    return 0;
}