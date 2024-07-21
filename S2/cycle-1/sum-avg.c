#include <stdio.h>

int main() {
  int n = 0;
  float sum = 0;
  float avg = 0;
  printf("Enter number of integers: ");
  scanf("%d", &n);
  int arr[n];

  for (int i = 0; i < n; i++) {
    printf("Enter a number: ");
    scanf("%d", arr + i);
  }

  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }
  avg = sum / n;

  printf("Sum: %f\n", sum);
  printf("Average: %f", avg);
}
