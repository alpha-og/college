#include <stdio.h>

int main() {
  int input = 0;
  int digitCount = 0;

  printf("Enter a number to check armstrong or not: ");
  scanf("%d", &input);

  int tmp = input;
  while (tmp > 0) {
    digitCount++;
    tmp = tmp / 10;
  }

  int result = 0;
  tmp = input;
  while (tmp > 0) {
    int currentDigit = tmp % 10;
    tmp = tmp / 10;
    int tmpPow = 1;
    for (int i = 0; i < digitCount; i++) {
      tmpPow *= currentDigit;
    }
    result += tmpPow;
  }

  if (result == input) {
    printf("%d is an armstrong number\n", input);
  } else {
    printf("%d is not an armstrong number\n", input);
  }
  return 0;
}
