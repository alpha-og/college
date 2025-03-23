/*
 * Problem Number: 11
 *
 * Description
 * Create a new process using the fork() system call. Have the processes
 * introduce themselves with their process IDs as follows: Parent: I am <myID>,
 * and my child is <mychildID> Child: I am <myID>, and my parent is <myparentID>
 * Use the pstree command to display the process tree for the child process
 * starting from the init process. The child process is to be “highlighted” in
 * the tree.
 *
 * Athul Anoop
 */

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
