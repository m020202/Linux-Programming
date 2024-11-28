#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

void sig_handler(int sig, siginfo_t *siginfo, void  *flag){
    printf("[%d] send me %d\n", siginfo->si_pid, sig);
}

int main() {
    pid_t pid, ppid;
    static struct sigaction act;
    act.sa_sigaction = sig_handler;
    sigaction(SIGUSR1, &act, NULL);

    switch (pid = fork()) {
        case -1:
            perror("fork error: ");
            exit(1);
        case 0:
            ppid = getppid();
            for (int i = 0; i < 10; ++i) {
                sleep(1);
                kill(ppid, SIGUSR1);
                pause();
            }
        default:
            for (int i = 0; i < 10; ++i) {
                pause();
                sleep(1);
                kill(pid, SIGUSR1);
            }
    }
}