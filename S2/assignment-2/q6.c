// To insert a string into another string at a specified position

#include <stdio.h>
#include <string.h>

#define CAP 1000

int main() {
  char input[CAP];
  printf("Type some text: ");
  scanf("%[^\n]%*c", input);

  int position = 0;
  char insertion[CAP];
  printf("Provide the string to be inserted: ");
  scanf("%[^\n]%*c", insertion);

  printf("Provide the position for inserting string: ");
  scanf("%d", &position);

  char modifiedText[1000];
  int inserted = 0;
  for (int i = 0; i < CAP; i++) {
    if (i == position) {
      for (int j = 0; j < strlen(insertion); j++) {
        modifiedText[i + j] = insertion[j];
      }
      inserted = 1;

    } else {
      if (inserted == 1) {
        modifiedText[i + strlen(insertion) - 1] = input[i - 1];
      } else {
        modifiedText[i] = input[i];
      }
    }
  }

  printf("Original: %s\n", input);

  printf("Modified: %s\n", modifiedText);
  return 0;
}
