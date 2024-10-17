#include <ulimit.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    long currentFileSize;

    currentFileSize = ulimit(UL_GETFSIZE);

    printf("Current maximum file size: %ld", currentFileSize);
};
