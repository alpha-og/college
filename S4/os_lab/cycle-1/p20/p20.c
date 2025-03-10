// Athul Anoop
// Roll no: 25
// Description: C program to execute a command and calculate the time taken to
// complete its execution
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  key_t key = IPC_PRIVATE;
  int shm_id = shmget(key, sizeof(struct timeval), IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("shmget failed");
    exit(1);
  }

  struct timeval *start_time = (struct timeval *)shmat(shm_id, NULL, 0);
  if (start_time == (void *)-1) {
    perror("shmat failed");
    exit(1);
  }
  pid_t pid = fork();
  if (pid < 0) {
    printf("Error in forking process\n");
  } else if (pid == 0) {
    gettimeofday(start_time, 0);
    execvp(argv[1], argv + 1);
  } else {
    wait(NULL);
    struct timeval *end_time = calloc(1, sizeof(struct timeval));
    gettimeofday(end_time, 0);
    printf("\nCommand %s took %ld seconds to execute\n", argv[1],
           end_time->tv_sec - start_time->tv_sec);
    shmdt(start_time);
  }
}
