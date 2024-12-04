#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "msg_header.h"

int msgid;

void sig_handler(int signo) {
    msgctl(msgid, IPC_RMID, 0);
    printf("\nGraceful Exit!");
    exit(0);
}

int main() {
    struct msg_entry msg;
    struct sigaction act;

    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);

    if ((msgid = msgget(IPC_CREAT, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            msg.mtype = 1;
            strcpy(msg.mtext, "message type 1 from child\n");
            if (msgsnd(msgid, &msg, 100, IPC_NOWAIT) == -1) {
                perror("msgsnd");
                exit(1);
            }
            return 0;
        default:
            while(msgrcv(msgid ,&msg,100, 0,0) > 0) {
                printf("Received Message = %s\n", msg.mtext);
            }
            wait(NULL);
    }

    return 0;

}