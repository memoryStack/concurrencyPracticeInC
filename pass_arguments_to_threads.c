#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

void *func(void* ptr) {
    printf("passed values is: %d\n", *(int*)ptr);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[10];

    int* mem[10];

    for (int i=0;i<10;i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        mem[i] = val;
        pthread_create(th + i, NULL, &func, (void*)val);
    }

    for (int i=0;i<10;i++) {
        pthread_join(th[i], NULL);
        free(mem[i]);
    }

    return 0;
}

/*
    basically need to pass an address of memory where our arguments are stored.
    Observation: man really learn the pointers and we get a lot of power in C.
*/
