#include <stdio.h>

int factorial(int n) {
  if (n == 0) {
    return 1;
  }
  return n * factorial(n - 1);
}

int main() {
  int n = 0, result = 0;
  printf("Enter a number: ");
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    result += factorial(i) / i;
    if (i == n) {
      printf("%d!/%d = ", i, i);
    } else {
      printf("%d!/%d + ", i, i);
    }
  }
  printf("%d\n", result);
  return 0;
}
