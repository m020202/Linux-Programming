#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    while (--argc > 0) {
        printf("%s ", *++argv);
    }
    printf("\n");
}