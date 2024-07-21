// Write a program that takes a binary number as input and converts it to
// decimal.

#include <math.h>
#include <stdio.h>

int main() {
  int binary = 0, decimal = 0;
  printf("Enter a binary number: ");
  scanf("%d", &binary);

  for (int i = 0; binary > 0; i++) {
    decimal += (binary % 10) * pow(2, i);
    binary /= 10;
  }
  printf("Decimal representation is %d\n", decimal);
  return 0;
}
