#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "msg_header.h"

int msgid;

void sig_handler(int signo) {
    msgctl(msgid, IPC_RMID, 0);
    printf("\nGraceful Exit!");
    exit(0);
}

int P(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf,1) == -1) {
        perror("P(semid) failed");
        exit(1);
    }

    return 0;
}

int V(int semid) {
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1) {
        perror("V(semid) failed");
        exit(1);
    }

    return 0;
}

void handleSem(key_t key) {
    int semid;
    pid_t pid = getpid();
    if ((semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644)) == -1) {
        if (errno == EEXIST)
            semid = semget(key, 1, 0);
    }
    else {
        union semun arg;
        arg.val = 1;
        semctl(semid, 0,SETVAL, arg);
    }

    printf("\nProcess %d before c s\n", pid);
    P(semid);

    printf("Process %d in c s\n", pid);

    sleep(1);

    V(semid);
    printf("\nProcess %d after c s\n", pid);
    exit(1);

}

int main() {
    key_t key = 0x200;

    for (int i = 0; i < 2; ++i) {
        if (fork() == 0) {
            handleSem(key);
        }
    }

}