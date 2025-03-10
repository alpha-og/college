/* Athul Anoop
 * Roll no: 25
 * Description: C program to fork a new process and load a custom binary into
 * the child process
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("\nFork failed");
    return 0;
  } else if (pid == 0) {
    char *args[] = {"./myadder", argv[1], argv[2], NULL};
    execvp("./myadder", args);
  } else {
    wait(NULL);
    return 0;
  }
}
