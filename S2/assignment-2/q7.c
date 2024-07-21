// Write a program to print the Fibonacci series of n numbers using recursion

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
  int n = 0;
  printf("Enter the number of terms: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("%d, ", fib(i));
  }
    printf("\n");
}
