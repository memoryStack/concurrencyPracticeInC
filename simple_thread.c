#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

void *func(int threadNum) {
    printf("thread in %d\n", threadNum);
    sleep(3);
    printf("thread out %d\n", threadNum);
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, &func, 1);
    pthread_create(&t2, NULL, &func, 2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

/*
    Learning TODOs: 
        1. how "sleep" works in all languages.
        2. what all these libraries mentioned above do.
        3. learn about function pointers in C properly and see why this "func"
            has to be void* here instead of void. i just don't understand the signature used here ??
    
    Questions based on this program:
        1. how to pass arguments to the function properly. this format 
            is giving me some warnings, need to resolve them.
        2. how to access the thread properties in this program and what properties and fields
            does a thread struct have. e.g. t1 or t2 here.
*/
