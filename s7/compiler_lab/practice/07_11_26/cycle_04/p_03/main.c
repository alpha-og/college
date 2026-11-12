/*
 * E->E+E
 * E->E*E
 * E->(E)
 * E->i
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 24
char w[MAX_INPUT_LENGTH];
char stk[MAX_INPUT_LENGTH];
int top;
int idx;

void push(char item);
void pop();

int main() {
  memset(w, 0, MAX_INPUT_LENGTH);
  memset(stk, 0, MAX_INPUT_LENGTH);
  top = -1;
  idx = 0;

  fprintf(stdout, "Input string(w): ");
  fgets(w, MAX_INPUT_LENGTH, stdin);
  w[strcspn(w, "\n")] = '\0';

  fprintf(stdout, "%-10s %-24s %-10s\n", "Input", "Stack", "Action");

  int reduced = 1;
  while (reduced || w[idx] != '\0') {
    reduced = 0;
    if (w[idx] != '\0') {
      push(w[idx]);
      fprintf(stdout, "%-10s %-24s %-10s\n", w + idx, stk, "Shift");
      idx++;
    }

    if (top > -1 && stk[top] == 'i') {
      pop();
      push('E');
      reduced = 1;
      fprintf(stdout, "%-10s %-24s %-10s\n", w + idx, stk, "E->i");
    }

    if (top > 1 && stk[top] == 'E' && stk[top - 1] == '+' &&
        stk[top - 2] == 'E') {
      pop();
      pop();
      pop();
      push('E');
      reduced = 1;
      fprintf(stdout, "%-10s %-24s %-10s\n", w + idx, stk, "E->E+E");
    }

    if (top > 1 && stk[top] == 'E' && stk[top - 1] == '*' &&
        stk[top - 2] == 'E') {
      pop();
      pop();
      pop();
      push('E');
      reduced = 1;
      fprintf(stdout, "%-10s %-24s %-10s\n", w + idx, stk, "E->E*E");
    }

    if (top > 1 && stk[top] == ')' && stk[top - 1] == 'E' &&
        stk[top - 2] == '(') {
      pop();
      pop();
      pop();
      push('E');
      reduced = 1;
      fprintf(stdout, "%-10s %-24s %-10s\n", w + idx, stk, "E->(E)");
    }
  }
  if (w[idx] == '\0' && top == 0 && stk[top] == 'E') {
    fprintf(stdout, "Accepted: %s is a valid input string\n", w);
    exit(EXIT_SUCCESS);
  } else {
    fprintf(stdout, "Rejected: %s is not valid input string\n", w);
    exit(EXIT_FAILURE);
  }
}

void push(char item) { stk[++top] = item; }
void pop() {
  stk[top] = '\0';
  top--;
}
