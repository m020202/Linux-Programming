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
#include"pv.h"

int p(int semid) {
    struct sembuf p_buf;

    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;

    if (semop(semid, &p_buf, 1) == -1) {
        perror("p(semid) failed");
        return -1;
    }

    return 0;
}

int v(int semid) {
    struct sembuf v_buf;

    v_buf.sem_num = 0;
    v_buf.sem_op = 1;
    v_buf.sem_flg = SEM_UNDO;

    if (semop(semid, &v_buf, 1) == -1) {
        perror("v(semid) failed");
        return -1;
    }

    return 0;
}


void handleSem(key_t key) {
    int semid;
    int status = 0;

    pid_t pid = getpid();
    if ((semid = semget(key, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1) {
        if (errno == EEXIST)
            semid = semget(key, 1, 0);
    }
    else {
        semun arg;
        arg.val = 1;
        status = semctl(semid, 0, SETVAL, arg);
    }

    printf("\nprocess %d before critical section\n", pid);
    p(semid);
    printf("process %d in critical section\n", pid);

    sleep(10);

    printf("process %d leaving critical section\n", pid);
    v(semid);
    printf("processs %d exiting\n", pid);
}

int main()
{
    key_t semkey = 0x200;
    for (int i = 0; i < 3; ++i) {
        if (fork() == 0) handleSem(semkey);
    }
}

