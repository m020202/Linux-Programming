#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <setjmp.h>

sigjmp_buf position;

void goBack() {
    fprintf(stderr, "\nInterrupted\n");
    siglongjmp(position, 1);
}

int main ()
{
    static struct sigaction act;
    printf("1\n");
    int result = sigsetjmp(position, 1);
    if (result == 0) {
        act.sa_handler = goBack;
        sigaction(SIGINT, &act, NULL);
        sleep(5);
    }
    else if (result == 1) {
        printf("3\n");
    }

    printf("2");

}
