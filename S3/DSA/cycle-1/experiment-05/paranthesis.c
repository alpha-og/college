/*
 * Experiment - 05
 * Input a string of parentheses and braces and determine if it forms a valid
 * string. An input string is valid if: Every open parenthesis "(". has a
 * corresponding close parenthesis ")". Open parentheses (braces) must be
 * closed in the correct order within a pair of paranthesis (with nesting)
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
  char *elements;
  char *top;
} Stack;

void push(Stack *stack, char ch);
char pop(Stack *stack);

int main() {
  Stack *stack = (Stack *)calloc(1, sizeof(Stack));
  stack->elements = (char *)calloc(MAX, sizeof(char));
  stack->top = stack->elements;
  char ch = '\0';
  int is_valid = 1;
  while ((ch = fgetc(stdin)) != '\n') {
    if (ch == '(' || ch == '{') {
      push(stack, ch);
    } else {
      if (ch == ')') {
        if (*(stack->top) == '(')
          pop(stack);
        else {
          is_valid = 0;
          break;
        }
      } else if (ch == '}') {
        if (*(stack->top) == '{')
          pop(stack);
        else {
          is_valid = 0;
          break;
        }
      }
    }
  }
  if (is_valid)
    fprintf(stdout, "\nGiven string is valid\n");
  else
    fprintf(stdout, "\nGiven string is invalid\n");
  return 0;
}

void push(Stack *stack, char ch) {
  if (stack->top == stack->elements + MAX - 1) {
    fprintf(stderr, "ERROR: Stack overflow. Exiting...\n");
    exit(1);
  } else {
    if (*(stack->elements) != '\0')
      stack->top = stack->top + 1;
    *(stack->top) = ch;
  }
}

char pop(Stack *stack) {
  if (stack->top == stack->elements)
    return '\0';
  char tmp = *(stack->top);
  *(stack->top) = '\0';
  stack->top = stack->top - 1;
  return tmp;
}
