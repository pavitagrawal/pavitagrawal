#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MAX_EATS 3 // Maximum number of times each philosopher can eat

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Mutexes for forks

void *philosopher(void *num) {
    int id = *(int *)num;
    int eat_count = 0; // Count how many times the philosopher has eaten

    while (eat_count < MAX_EATS) { // Eat a maximum of MAX_EATS times
        printf("Philosopher %d is thinking.\n", id);
        usleep(rand() % 1000000); // Simulate thinking time

        // Pick up forks
        int left_fork = id; // Fork on the left
        int right_fork = (id + 1) % NUM_PHILOSOPHERS; // Fork on the right

        // Ensure lower-numbered fork is picked up first to avoid deadlock
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[left_fork]);
            pthread_mutex_lock(&forks[right_fork]);
        } else {
            pthread_mutex_lock(&forks[right_fork]);
            pthread_mutex_lock(&forks[left_fork]);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        usleep(rand() % 1000000); // Simulate eating time
        eat_count++; // Increment the eat count

        // Put down forks
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
    }

    printf("Philosopher %d has finished eating.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_ids[i] = i; // Assign philosopher IDs
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
