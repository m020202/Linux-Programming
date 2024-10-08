#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");
    FILE *fp2 = fopen("test.txt", "w");

    int number = 42;
    const char *text = "Hello world!";

    fprintf(fp, "숫자: %d\n", number);
    fprintf(fp2, "문자열: %s\n", text);

    fclose(fp);

    printf("파일에 데이터 출력 완료");

    return 0;
}