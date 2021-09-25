#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void* routine(void* args) {
    sem_wait(&semaphore);
    sleep(1);
    printf("hello threrad No: %d\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}

/*
    it can work like a lock or it can work like a condition variable as well.
    basically it will let at most N threads in the critical section at a time.
    TODO: this program is not working right now as expected. try to run it on linux machine
        once, in macOS i am getting errors related to library deprecated.
*/
