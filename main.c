#include <unistd.h>
#include <stdio.h>

int main() {
    int increment = 5;

    int current_nice = nice(0);
    printf("Current nice: %d\n", current_nice);

    if (nice(increment) == -1) {
        perror("nice: ");
        return 1;
    }

    int new_nice = nice(0);
    printf("New nice value: %d\n", new_nice);

    return 0;
};
