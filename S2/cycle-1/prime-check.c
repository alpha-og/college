#include <stdbool.h>
#include <stdio.h>

int main() {
  int input = 0;
  bool flag = true;
  printf("Enter a number to check prime or not: ");
  scanf("%d", &input);
  for (int i = 2; i < (input / 2 + 1); i++) {
    if (input % i == 0) {
      flag = false;
      break;
    } else {
      continue;
    }
  }
  if (flag) {
    printf("Number is prime");
  } else {
    printf("Number is not prime");
  }
  return 0;
}
