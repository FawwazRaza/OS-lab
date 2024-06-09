#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeblock;
int data = 0, readers_count = 0;

void *start_read(void *arg);
void *end_read(void *arg);
void *start_write(void *arg);
void *end_write(void *arg);

void *start_read(void *arg) {
    sem_wait(&mutex);
    readers_count++;
    if (readers_count == 1)
    {
        sem_wait(&writeblock);
    }
    sem_post(&mutex);

    printf("Reader is reading data: %d\n", data);

    sem_wait(&mutex);
    readers_count--;
    if (readers_count == 0)
    {
        sem_post(&writeblock);
    }
    sem_post(&mutex);
    return NULL;
}

void *end_read(void *arg) 
{
    return NULL;
}

void *start_write(void *arg) 
{
    sem_wait(&writeblock);
    data++;
    printf("Writer  is writing data: %d\n", data);
    sem_post(&writeblock);
    return NULL;
}

void *end_write(void *arg) 
{
    return NULL;
}
int main() 
{
    pthread_t thread1[5], thread2[5];
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread2[i], NULL, start_write, NULL);
        pthread_create(&thread1[i], NULL, start_read, NULL);
    }

    for (int i = 0; i < 3; i++) 
    {
        pthread_join(thread2[i], NULL);
        pthread_join(thread1[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeblock);
    return 0;
}

