//
// Created by zcw on 11/18/19.
//
//
// Created by zcw on 11/18/19.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *myThread1(void* arg) {
    int* num;
    num = (int*)arg;
    printf("Parameter is %d. \n", *num);
}

void *myThread2(void* arg) {
    char* num;
    num = (char*)arg;
    printf("Parameter is %c. \n", *num);
}
int main() {
    int r1, r2;
    pthread_t t1, t2;
    int n = 12345;
    char c = 'a';
    int* np = &n;
    char* cp = &c;
    
    r1 = pthread_create(&t1, NULL, myThread1, (void*) np);
    if (r1 != 0) {
        printf("Error occurs when creating pthread1. \n");
        exit(1);
    }
    r2 = pthread_create(&t2, NULL, myThread2, (void*) cp);
    if (r2 != 0) {
        printf("Error occurs when creating pthread2. \n");
        exit(1);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
