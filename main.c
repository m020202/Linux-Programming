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

void g_exit(int s) {
    unlink("test");
    fprintf(stderr, "\nInterrupted - exiting\n");
}

int main() {
    static struct sigaction act;

    act.sa_handler = g_exit;
    sigaction(SIGINT, &act, NULL);

    sleep(5);
}
