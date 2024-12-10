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

void sig_handler(int signo, siginfo_t *siginfo, void *p) {
    printf("%d Receive from %d\n", getpid(), siginfo->si_pid);
}

int main() {
    struct sigaction act;
    act.sa_sigaction = sig_handler;
    sigaction(SIGUSR1, &act, NULL);
    pid_t pid;

    switch(pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            for(int i = 0; i < 5; ++i) {
                sleep(1);
                kill(getppid(), SIGUSR1);
                pause();
            }
        default:
            for(int i = 0; i < 5; ++i) {
                pause();
                sleep(1);
                kill(pid, SIGUSR1);
            }
    }

    return 0;
}