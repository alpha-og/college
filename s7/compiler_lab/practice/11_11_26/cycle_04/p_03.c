#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 32

void push(char item);
char pop();
void display_state(const char *action);

char input[MAX_INPUT_LENGTH];
int cursor;

char stk[MAX_INPUT_LENGTH];
int top;

int main(int argc, char *argv[]) {
  if (argc < 1) {
    fprintf(stderr, "insufficient arguments: input string must be provided\n");
    exit(EXIT_FAILURE);
  }
  memset(input, 0, MAX_INPUT_LENGTH);
  cursor = 0;

  memset(stk, 0, MAX_INPUT_LENGTH);
  top = -1;

  strncpy(input, argv[1], MAX_INPUT_LENGTH);

  fprintf(stdout, "%-16s %-16s %-16s\n", "Input", "Stack", "Action");
  fprintf(stdout, "%-16s %-16s %-16s\n", input, "-", "-");
  int reduced = 1;
  while (reduced || input[cursor] != 0) {
    reduced = 0;
    if (input[cursor] != 0) {
      push(input[cursor++]);
      display_state("SHIFT");
    }

    if (stk[top] == 'd' && stk[top - 1] == 'i') {
      pop();
      pop();
      push('E');
      display_state("REDUCE { E->id }");
      reduced = 1;
    }
    if (stk[top] == ')' && stk[top - 1] == 'E' && stk[top - 2] == '(') {
      pop();
      pop();
      pop();
      push('E');
      display_state("REDUCE { E->(E) }");
      reduced = 1;
    }
    if (stk[top] == 'E' && stk[top - 1] == '+' && stk[top - 2] == 'E') {
      pop();
      pop();
      pop();
      push('E');
      display_state("REDUCE { E->E+E }");
      reduced = 1;
    }
    if (stk[top] == 'E' && stk[top - 1] == '*' && stk[top - 2] == 'E') {
      pop();
      pop();
      pop();
      push('E');
      display_state("REDUCE { E->E*E }");
      reduced = 1;
    }
  }
  if (top == 0 && stk[top] == 'E' && input[cursor] == 0) {
    fprintf(stdout, "input accepted: %s is a valid string\n", input);
    return EXIT_SUCCESS;
  } else {

    fprintf(stderr, "input rejected: %s is not a valid string\n", input);
    return EXIT_FAILURE;
  }
}

void push(char item) {
  if (top + 1 == MAX_INPUT_LENGTH) {
    fprintf(stderr, "insufficient memory: stack overflow\n");
    exit(EXIT_FAILURE);
  }
  stk[++top] = item;
}

char pop() {
  if (top < 0) {
    fprintf(stderr, "insufficient contents: stack underflow\n");
    exit(EXIT_FAILURE);
  }
  stk[top] = 0;
  return stk[top--];
}

void display_state(const char *action) {
  fprintf(stdout, "%-16s %-16s %-16s\n", input + cursor, stk, action);
  return;
}
