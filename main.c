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
#include <sys/sem.h>
#include <sys/shm.h>
#include <setjmp.h>
#include "shared_memory.h"

int ntimes = 0;

void p_action(int sig) {
    printf("Parent caught signal #%d\n", ++ntimes);
}

void c_action(int sig) {
    printf("Child caught signal #%d\n", ++ntimes);
}

int main() {
    struct sigaction p_act, c_act;
    p_act.sa_handler = p_action;
    c_act.sa_handler = c_action;
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            sigaction(SIGUSR1, &c_act, NULL);
            while (1) {
                sleep(1);
                kill(getppid(), SIGUSR1);
                pause();
            }
        default:
            sigaction(SIGUSR1, &p_act, NULL);
            while (1) {
                pause();
                sleep(1);
                kill(pid, SIGUSR1);
            }
    }
}