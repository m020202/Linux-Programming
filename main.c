#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

int count;
void alarm_action(int sig) {
    printf("wrtie blocked after %d characters\n", count);
    exit(0);
}

int main() {
    int p[2];
    int pipe_size;
    char c = 'x';
    static struct sigaction act;

    act.sa_handler = alarm_action;
    sigfillset(&(act.sa_mask));

    if (pipe(p) == -1) {
        perror("pipe call: ");
        exit(1);
    }

    pipe_size = fpathconf(p[0], _PC_PIPE_BUF);
    printf("Maximum size of write to pipe: %dbytes\n", pipe_size);

    sigaction(SIGALRM, &act, NULL);

    while (1) {
        alarm(5);
        write(p[1], &c, 1);
        alarm(0);
        if ((++count % 1024) == 0)
            printf("%d characters in pipe\n", count);
    }

    return 0;
}