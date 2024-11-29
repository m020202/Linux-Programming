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
#include <time.h>

int main(int argc, char **argv) {
    key_t skey;
    int semid;

    if ((skey = ftok(argv[1], atoi(argv[2]))) == (key_t) -1) {
        perror("ftok error");
        exit(1);
    }

    if ((semid = semget(skey, 2, 0660 | IPC_CREAT)) == -1) {
        perror("semget error");
        exit(1);
    }

    printf("semid = %d\n", semid);
    return 0;
}