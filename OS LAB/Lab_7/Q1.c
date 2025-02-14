#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int capacity = 5; 
int produced_item = 0;
int consumed_item = -1;
int *buffer;

sem_t empty; // Semaphore for empty slots
sem_t full;  // Semaphore for full slots
pthread_mutex_t mutex; // Mutex for critical section
int in = 0, out = 0; // Buffer indices

void *producer(void *arg) {
    while (1) {
        // Produce data 
        produced_item++; 
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Put into buffer
        buffer[in] = produced_item;
        printf("Produced: %d\n", produced_item);
        in = (in + 1) % capacity;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal that a new item is produced

        usleep(rand() % 1000000); // Simulate variable production time

        if (produced_item >= 10) { 
            printf("10 items produced, exiting Producer Thread\n");
            break;
        }  
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Use consumed data
        consumed_item = buffer[out];
        printf("Consumed: %d\n", consumed_item);
        out = (out + 1) % capacity;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal that an item has been consumed

        usleep(rand() % 1000000); // Simulate variable consumption time

        if (consumed_item >= 10) {
            printf("10 items consumed, exiting Consumer Thread\n");
            break;
        }  
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    buffer = (int*)malloc(sizeof(int) * capacity);
    sem_init(&empty, 0, capacity); // Initialize empty semaphore
    sem_init(&full, 0, 0); // Initialize full semaphore
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up
    free(buffer);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
