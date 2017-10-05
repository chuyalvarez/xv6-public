#include <pthread.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <semaphore.h>

 #define NUM_THREADS     10

 long saldo;
 sem_t mutex;
 void *PrintHello(void *threadid)
 {
    long tid;
    long lsaldo;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    sem_wait(&mutex);
    lsaldo = saldo;
    sleep(1); // forzando a perder el cpu
    lsaldo += 1;
    saldo = lsaldo;
    sem_post(&mutex);
    pthread_exit(NULL);
 }

 int main (int argc, char *argv[])
 {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    saldo = 0;
    sem_init(&mutex,0,1);

    for(t=0; t<NUM_THREADS; t++){
       printf("In main: creating thread %ld\n", t);
       rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          //exit(-1);
       }
    }
    for(t=0; t<NUM_THREADS; t++){
      pthread_join(threads[t], NULL);
    }
    printf("El valor del saldo es %ld\n", saldo);
    /* Last thing that main() should do */
    pthread_exit(NULL);
 }
