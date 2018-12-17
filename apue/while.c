#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *threadRoutine(void *);

int
main(int argc, char *argv[])
{
    pthread_t  tid;
    pthread_create(&tid, NULL, threadRoutine, NULL);
    pthread_join(tid, NULL);
    return 0;
}

void
*threadRoutine(void *args)
{
    while(1) {
        sleep(1);
    }
    return (void *)(0);
}