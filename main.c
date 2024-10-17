#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
    printf("Calling fork...\n");

    pid = fork();

    if (pid == 0) {
        printf("I'm the child. pid: %d, getpid(): %d, getppid: %d\n",
               getpid(), getppid());
    }
    else if (pid > 0) {
        printf("I'm the parent. pid: %d, getpid(): %d, getppid: %d\n", pid, getpid(), getppid());
    } else
        printf("Fork failed\n");

    return 0;
};
