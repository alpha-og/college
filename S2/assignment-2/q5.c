// To check if a string is palindrome.

#include <stdio.h>
#include <string.h>

#define CAP 1000

int main() {
  char input[CAP];
  printf("Type some text: ");
  scanf("%[^\n]%*c", input);

  int inputLength = strlen(input);
  char original[CAP];
  strcpy(original, input);

  for (int i = 0; i < inputLength / 2; i++) {
    char tmp = input[i];
    input[i] = input[inputLength - 1 - i];
    input[inputLength - 1 - i] = tmp;
  }

  if (strcmp(original, input) == 0) {
    printf("Given string is a palindrome");
  } else {
    printf("Given string is not a palindrome");
  }

  return 0;
}
