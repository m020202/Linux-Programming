#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("data", "a");

    putc('a', file);
    putc('b', file);

    return 0;
};
