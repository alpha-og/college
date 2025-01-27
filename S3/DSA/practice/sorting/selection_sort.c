#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (!(argc > 1)) {
    printf("Cannot sort empty array");
    exit(1);
  }
  int *sorted = calloc(argc - 1, sizeof(int));
  printf("Unsorted array: ");
  for (int i = 1; i < argc; i++) {
    int arg = atoi(argv[i]);
    printf("%d ", arg);
    sorted[i - 1] = arg;
  }

  printf("\n");

  for (int i = 0; i < argc - 2; i++) {
    int min = i;
    for (int j = i; j < argc - 1; j++) {
      if (sorted[min] > sorted[j]) {
        min = j;
      }
    }
    int tmp = sorted[i];
    sorted[i] = sorted[min];
    sorted[min] = tmp;
  }
  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}
