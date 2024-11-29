#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main(int argc, char **argv) {
    key_t mkey;
    int msq_id;
    struct msqid_ds msq_status;

    if (argc != 2) {
        perror("usage: show msg keyval\n");
        exit(1);
    }
    mkey = (key_t) argv[1];
    if ((msq_id = msgget(mkey, 0)) == -1) {
        perror("msgget failed");
        exit(2);
    }

    if (msgctl(msq_id, IPC_STAT, &msq_status) == -1) {
        perror("msgctl failed");
        exit(3);
    }

    printf("%d", mkey);
    printf("%ld message(s) on queue", msq_status.msg_qnum);
    printf("%s", ctime(&msq_status.msg_stime));
    return 0;
}