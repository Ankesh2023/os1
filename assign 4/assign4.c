// asynchronous_reader_writer.c

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h> // for intptr_t

int data = 0;

void* reader(void* arg)
{
    int id = (intptr_t)arg;
    printf("Reader %d reads data = %d\n", id, data);
    sleep(1);
    pthread_exit(NULL);
}

void* writer(void* arg)
{
    int id = (intptr_t)arg;
    data++;
    printf("Writer %d writes data = %d\n", id, data);
    sleep(1);
    pthread_exit(NULL);
}

int main()
{
    int ids[5];
    pthread_t readers[5], writers[2];

    for (int i = 0; i < 5; i++)
    {
        ids[i] = i + 1;

        if (pthread_create(&readers[i], NULL, reader, (void*)(intptr_t)ids[i]) != 0)
        {
            perror("Failed Reader Creation!");
            pthread_exit(NULL);
        }

        if (i < 2)
        {
            if (pthread_create(&writers[i], NULL, writer, (void*)(intptr_t)ids[i]) != 0)
            {
                perror("Failed Writer Creation!");
                pthread_exit(NULL);
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    return 0;
}













// synchronous_reader_writer.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>  


int data = 0;
int readcount = 0;
pthread_mutex_t mutex;
sem_t wrt;

void* reader(void* arg) {
    int id = (intptr_t)arg;

    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Mutex Lock Failed!");
        pthread_exit(NULL);
    }

    readcount++;
    if (readcount == 1) {
        if (sem_wait(&wrt) != 0) {
            perror("Semaphore Wait Failed!");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Mutex Unlock Failed!");
        pthread_exit(NULL);
    }

    printf("Reader %d reads data = %d\n", id, data);
    sleep(1);

    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Mutex Lock Failed!");
        pthread_exit(NULL);
    }

    readcount--;
    if (readcount == 0) {
        if (sem_post(&wrt) != 0) {
            perror("Semaphore Post Failed!");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Mutex Unlock Failed!");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = (intptr_t)arg;

    if (sem_wait(&wrt) != 0) {
        perror("Semaphore Wait Failed!");
        pthread_exit(NULL);
    }

    data++;
    printf("Writer %d writes data = %d\n", id, data);
    sleep(1);

    if (sem_post(&wrt) != 0) {
        perror("Semaphore Post Failed!");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[2];

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex Initialization Failed!");
        return 1;
    }

    if (sem_init(&wrt, 0, 1) != 0) {
        perror("Semaphore Initialization Failed!");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        if (pthread_create(&readers[i], NULL, reader, (void*)(intptr_t)(i + 1)) != 0) {
            perror("Failed Reader Creation!");
            exit(EXIT_FAILURE);
        }

        if (i < 2) {
            if (pthread_create(&writers[i], NULL, writer, (void*)(intptr_t)(i + 1)) != 0) {
                perror("Failed Writer Creation!");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
