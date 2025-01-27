#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid < 0) {
    printf("Failed to fork\n");
  }

  if (pid > 0) {
    printf("I am %d, and my child is %d\n", getpid(), pid);
    wait(NULL);
  } else {
    printf("I am %d, and my parent is %d\n", getpid(), getppid());
    sleep(10);
  }
  return 0;
}
