/* Athul Anoop
 * Roll no: 25
 * Description: C program to solve TA problem
 */

#include <_stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/semaphore.h>
#include <time.h>
#include <unistd.h>

#define MAX_STUDENTS 100

sem_t ta, chairs;
pthread_t students[MAX_STUDENTS];

void *get_help_from_TA(int *id);

int main() {
  srand(time(0));
  int status = sem_init(&chairs, 0, 3);
  if (status != 0) {
    perror("\nSemaphore initialization failed");
    exit(1);
  }

  for (int i = 0; i < MAX_STUDENTS; i++) {
    int *id = malloc(sizeof(int));
    *id = i;

    int status =
        pthread_create(students + i, NULL, (void *)get_help_from_TA, id);
    if (status != 0) {
      perror("\nThread creation failed\n");
      exit(1);
    }
    return 0;
  }

  for (int i = 0; i < MAX_STUDENTS; i++) {
    int status = pthread_join(students[i], NULL);
    if (status != 0) {
      perror("\nThread join failed");
      exit(1);
    }
  }
}

void *get_help_from_TA(int *id) {
  printf("\nStudent %d has arrived", *id);
  while (sem_trywait(&ta) != 0) {
    if (sem_trywait(&chairs) != 0) {
      int delay = rand() % 5;
      printf("No chairs, available student %d will return after %d seconds",
             *id, delay);
      sleep(delay);
      continue;
    } else
      printf("Student %d is waiting on a chair", *id);
  }
  printf("TA is helping student %d", *id);
  sem_post(&ta);

  return NULL;
}
