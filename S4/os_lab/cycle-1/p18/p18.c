/* Athul Anoop
 * Roll no: 25
 * Description: C program to display system date and time and time elapsed by
 * the current process in user and kernel mode
 */

#include <stdio.h>
#include <sys/resource.h>

int main() {
  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    printf("User mode CPU time: %ld.%d seconds\n", usage.ru_utime.tv_sec,
           usage.ru_utime.tv_usec);
    printf("Kernel mode CPU time: %ld.%d seconds\n", usage.ru_stime.tv_sec,
           usage.ru_stime.tv_usec);
  } else
    perror("getrusage");
  for (int i = 0; i < 9999999; i++)
    ;

  printf("\nAfter long running loop\n");
  if (getrusage(RUSAGE_SELF, &usage) == 0) {
    printf("User mode CPU time: %ld.%d seconds\n", usage.ru_utime.tv_sec,
           usage.ru_utime.tv_usec);
    printf("Kernel mode CPU time: %ld.%d seconds\n", usage.ru_stime.tv_sec,
           usage.ru_stime.tv_usec);
  } else
    perror("getrusage");

  return 0;
}
