#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d\n", getpid());
    printf("%d\n", getuid());
    printf("%d\n", geteuid());
    printf("%d\n", getgid());
    printf("%d\n", getegid());
};
