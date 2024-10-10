#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    if (link("test.txt", "test3.txt") == -1) {
        perror("link failed");
        exit(1);
    }

    if (unlink("test.txt") == -1) {
        perror("unlink failed");
        unlink("test3.txt");
        exit(1);
    }

    printf("succeeded!");
}