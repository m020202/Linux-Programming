#include <printf.h>
#include <unistd.h>


int main() {
    const char *args[] = {"ls", "-l", (char* ) 0};
    printf("executing ls\n");

    execv("/bin/ls", args);

    perror("execl failed to run ls");

    return 0;
}

