/*
 * Experiment - 05
 * Input a string of parentheses and braces and determine if it forms a valid
 * string. An input string is valid if: Every open parenthesis "(". has a
 * corresponding close parenthesis ")". Open parentheses (braces) must be
 * closed in the correct order within a pair of paranthesis (with nesting)
 * Athul Anoop
 */

#include <stdio.h>
#define MAX_STRING_SIZE 100

int main() {
  char string[MAX_STRING_SIZE] = {'\0'};
  printf("Enter a string: ");
  char current = '\0';
  char *top = string;
  while ((current = fgetc(stdin)) != '\n') {
    if (current == ')') {
      char tmp[MAX_STRING_SIZE] = {'\0'};
      int index = 0;
      while (*top != '(' && top != string) {
        tmp[index] = *top;
        top = top - 1;
        index++;
      }
      for (int i = 0; i < index; i++) {
        printf("%c", tmp[index - i]);
      }
      printf(" ");
      top = top - 1;
    } else {
      *top = current;
      top = top + 1;
    }
  }
  printf("\n");
  return 0;
}
