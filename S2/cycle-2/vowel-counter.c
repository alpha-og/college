// Read a string (ending with a $ symbol), store it in an array and count the
// number of vowels,

#include <stdio.h>

int main() {
  char str[1000] = {'\0'};
  int vowelCount = 0;
  printf("Enter the string: ");
  scanf("%s", str);

  for (int i = 0; str[i] != '\0'; i++) {
    switch (str[i]) {
    case 'a':
      vowelCount += 1;
      break;
    case 'e':
      vowelCount += 1;
      break;
    case 'i':
      vowelCount += 1;
      break;
    case 'o':
      vowelCount += 1;
      break;
    case 'u':
      vowelCount += 1;
      break;
    default:
      break;
    }
  }
  printf("Number of vowels: %d\n", vowelCount);

  return 0;
}
