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
    int element = sorted[i];
    int j = i - 1;
    while (j >= 0 && sorted[j] > element) {
      sorted[j + 1] = sorted[j];
      j--;
    }
    sorted[j + 1] = element;
  }
  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}
