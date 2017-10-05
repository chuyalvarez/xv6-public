#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_SIZE 10
int buffer[MAX_SIZE];

sem_t ready; // initial 0 producer indicates that there is something
sem_t slots;

int getRand(float max){
  return 1 + rand() * max / RAND_MAX;
}

void *producer(void *threadid){
  int i = 0;
  while(1){
    i = i%MAX_SIZE;
    sem_wait(&slots);
    buffer[i] = getRand(10.0);
    printf("Produced %i \n", buffer[i]);
    sem_post(&ready);
    i++;
  }
  pthread_exit(NULL);
}

void *consumer(void *threadid){
  int i = 0;
  int value;
  while(1){
    sem_wait(&ready);
    i = i%MAX_SIZE;
    value =buffer[i];
    printf("Consumed %i \n", value);
    sem_post(&slots);
    i++;
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  pthread_t ptproducer;
  pthread_t ptconsumer;
  long t;

  sem_init(&ready,0,0);
  sem_init(&slots,0,MAX_SIZE);
  pthread_create(&ptproducer, NULL, producer, NULL);
  pthread_create(&ptconsumer, NULL, consumer, NULL);

  /* Last thing that main() should do */
  pthread_exit(NULL);
}
