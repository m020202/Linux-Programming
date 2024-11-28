#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>


static int time_out;
static char answer[11];

void sig_handler (int sig) {
    if (sig == SIGINT)
        printf("\nDon't Ctrl+C !!\n");
    else if (sig == SIGALRM) {
        printf("시간 초과\n");
        time_out = 1;
    }

}

int main() {
    static struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGALRM, &act, NULL);

    time_out = 0;
    alarm(2);

    while (!time_out) {
        pause();
    }

    sleep(5);
    printf("완료됨");
    return 0;
}