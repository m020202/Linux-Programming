#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

void handler(int signo) {
    if (signo == SIGINT) {
        printf("\nDon't try to kill this program with signal! You have 'exit' command!\n");
    }
}

int main() {
    static struct sigaction act;
    act.sa_handler = handler;
    sigaction(SIGINT, &act, NULL);
    int pid;

    switch (pid = fork()) {
        case 0:
            for (int i = 0; i < 10; ++i) {
                printf("hello world\n");
                sleep(1);
            }
        default:
            wait(NULL);
    }
}