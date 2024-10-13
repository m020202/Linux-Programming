#include <printf.h>
#include <unistd.h>


int main() {
    printf("executing ls\n");

    execl("/bin/ls", "ls", "-l", (char *) 0);

    perror("execl failed to run ls");

    return 0;
}

