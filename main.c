#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

int main() {
    if (access("data", R_OK) == -1) {
        printf("Couldn't read file");
        return -1;
    }

    printf("%s readable, proceeding\n", "data");

    return 0;
};
