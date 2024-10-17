#include <stdio.h>
#include <ulimit.h>

int main() {
    printf("%ld", ulimit(UL_GETFSIZE));
    return 0;
}