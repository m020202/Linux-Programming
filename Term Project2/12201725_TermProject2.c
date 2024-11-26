#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define MSG_LEN 512

static int time_out;

void handler(int signo) {
    if (signo == SIGINT) {
        printf("\nDon't try to kill this program with signal! You have 'exit' command!\n");
    } else if (signo == SIGALRM) { // alarm에 대한 시그널 설정
        time_out = 1;
    }
}

int main (int argc, char **argv)
{
    int nsec;
    int ctp[2], ptc[2];
    pid_t pid, ppid;
    char inbuf[MSG_LEN];
    static struct sigaction act;

    /* Signal Handling */
    /* Your Code */
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGALRM, &act, NULL);

    /* Pipe communications. */
    /* Your Code */
    if (pipe(ctp) == -1) {
        perror("pipe call");
        exit(1);
    }
    if (pipe(ptc) == -1) {
        perror("pipe call");
        exit(1);
    }
    // Non-Blocking 구현
    if (fcntl(ctp[0], F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl: nonblock");
        return 0;
    }

    switch (pid = fork()) {
        case -1:
            perror("fork call");
            exit(2);
        case 0:
            close(ctp[0]);
            close(ptc[1]);
            int res;
            while(1) {
                res = scanf("%d", &nsec);
                // 입력 값이 숫자가 아닐 경우
                if (res == 0) {
                    char input[10];
                    scanf("%s", input);
                    if (strcmp(input, "exit") == 0) {
                        exit(1);
                    }
                    else
                        continue;
                }
                // 입력 값이 숫자이지만 범위가 다를 경우
                else if (nsec < 1 || nsec > 60)
                    continue;
                printf("-----------------\n");
                write(ctp[1], &nsec, 1);
                // 1초에 한 번씩 카운트 다운
                while(nsec >= 0) {
                    time_out = 0;
                    alarm(1);
                    while (!time_out) {
                        pause();
                    }
                    if (nsec == 0)
                        break;
                    printf("%d\n", nsec);
                    nsec--;
                }
                // 부모가 pipe로 보낸 메시지 읽기
                read(ptc[0], inbuf, MSG_LEN);
                printf("%s\n", inbuf);
            }
            break;
        default:
            close(ptc[0]);
            close(ctp[1]);
            int result;
            while(1) {
                // 자식이 pipe로 주는 메시지 기다리기
                result = read(ctp[0], &nsec, 1);
                if (result == -1){
                    if (errno == EAGAIN)
                        continue;
                    else {
                        perror("read call");
                        return 0;
                    }
                }
                // 만약 자식이 보낸 값이 없다면 종료
                else if (result == 0)
                    exit(0);
                // 값이 있다면 값만큼 타이머 세팅
                else {
                    act.sa_handler = SIG_IGN;
                    sigaction(SIGINT, &act, NULL);
                    time_out = 0;
                    alarm(nsec);
                    while (!time_out) {
                        pause();
                    }
                    // 타이머 종료 후 자식에게 pipe로 메시지 보내기
                    write(ptc[1], "Wake Up!", MSG_LEN);
                }
            }
            wait(NULL);
    }
    return 0;
}
