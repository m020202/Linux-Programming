#include <printf.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t  pid;
    printf("Just one process so far\n");
    printf("Calling fork ...\n");

    pid = fork();

    if (pid == 0) {
        printf("I'm the child\n");
        printf("%d\n", getppid());
    }
    else if (pid > 0) {
        wait(0);
        printf("I'm the parent, child has pid %d\n", pid);
        printf("%d\n", getpid());
    }
    else
        printf("Fork returned error code, no child\n");

    return 0;
}

