#include <ulimit.h>
#include <stdio.h>

int main() {
    long currentFileSize;

    if ((currentFileSize = ulimit(UL_SETFSIZE, 10 * 1024 * 1024)) == -1) {
        perror("ulimit:");
        return 1;
    }

    printf("Current maximum file size: %ld", currentFileSize);
};
