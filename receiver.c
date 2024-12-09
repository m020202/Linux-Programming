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
    shmctl(shmid, IPC_RMID, 0);
    printf("\nGraceful Exit!");
    exit(1);
}

int main() {
    SHM_INFO *shmInfo = NULL;
    struct sigaction act;

    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);

    if ((shmid = shmget((key_t) 3836, sizeof(SHM_INFO) * 4, 0600 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((shmInfo = (SHM_INFO *) shmat(shmid, 0, SHM_RND)) == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    while(1) {
        for (int i = 0; i < 4; ++i) {
            printf("%d\n", i);
            printf("%s\n", shmInfo[i].str_ip);
            printf("%u\n", shmInfo[i].int_ip);
            printf("%u\n", shmInfo[i].int_id);

            sleep(1);
        }
    }
}