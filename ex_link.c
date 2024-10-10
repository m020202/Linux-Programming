#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    if (symlink("test2.txt", "test4.txt") == -1) {
        perror("link failed");
        exit(1);
    }

    char* buf[10];
    ssize_t len = readlink("test4.txt", buf, 10);

    printf("%s", buf);
}