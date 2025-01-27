#include <stdio.h>
#include <stdlib.h>

void heapify(int *, int, int);
void build_heap(int *, int);
void heap_sort(int *, int);

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
  build_heap(sorted, argc - 1);
  heap_sort(sorted, argc - 1);

  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}

void heapify(int *array, int size, int root) {
  int left_child = 2 * root + 1;
  int right_child = 2 * root + 2;
  int largest = root;
  if (left_child < size && array[largest] < array[left_child])
    largest = left_child;
  if (right_child < size && array[largest] < array[right_child])
    largest = right_child;
  if (largest != root) {
    int tmp = array[root];
    array[root] = array[largest];
    array[largest] = tmp;
    heapify(array, size, largest);
  }
}

void build_heap(int *array, int size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, size, i);
  }
}

void heap_sort(int *array, int size) {
  if (size == 0)
    return;
  int tmp = array[0];
  array[0] = array[size - 1];
  array[size - 1] = tmp;
  heapify(array, size - 1, 0);
  heap_sort(array, size - 1);
}
