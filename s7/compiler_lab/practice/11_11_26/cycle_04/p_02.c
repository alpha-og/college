#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 32

/*
 * E->TE'
 * E'->+TE'
 * E'->e
 * T->FT'
 * T'->*FT'
 * T'->e
 * F->(E)
 * F->i
 */

int E();
int E_prime();
int T();
int T_prime();
int F();
void display_state(const char *action);

char input[MAX_INPUT_LENGTH];
int cursor;

int main(int argc, char *argv[]) {
  if (argc < 1) {
    fprintf(stderr, "insufficient argument: input string must be provided\n");
    exit(EXIT_FAILURE);
  }
  memset(input, 0, MAX_INPUT_LENGTH);
  strncpy(input, argv[1], MAX_INPUT_LENGTH);
  cursor = 0;
  fprintf(stdout, "%-16s %-16s\n", "Input", "Action");
  if (E()) {
    fprintf(stderr, "input rejected: %s does not satisfy grammar\n", input);
    exit(EXIT_FAILURE);
  }
  fprintf(stdout,
          "input accepted: %s is a valid string satisfying the grammar\n",
          input);
  exit(EXIT_SUCCESS);
}

void display_state(const char *action) {
  fprintf(stdout, "%-16s %-16s\n", input + cursor, action);
  return;
}

int E() {
  display_state("E->TE'");
  if (T())
    return 1;
  if (E_prime())
    return 1;
  return 0;
}
int E_prime() {
  if (input[cursor] == '+') {
    cursor++;
    display_state("E'->+TE'");
    if (T())
      return 1;
    if (E_prime())
      return 1;
  }
  display_state("E'->e");
  return 0;
}
int T() {
  display_state("T->FT'");
  if (F())
    return 1;
  if (T_prime())
    return 1;
  return 0;
}
int T_prime() {
  if (input[cursor] == '*') {
    cursor++;
    display_state("T'->*FT'");
    if (T())
      return 1;
    if (E_prime())
      return 1;
  }
  display_state("T'->e");
  return 0;
}
int F() {
  if (input[cursor] == '(') {
    display_state("F->(E)");
    cursor++;
    if (E())
      return 1;
    if (input[cursor] == ')') {
      cursor++;
      return 0;
    }
  } else if (input[cursor] == 'i') {
    display_state("F->i");
    cursor++;
    return 0;
  }
  return 1;
}
