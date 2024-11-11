#include <dirent.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main() {
    short octarr[9] = {
            0400, 0200, 0100,
            0040,0020, 0010,
            0004, 0002, 0001
    };
    char term[9] = "rwxrwxrwx";

    while(1) {
        DIR* dp;
        struct dirent *d;
        dp = opendir(".");

        // 하위 file / directory 탐색하며 목록 출력
        int idx = 0;
        while ((d = readdir(dp))) {
            if (d->d_ino == 0)
                continue;
            printf("%d %s\n", idx, d->d_name);
            ++idx;
        }
        printf("=====================\n");

        // 번호 입력 받기
        int num;
        char ch;
        int result = scanf("%d", &num);

        // 번호를 입력했다면
        if (result == 1) {
            // 입력한 번호의 디렉토리 엔트리 정보 가져 오기
            if (num < 0 || num >= idx) {
                printf("Try Again !!!\n");
                continue;
            }
            rewinddir(dp);
            for (int i = 0; i <= num; ++i) {
                d = readdir(dp);
            }

            // 파일 정보 가져오기
            struct stat sb;
            if (stat(d->d_name, &sb) == -1) {
                fprintf(stderr,"Couldn't stat %s\n", d->d_name);
            }

            // 해당 항목이 파일이면
            if (S_ISREG(sb.st_mode)) {
                char descrip[10];
                descrip[9] = '\0';
                for (int i = 0; i < 9; ++i) {
                    if (sb.st_mode & octarr[i])
                        descrip[i] = term[i];
                    else
                        descrip[i] = '-';
                }

                printf("%-10s %-10lld %-10s\n", descrip, sb.st_size, d->d_name);
            }
                // 해당 항목이 디렉토리면
            else if (S_ISDIR(sb.st_mode)) {
                chdir(d->d_name);
            }
        }
            // 'c'를 입력 했다면
        else {
            scanf("%c", &ch);
            char name[512];
            scanf("%s", name);

            // 해당 파일이 이미 존재하는지 체크
            rewinddir(dp);
            bool tmp = true;
            while ((d = readdir(dp))) {
                if (d->d_ino && strcmp(d->d_name, name) == 0) {
                    remove(name);
                    tmp = false;
                    break;
                }
            }

            // 파일 존재하지 않으면 새로 생성
            if (tmp) {
                int fd;
                if ((fd = open(name, O_WRONLY | O_CREAT, 0644)) == -1) {
                    fprintf(stderr, "File create error !!!");
                }
                close(fd);
            }
        }
        closedir(dp);
        printf("\n");
    }
    return 0;
}