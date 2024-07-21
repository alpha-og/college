// Read two strings (each one ending with a $ symbol), store them in arrays and
// concatenate them without using library functions.

#include <stdio.h>

int main() {
  char str1[1000] = {'\0'};
  char str2[1000] = {'\0'};

  printf("Enter the first string: ");
  scanf("%[^\n]%*c", str1);
  printf("Enter the second string: ");
  scanf("%[^\n]%*c", str2);
  char result[2000] = {'\0'};
  int i = 0;
  for (; str1[i] != '\0'; i++) {
    result[i] = str1[i];
  }
  int str1Len = i;

  for (; str2[i - str1Len] != '\0'; i++) {
    result[i] = str2[i - str1Len];
  }
  printf("%s", result);
  printf("\n");

  return 0;
}
