// Write a program that takes a number of terms as input and prints the
// Fibonacci series up to that number of terms.

#include <stdio.h>

int fib(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

int main() {
  int n;
  printf("Enter the number of terms: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("%d ", fib(i));
  }
  printf("\n");
  return 0;
}
