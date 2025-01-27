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

  for (int i = 0; i < argc - 1; i++) {
    for (int j = 0; j < argc - i - 2; j++) {
      if (sorted[j + 1] < sorted[j]) {
        int tmp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = tmp;
      }
    }
  }
  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}
