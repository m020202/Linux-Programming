#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d\n", getpid());
    printf("%d\n", getpgid(1));
    setpgid(1, 0);
    printf("%d\n", getpgid(1));
};
