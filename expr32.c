//
// Created by zcw on 11/18/19.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *myThread1(void* arg) {
    int *Array;
    Array = (int*)arg;
    int n = 10;
    int Smallest;
    for (int i = 0; i < n; i ++) {
        Smallest = i;
        for (int j = i + 1; j < n; j ++) {
            if(Array[j] < Array[Smallest]) {
                Smallest = j;
            }
        }
        int t = Array[Smallest];
        Array[Smallest] = Array[i];
        Array[i] = t;
    }
    for (int i = 0; i < 10; i ++) {
        printf("%d ", Array[i]);
    }
    printf("\n");

    return (void*)0;
}

void *myThread2(void* arg) {
    int *Array;
    Array = (int*)arg;
    int n = 10;
    int Biggest;
    for (int i = 0; i < n; i ++) {
        Biggest = i;
        for (int j = i + 1; j < n; j ++) {
            if(Array[j] > Array[Biggest]) {
                Biggest = j;
            }
        }
        int t = Array[Biggest];
        Array[Biggest] = Array[i];
        Array[i] = t;
    }
    for (int i = 0; i < 10; i ++) {
        printf("%d ", Array[i]);
    }
    printf("\n");
}

int main() {
    int r1, r2;
    pthread_t t1, t2;
    int data[] = {3, 7, 5, 8, 4, 1, 2, 6, 10, 9};
    int (*np)[] = &data;

    r1 = pthread_create(&t1, NULL, myThread1, (void*)np);
    if (r1 != 0) {
        printf("Error occurs when creating pthread1. \n");
        exit(1);
    }

    r2 = pthread_create(&t2, NULL, myThread2, (void*)np);
    if (r2 != 0) {
        printf("Error occurs when creating pthread2. \n");
        exit(1);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
