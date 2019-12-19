//
// Created by zcw on 11/21/19.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;
static void sig_usr(int signo)		/* argument is signal number */
{
    printf("\n pid: %d\n", pid);
    if (signo == SIGUSR1) printf("\npid: %d received SIGUSR1 %d\n", pid, signo);
    else if (signo == SIGINT) printf("\npid: %d received SIGINT %d\n", pid, signo);
    else {
        printf("received signal %d\n", signo);
        exit(2);
    }
    exit(0);
}

int main() {
    pid = fork();
    if (pid == 0) {
        // Child
        printf("Child pid: %d\n", pid);
        if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
            printf("can't catch SIGUSR1\n");
            exit(1);
        }
        for ( ; ; )
            pause();
    }
    else {
        printf("Father pid: %d\n", pid);
        if (signal(SIGINT, sig_usr) == SIG_ERR) {
            printf("can't catch SIGINT\n");
            exit(1);
        }
        for ( ; ; )
            pause();
    }
}
