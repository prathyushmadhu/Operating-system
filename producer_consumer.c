#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

sem_t full,empty,mutex;
int in,out;
int *buffer;
int buffersize;
int item = 10;

void * Producer() {
    do {
        sem_wait(&empty);
        sem_wait(&mutex);
        
        buffer[in] = item++;
        printf("Produced %dth item %d\n", in, buffer[in]);
        in=(in+1)%buffersize;
        sleep(1);
        
        sem_post(&mutex);
        sem_post(&full);
    }while(1);
}

void * Consumer() {
    do {
        sem_wait(&full);
        sem_wait(&mutex);
        
        printf("Consumed %dth item %d\n", out, buffer[out]);
        out=(out+1)%buffersize;
        sleep(1);
        
        sem_post(&mutex);
        sem_post(&empty);
    }while(1);
}

int main() {
    printf("Enter the size of buffer: ");
    scanf("%d",&buffersize);
    buffer = (int *)malloc(buffersize*sizeof(int));
    in = 0;
    out = 0;
    
    // buffer initialisation
    sem_init(&empty, 0, buffersize); // 0->shared among thread of same process
    sem_init(&full, 0, 0);           // buffersize -> initial value
    sem_init(&mutex, 0, 1);
    
    // Creating new thread
    pthread_t prodThread, consThread;
    pthread_create(&prodThread, NULL, Producer, NULL);
    pthread_create(&consThread, NULL, Consumer, NULL);
    
    // Calling thread (Telling main thread to wait for this particular thread)
    pthread_join(prodThread,NULL);
    pthread_join(consThread,NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    free(buffer);
    return 0;

}
