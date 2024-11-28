#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

void handler(int sig){
    printf("Received signal %d\n", sig);
}

int main() {
    static struct sigaction act;
    act.sa_handler = handler;
    sigaction(SIGINT, &act, NULL);

    printf("Sending SIGINT to myself...\n");

    raise(SIGINT);

    return 0;
}