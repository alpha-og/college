#include <stdio.h>

int main() {
  int n = 0;
  printf("Enter number of integers: ");
  scanf("%d", &n);
  int arr[n];

  for (int i = 0; i < n; i++) {
    printf("Enter a number: ");
    scanf("%d", arr + i);
  }
  printf("Input array: ");
  for (int i = 0; i < n; i++) {
    printf("%d,", arr[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = tmp;
      }
    }
  }
  printf("Output array: ");
  for (int i = 0; i < n; i++) {
    printf("%d,", arr[i]);
  }

  return 0;
}
