//
// Created by zcw on 11/21/19.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message {
    char m[20];
}msg;
int main() {
    pid_t sender, receiver;
    int qid;
    int e;

    qid = msgget(88, IPC_CREAT | 0666);

    if (qid == -1) {
        perror("Failed in calling msgget");
        return -1;
    }
    while (1) {
        sender = fork();
        if (sender == 0) {
            char a[20];
            printf("In sender: ");
            scanf("%s", a);
            if (strcmp(a, "exit") == 0) {
                exit(1);
            }
            strcpy(msg.m, a);
            msgsnd(qid, &msg, 20, 0);
            exit(0);
        }
        else if (sender < 0) {
            printf("Fork error");
            exit(1);
        }
        else {
            wait(&e);
            if (WEXITSTATUS(e) == 1){
                msgctl(qid, IPC_RMID, 0);
                exit(0);
            }
            receiver = fork();
            if (receiver == 0) {
                msgrcv(qid, &msg, 20, 0, 0);
                printf("In receiver: ");
                printf("%s\n", msg.m);
                exit(0);
            }
            else if (receiver < 0) {
                printf("Fork error");
                exit(1);
            }
            else {
                wait(NULL);
            }
        }
    }
}
