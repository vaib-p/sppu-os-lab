#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer_thr(void *temp);
void *reader_thr(void *temp);

sem_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;

int main() { 
  long int i;
  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);
  pthread_t reader[100], writer[100];
  printf("\n Enter number of readers:");
  scanf("%d", &nrd);
  printf("\n Enter number of writers:");
  scanf("%d", &nwt);

  for (i = 1; i <= nwt; i++) {
    pthread_create(&writer[i], NULL, writer_thr, (void *)&i); 
  }

  for (i = 1; i <= nrd; i++) {
    pthread_create(&reader[i], NULL, reader_thr, (void *)&i); 
  }

  for (i = 1; i <= nwt; i++) {
    pthread_join(writer[i], NULL); 
  }

  for (i = 1; i <= nrd; i++) {
    pthread_join(reader[i], NULL); 
  }

  sem_destroy(&wrt);
  sem_destroy(&mutex);

  return 0; 
}

void *reader_thr(void *temp) {
  int id = *((int *)temp); // Cast the pointer back to int

  printf("\n Reader %d is trying to enter database for reading.", id);
  sem_wait(&mutex);
  readcount++;
  if (readcount == 1)
    sem_wait(&wrt);
  sem_post(&mutex);

  printf("\n Reader %d is now reading in the database.", id);

  sem_wait(&mutex);
  readcount--;
  if (readcount == 0)
    sem_post(&wrt);
  sem_post(&mutex);
  printf("\n Reader %d has left the database.\n", id);
  sleep(3);
}

void *writer_thr(void *temp) {
  int id = *((int *)temp); 

  printf("\n Writer %d is trying to enter the database for modifying data", id);
  sem_wait(&wrt);
  printf("\n Writer %d is writing in the database.", id);
  sleep(3);
  printf("\n Writer %d is leaving the database.\n", id);
  sem_post(&wrt);
}

