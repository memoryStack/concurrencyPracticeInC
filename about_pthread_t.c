#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define THREAD_NUM 2

void* routine(void* args) {
    pthread_t th = pthread_self(); // it will returrn the thread_id maintaied by the pthread.h library
    printf("pthread level id: %ul\n", th);
    printf("OS level id: %d\n", (pid_t) syscall(SYS_gettid)); // it is the Pid as maintained at the OS level
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
        // printf("%ul\n", th[i]);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    return 0;
}

/*
    pthread_t is just a unsigned long number which will store the threadID.
    TODO: OS level threadID syscall is not working. let's see how to make it right on macOS.
*/