#include <stdio.h>
#include <stdlib.h>

int partition(int *, int, int);
void swap(int *, int, int);
void quick_sort(int *, int, int);

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

  quick_sort(sorted, 0, argc - 2);

  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}

void swap(int *array, int i, int j) {
  int tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

int partition(int *array, int low, int high) {
  int i = low - 1;
  int j = low;
  int pivot = high;
  while (j < pivot) {
    if (array[j] <= array[pivot]) {
      swap(array, j++, ++i);
    } else
      j++;
  }
  swap(array, ++i, j);
  return i;
}

void quick_sort(int *array, int low, int high) {
  if (low >= high)
    return;
  int pi = partition(array, low, high);
  quick_sort(array, low, pi - 1);
  quick_sort(array, pi + 1, high);
}
