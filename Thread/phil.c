#include <pthread.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <semaphore.h>

 #define NUM_PHIL     5
 #define NUM_FORK     5


 sem_t forks[NUM_FORK];
 int getRand(float max) {

   return 1 + (rand() * max) / RAND_MAX;
 }

 void eating(void){
    sleep(getRand(5.0));
 }

 void thinking(void){
    sleep(getRand(5.0));
 }

 void *philLive(void *threadid){
   long tid;
   tid =(long)threadid;
   while(1){
     printf("i am phil %ld, thinking \n", tid);
     thinking();
     if (tid % 2 == 0){
       sem_wait(&forks[tid]);
       sem_wait(&forks[(tid+1) % NUM_PHIL]);
     }else{

     sem_wait(&forks[(tid+1) % NUM_PHIL]);
      sem_wait(&forks[tid]);
   }
      printf("i am phil %ld, eating \n", tid);

     eating();
     sem_post(&forks[tid]);
     sem_post(&forks[(tid+1) % NUM_PHIL]);
   }
 }

 int main (int argc, char *argv[])
 {
    pthread_t philosophers[NUM_PHIL];
    int rc;
    long t;
    srand(time(NULL));
    for(t=0; t<NUM_FORK; t++){
      sem_init(&forks[t],0,1);
    }
    for(t=0; t<NUM_PHIL; t++){
       printf("In main: creating thread %ld\n", t);
       rc = pthread_create(&philosophers[t], NULL, philLive, (void *)t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
 }
