#include <printf.h>
#include <unistd.h>


int main() {
    pid_t  pid;
    printf("Just one process so far\n");

    pid = fork();

    if (pid == 0)
        printf("I'm the child\n");
    else if (pid > 0)
        printf("I'm the parent, child has pid %d\n", pid);
    else
        printf("Fork returned error code, no child\n");

    return 0;
}

