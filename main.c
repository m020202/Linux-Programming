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

void catch (int sig) {
    time_out = 1;

}

int main() {
    static struct sigaction act;
    act.sa_handler = catch;
    sigaction(SIGALRM, &act, NULL);

    for (int i = 0; i < 5; ++i) {
        time_out = 0;
        alarm(5);
        scanf("%s", answer);
        alarm(0);
        if (!time_out) break;
    }

    printf("%s", answer);
    return 0;
}