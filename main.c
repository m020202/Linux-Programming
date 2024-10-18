#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("data", "w");
    if (file == NULL) {
        perror("파일 열기 실패: ");
        return -1;
    }

    int age = 25;
    const char *name = "J";
    fprintf(file, "이름: %s\n나이: %d", name, age);

    return 0;
};
