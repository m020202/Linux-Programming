#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");

    if (fp == NULL) {
        perror("파일 열기 실패");
        return -1;
    }

    int number = 42;
    const char *text = "Hello world!";

    fprintf(fp, "숫자: %d\n", number);
    fprintf(fp, "문자열: %s\n", text);

    fclose(fp);

    printf("파일에 데이터 출력 완료");

    return 0;
}