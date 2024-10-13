#include <unistd.h>


int main() {
    const char *argin[] = {"./ex_link", "hello", "world", (char *) 0};
    execv(argin[0], argin);
    return 0;
};

