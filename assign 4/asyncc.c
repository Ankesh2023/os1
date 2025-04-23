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

