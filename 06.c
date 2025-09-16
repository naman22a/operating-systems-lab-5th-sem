#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t wrt;
int read_count = 0;
int data = 0;

void *reader(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d is reading data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        sem_wait(&wrt);

        data++;
        printf("Writer %d is writing data = %d\n", id, data);
        sleep(1);

        sem_post(&wrt);

        sleep(2);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t rtid[5], wtid[3];
    int rid[5], wid[3];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < 5; i++)
    {
        rid[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &rid[i]);
    }

    for (i = 0; i < 3; i++)
    {
        wid[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &wid[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);
    for (i = 0; i < 3; i++)
        pthread_join(wtid[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
