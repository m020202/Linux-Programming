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

void catchInt(int signo) {
    printf("\nCATCHINT: signo=%d\n", signo);

    printf("CATCHINT: returning\n\n");
}

int main() {
    static struct sigaction act;
    act.sa_handler = catchInt;
    sigemptyset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);

    printf("sleep call #1\n");
    sleep(10);
    printf("sleep call #2\n");
    sleep(10);
    printf("sleep call #3\n");
    sleep(10);
    printf("sleep call #4\n");
    sleep(10);

    printf("Exiting\n");
    return 0;
}
