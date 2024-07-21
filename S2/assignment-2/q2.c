// To print all occurrences of a substring in a string

#include <stdio.h>
#include <string.h>

int main() {
  int cap = 1000;
  char input[cap];
  char substring[cap];

  printf("Type something: ");
  scanf("%[^\n]%*c", input);

  printf("Provide the substring to search for: ");
  scanf("%[^\n]%*c", substring);

  int inputLength = strlen(input);
  int substringLength = strlen(substring);

  for (int i = 0; i < (inputLength - substringLength); i++) {
    int matched = 1;
    int matchIndex = -1;
    for (int j = 0; j < substringLength; j++) {
      if (input[i + j] == substring[j]) {
        if (j == 0) {
          matchIndex = i;
        }
      } else {
        matched = 0;
        break;
      }
    }
    if (matched) {
      printf("Substring found at index %d\n", matchIndex);
    }
  }
  return 0;
}
