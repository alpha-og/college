// To replace all occurrences of a specified character in a string with another
// character.

#include <stdio.h>

int main() {
  int cap = 1000;
  char input[cap];
  printf("Type some text: ");
  scanf("%[^\n]%*c", input);

  char replace;
  char replacement;
  printf("Specify the character to be replaced and the corresponding "
         "replacement: ");
  scanf("%c,%c", &replace, &replacement);
  printf("Original: %s\n", input);

  for (int i = 0; i < cap; i++) {
    if (input[i] == replace) {
      input[i] = replacement;
    }
  }
  printf("Modified: %s\n", input);
  return 0;
}
