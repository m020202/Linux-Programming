#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 512

int main() {
    FILE *file_stream;
    if ((file_stream = fopen("test.txt", "r+")) == NULL) {
        printf("Could not open the test file! \n");
        exit(0);
    }

    int k = getc(file_stream);
    printf("%d\n", k);
    int c = putc('b', file_stream);
    printf("%d\n", c);
    c = putc(100, file_stream);
    printf("%d", c);
    return 0;
}
