//
// Created by zcw on 11/21/19.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
int main() {
    pid_t sender, receiver;
    int id;
    int e = 0;
    char* v_addr;
    while (e < 10) {
        sender = fork();
        id = shmget(88, 20, IPC_CREAT | 0666);
        v_addr = shmat(id, 0, 0);
        if (sender == 0) {
            int a;
            printf("In sender: ");
            scanf("%d", &a);
            v_addr[e] = a;
            exit(0);
        }
        else if (sender < 0) {
            printf("Fork error");
            exit(1);
        }
        else {
            wait(NULL);
            receiver = fork();

            if (receiver == 0) {
                int r = v_addr[e];
                printf("In receiver: %d\n", r * r);
                exit(0);
            }
            else if (receiver < 0) {
                printf("Fork error");
                exit(1);
            }
            else {
                wait(NULL);
                e += 1;
            }
        }
    }
    shmctl(id, IPC_RMID, 0);
    exit(0);
}
