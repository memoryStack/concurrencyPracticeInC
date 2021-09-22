#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void *func(void* arg) {
    int startIndex = *(int*)arg;
    int sum=0;
    for(int i=0;i<5;i++){
        sum += arr[startIndex+i];
    }
    *(int*)arg = sum;
    return arg;
}

int main(int argc, char *argv[]) {
    pthread_t th[2];

    for (int i=0;i<2;i++) {
        int* val = malloc(sizeof(int));
        *val = i * 5;
        pthread_create(th + i, NULL, &func, (void*)val);
    }

    int totalSum = 0;
    for (int i=0;i<2;i++) {
        int* result;
        pthread_join(th[i], (void**)&result);
        totalSum += *result;
        free(result);
    }

    printf("array sum is: %d\n", totalSum);

    return 0;
}

/*
    just a practical example of the learnings from previous examples
*/
