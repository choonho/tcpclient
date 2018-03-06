#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 65000

pthread_t tid[MAX_THREADS];

void *client(void *data)
{
    int *tid = (int *)data;

    printf("Thread[%d] started\n", *tid);
    /* Do your Logic */
    for(int i = 0; i < 1000; ++i) {}
    return NULL;
}

int main(int argc, char *argv[])
{
    int numthreads;
    int i;

    if (argc != 3) {
        fprintf(stderr, "usage: client <server_url> <number of threads>\n");
        fprintf(stderr, "  example) ./client http://127.0.0.1/index.html 1000\n");
        exit(1);
    }
    numthreads = atoi(argv[2]);
    if (numthreads == 0) {
        fprintf(stderr, "Failed to parse %s\n", argv[2]);
        exit(1);
    }
    if (numthreads > MAX_THREADS) {
        fprintf(stderr, "Maximum number of threads is %d\n", MAX_THREADS);
        numthreads = MAX_THREADS;
    }

    printf("Create clients: %d\n", numthreads);    
    for(i = 0; i < numthreads; ++i) {
        if(pthread_create(&tid[i], NULL, client, &i)) {
            fprintf(stderr, "Error creating thread[%d]\n", i);
            return 1;
        } 
        if(pthread_join(tid[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }
    return 0;
}
