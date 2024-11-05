#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_action(int sig, siginfo_t *siginfo, void* param2) {
    printf("%d receive sig_num:%d from %d\n", getpid(), sig, siginfo->si_pid);
}

int main() {
    int pid;

    struct sigaction p_act, c_act;
    p_act.sa_sigaction = sig_action;
    p_act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &p_act, 0);

    if ((pid = fork()) == -1) {
        perror("fork error: ");
        return -1;
    }

    if (pid > 0) {
        for (int i = 0; i < 10; ++i) {
            pause();
            sleep(1);
            kill(pid, SIGUSR1);
        }
    }
    else {
        c_act.sa_sigaction = sig_action;
        c_act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &c_act, 0);

        for (int i = 0; i < 10; ++i) {
            kill(getppid(), SIGUSR1);
            pause();
            sleep(1);
        }
    }

    return 0;
}