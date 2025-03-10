/* Athul Anoop
 * Roll no: 25
 * Description: C program to display system date and time and time elapsed by
 * the current process in user and kernel mode
 */

#include <stdio.h>
#include <sys/resource.h>
#include <time.h>

int main() {
  time_t t;
  time(&t);
  struct tm *time = localtime(&t);

  char buffer[100];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time);
  printf("Current system date and time: %s\n", buffer);

  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    printf("User mode CPU time: %ld.%06ld seconds\n", usage.ru_utime.tv_sec,
           (long)usage.ru_utime.tv_usec);
    printf("Kernel mode CPU time: %ld.%06ld seconds\n", usage.ru_stime.tv_sec,
           (long)usage.ru_stime.tv_usec);
  } else
    perror("getrusage");
  for (int i = 0; i < 9999999; i++)
    ;

  printf("\nAfter long running loop\n");
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    printf("User mode CPU time: %ld.%06ld seconds\n", usage.ru_utime.tv_sec,
           (long)usage.ru_utime.tv_usec);
    printf("Kernel mode CPU time: %ld.%06ld seconds\n", usage.ru_stime.tv_sec,
           (long)usage.ru_stime.tv_usec);
  } else
    perror("getrusage");

  return 0;
}
