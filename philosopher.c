#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 10
sem_t chopstick[MAX];

void eat(int n) {
    printf("Philosopher %d is eating\n",n);
}
void think(int n) {
    printf("Philosopher %d is thinking\n",n);
}

void *philosopher(void *j) {
    do {
        int *k = (int *)j;
        int i = *k;
        
        // left and right fork is locked
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i+1)%MAX]);
        
        // Eating process
        eat(i);
        sleep(1);
        
        // Release left and right fork
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i+1)%MAX]);
        
        // Thinking
        think(i);
        sleep(1);
    } while(1);
}

int main() {
    pthread_t philo[MAX];

    for(int i=0; i<MAX; i++) {
        sem_init(&chopstick[i], 0, 1);
    }
    
    for(int i=0; i<MAX; i++) {
        pthread_create(&philo[i], NULL, philosopher, &i);
    }
    
    for(int i=0; i<MAX; i++) {
        pthread_join(philo[i], NULL);
    }
    return 0;
}