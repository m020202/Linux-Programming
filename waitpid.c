#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status, exit_status;

    if ((pid = fork()) < 0)
        perror("fork failed");

    if (pid == 0) {
        sleep(4);
        exit(5);
    }

    int ret_pid;
    while ((ret_pid = waitpid(pid, &status, WNOHANG)) == 0) {
        printf("Still waiting ...%d\n", pid);
        sleep(1);
    }
    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", ret_pid, exit_status);
    }

    exit(0);
}