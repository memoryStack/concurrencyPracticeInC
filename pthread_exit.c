#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

void* func(void* arg) {
    sleep(5);
    printf("thread ran\n");
    return NULL;
}

int main(int argc, char* argv[]) {    
    pthread_t th;
    pthread_create(&th, NULL, &func, NULL);
    pthread_exit(0);
    printf("sdjkbvsj"); // this won't be printed as main thread has exited
    return 0;
}

/*
    pthread_exit simply terminates the thread which calls it. it won't affect the children threads
    spawned by the the caller thread. newly spawned threads will continue their execution until they terminate.
    Note: if we call exit(0) in main func then it will kill the process and the spawned threads will also be terminated if any.
*/
