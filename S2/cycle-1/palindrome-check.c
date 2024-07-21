#include <stdio.h>
#include <string.h>

int main() {
  char input[1000];
  printf("Enter some text: ");
  scanf("%[^\n]%*c", input);
  int flag = 1;
  int inputLength = strlen(input);
  for (int i = 0; i < inputLength; i++) {
    if (input[i] != input[inputLength - i - 1]) {
      flag = 0;
      break;
    } else {
      continue;
    }
  }
  if (flag) {
    printf("Palindrome");
  } else {
    printf("Not a palindrome");
  }
  return 0;
}
