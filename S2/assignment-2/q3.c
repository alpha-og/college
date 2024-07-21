// To replace all occurrences of a substring in a string with another string.

#include <stdio.h>
#include <string.h>

#define CAP 1000

int main() {
  char input[CAP];
  char substring[CAP];
  char replacement[CAP];
  char modified[CAP] = {'\0'};

  printf("Type something: ");
  scanf("%[^\n]%*c", input);

  printf("Provide the substring to replace: ");
  scanf("%[^\n]%*c", substring);

  printf("Specify the replacement: ");
  scanf("%[^\n]%*c", replacement);

  printf("Original: %s\n", input);

  int inputLength = strlen(input);
  int substringLength = strlen(substring);
  int replacementLength = strlen(replacement);

  int k = 0;
  int i = 0;
  for (; i < (inputLength - substringLength); i++) {
    int matched = 1;
    int position = -1;
    for (int j = 0; j < substringLength; j++) {
      if (input[i + j] == substring[j]) {
        if (j == 0) {
          position = i;
        }
        continue;
      } else {
        matched = 0;
        break;
      }
    }
    if (matched) {
      for (int j = 0; j < replacementLength; j++) {
        modified[k] = replacement[j];
        k++;
      }
      i = i + substringLength - 1;
    } else {
      modified[k] = input[i];
      k++;
    }
  }
  for (; i < inputLength; i++) {
    modified[k] = input[i];
    k++;
  }

  printf("Modified: %s\n", modified);
  return 0;
}
