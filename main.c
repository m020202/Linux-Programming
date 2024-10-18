#include <stdio.h>

int main() {
    FILE *file;

    if ((file = fopen("data","r")) == NULL) {
        printf("Couldn't open file!\n");
        return -1;
    }

    return 0;
};
