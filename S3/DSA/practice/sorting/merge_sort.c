#include <stdio.h>
#include <stdlib.h>

void merge(int *, int, int, int);
void merge_sort(int *, int, int);

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

  merge_sort(sorted, 0, argc - 2);

  printf("Sorted array: ");
  for (int i = 0; i < argc - 1; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");
}

void merge(int *array, int low, int mid, int high) {
  int l_count = mid - low + 1;
  int r_count = high - mid;
  int *l = calloc(l_count, sizeof(int));
  int *r = calloc(r_count, sizeof(int));
  for (int i = 0; i < l_count; i++) {
    l[i] = array[low + i];
  }
  for (int i = 0; i < r_count; i++) {
    r[i] = array[mid + 1 + i];
  }
  int i = 0;
  int j = 0;
  int k = low;
  while (i < l_count && j < r_count) {
    if (l[i] < r[j])
      array[k++] = l[i++];
    else
      array[k++] = r[j++];
  }
  while (i < l_count) {
    array[k++] = l[i++];
  }
  while (j < r_count) {
    array[k++] = r[j++];
  }
  free(l);
  free(r);
}

void merge_sort(int *array, int low, int high) {
  if (low >= high)
    return;
  int mid = low + (high - low) / 2;
  merge_sort(array, low, mid);
  merge_sort(array, mid + 1, high);
  merge(array, low, mid, high);
}
