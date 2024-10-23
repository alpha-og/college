#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int comparisons = 0; // global variable to count comparisons

// function to read numbers from a file
void read_numbers(const char *filename, int *arr, int *size) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

  *size = 0;
  while (fscanf(file, "%d", &arr[(*size)++]) == 1 && *size < MAX_SIZE)
    ;
  fclose(file);
}

// function for Insertion Sort
void insertion_sort(int *arr, int size) {
  comparisons = 0; // reset comparisons for this sort
  for (int i = 1; i < size; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      comparisons++;
      arr[j + 1] = arr[j];
      j--;
    }
    comparisons++; // count the last comparison when the loop exits
    arr[j + 1] = key;
  }
}

// function for Selection Sort
void selection_sort(int *arr, int size) {
  comparisons = 0; // reset comparisons for this sort
  for (int i = 0; i < size - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < size; j++) {
      comparisons++;
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[min_index];
    arr[min_index] = temp;
  }
}

// function for Heap Sort
void heapify(int *arr, int size, int root) {
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;

  if (left < size) {
    comparisons++;
    if (arr[left] > arr[largest]) {
      largest = left;
    }
  }

  if (right < size) {
    comparisons++;
    if (arr[right] > arr[largest]) {
      largest = right;
    }
  }

  if (largest != root) {
    int temp = arr[root];
    arr[root] = arr[largest];
    arr[largest] = temp;

    heapify(arr, size, largest);
  }
}

void heap_sort(int *arr, int size) {
  comparisons = 0; // reset comparisons for this sort
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(arr, size, i);
  }
  for (int i = size - 1; i > 0; i--) {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;

    heapify(arr, i, 0);
  }
}

// function for Merge Sort
void merge(int *arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int *L = malloc(n1 * sizeof(int));
  int *R = malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    comparisons++;
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < n1) {
    arr[k++] = L[i++];
  }

  while (j < n2) {
    arr[k++] = R[j++];
  }

  free(L);
  free(R);
}

void merge_sort(int *arr, int left, int right) {
  comparisons = 0; // reset comparisons for this sort
  if (left < right) {
    int mid = left + (right - left) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

// function for Quick Sort
int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    comparisons++;
    if (arr[j] < pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }

  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;

  return (i + 1);
}

void quick_sort(int *arr, int low, int high) {
  comparisons = 0; // reset comparisons for this sort
  if (low < high) {
    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

// function to print the array
void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// main function
int main() {
  int arr[MAX_SIZE];
  int size;

  // read numbers from file
  read_numbers("numbers.txt", arr, &size);

  // Insertion Sort
  int arr1[MAX_SIZE];
  for (int i = 0; i < size; i++)
    arr1[i] = arr[i]; // copy original array
  insertion_sort(arr1, size);
  printf("Insertion Sort: ");
  print_array(arr1, size);
  printf("Comparisons: %d\n", comparisons);

  // Selection Sort
  int arr2[MAX_SIZE];
  for (int i = 0; i < size; i++)
    arr2[i] = arr[i]; // copy original array
  selection_sort(arr2, size);
  printf("Selection Sort: ");
  print_array(arr2, size);
  printf("Comparisons: %d\n", comparisons);

  // Heap Sort
  int arr3[MAX_SIZE];
  for (int i = 0; i < size; i++)
    arr3[i] = arr[i]; // copy original array
  heap_sort(arr3, size);
  printf("Heap Sort: ");
  print_array(arr3, size);
  printf("Comparisons: %d\n", comparisons);

  // Merge Sort
  int arr4[MAX_SIZE];
  for (int i = 0; i < size; i++)
    arr4[i] = arr[i]; // copy original array
  merge_sort(arr4, 0, size - 1);
  printf("Merge Sort: ");
  print_array(arr4, size);
  printf("Comparisons: %d\n", comparisons);

  // Quick Sort
  int arr5[MAX_SIZE];
  for (int i = 0; i < size; i++)
    arr5[i] = arr[i]; // copy original array
  quick_sort(arr5, 0, size - 1);
  printf("Quick Sort: ");
  print_array(arr5, size);
  printf("Comparisons: %d\n", comparisons);

  return 0;
}
