#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void sig_handler(int sig, siginfo_t *siginfo, void* param2) {
    printf("[Parent: %d]: receive a signal from child %d\n\n", getpid(), siginfo->si_pid);
}


int main() {
    pid_t pid;
    static struct sigaction act;
    act.sa_sigaction = sig_handler;
    act.sa_flags = SA_SIGINFO;
    sigfillset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);

    int i = 0;
    while((pid = fork())) {
        printf("[Parent: %d]: create child %d\n", getpid(), pid);
        sleep(3);
        if (i++ == 3)
            break;
    }

    if (pid > 0) {
//        getchar();
    }
    else {
        sleep(2);
        kill(getppid(), SIGUSR1);  // 자식은 부모에게 SIGUSR1 신호를 보냄
    }

    return 0;
}
