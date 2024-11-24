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
    static struct sigaction act, oact;

    act.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act, &oact);
    sigaction(SIGINT, &oact, NULL);

    printf("hello world\n");
    sleep(10);
    return 0;
}
