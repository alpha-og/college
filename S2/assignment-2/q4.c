// to reverse a string

#include <stdio.h>
#include <string.h>

#define CAP 1000

int main() {
  char input[CAP];
  printf("Type some text: ");
  scanf("%[^\n]%*c", input);

  int inputLength = strlen(input);

  printf("Original: %s\n", input);
  for (int i = 0; i < inputLength / 2; i++) {
    char tmp = input[i];
    input[i] = input[inputLength - 1 - i];
    input[inputLength - 1 - i] = tmp;
  }
  printf("Modified: %s\n", input);
  return 0;
}
