// Athul Anoop
// Roll no: 25
// Description: C program to solve dining philosopher's problem using semaphores
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 5

sem_t chopsticks[SIZE];
pthread_t philosophers[SIZE];

void *philosopher_action(int *N);

int main() {
  for (int i = 0; i < SIZE; i++) {
    int status = sem_init(chopsticks + i, 0, 1);
    if (status != 0) {
      perror("\nSemaphore initialization failed");
      exit(1);
    }
  }

  for (int i = 0; i < SIZE; i++) {
    int *id = malloc(sizeof(int));
    *id = i;
    int status =
        pthread_create(philosophers + i, NULL, (void *)philosopher_action, id);
    if (status != 0) {
      perror("\nThread creation failed\n");
      exit(1);
    }
  }

  for (int i = 0; i < SIZE; i++) {
    int status = pthread_join(philosophers[i], NULL);
    if (status != 0) {
      perror("\nThread join failed");
      exit(1);
    }
  }
}

void *philosopher_action(int *N) {
  printf("\nPhilosopher % d is thinking ", *N);
  sem_wait(chopsticks + *N);
  sem_wait(chopsticks + (*N + 1) % SIZE);
  printf("\nPhilosopher % d is eating", *N);
  sleep(2);
  sem_post(chopsticks + *N);
  sem_post(chopsticks + (*N + 1) % SIZE);

  return NULL;
}
