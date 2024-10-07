#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 512

int main() {
//    ssize_t nread;
//    char buf[SIZE];
//
//    while ((nread = read(0, buf, SIZE)) > 0)
//        write(1, buf, nread);
//
//    exit(0);

    FILE *file_stream;
    if ((file_stream = fopen("test.txt", "r+")) == NULL) {
        printf("Could not open the test file! \n");
        exit(0);
    }

    return 0;
}
