#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 32

/*
 * E -> TE'
 * E' -> +TE'
 * E' -> e
 * T -> FT'
 * T' -> *FT'
 * T' -> e
 * F -> (E)
 * F -> i
 */

int E();
int E_prime();
int T();
int T_prime();
int F();

int idx;
char w[MAX_INPUT_LENGTH];

int main() {
  memset(w, 0, MAX_INPUT_LENGTH);

  fprintf(stdout, "Input String (w): ");
  fgets(w, MAX_INPUT_LENGTH - 1, stdin);
  w[strcspn(w, "\n")] = '\0';

  idx = 0;

  fprintf(stdout, "%-10s %s\n", "Input", "Action");
  if (E() < 0 || w[idx] != '\0') {
    fprintf(stdout, "rejected: %s is an invalid input\n", w);
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "accepted: %s is a valid input\n", w);
  return 0;
}

int E() {
  fprintf(stdout, "%-10s E->TE'\n", w + idx);
  if (T() < 0)
    return -1;
  if (E_prime() < 0)
    return -1;
  return 0;
}

int E_prime() {
  if (w[idx] == '+') {
    fprintf(stdout, "%-10s E'->+TE'\n", w + idx);
    idx++;
    if (T() < 0)
      return -1;
    if (E_prime() < 0)
      return -1;
    return 0;
  }
  fprintf(stdout, "%-10s E'->e\n", w + idx);
  return 0;
}

int T() {
  fprintf(stdout, "%-10s T->FT'\n", w + idx);
  if (F() < 0)
    return -1;
  if (T_prime() < 0)
    return -1;
  return 0;
}
int T_prime() {
  if (w[idx] == '*') {
    fprintf(stdout, "%-10s T'->*FT'\n", w + idx);
    idx++;
    if (F() < 0)
      return -1;
    if (T_prime() < 0)
      return -1;
    return 0;
  }
  fprintf(stdout, "%-10s T'->e\n", w + idx);
  return 0;
}

int F() {
  if (w[idx] == '(') {
    fprintf(stdout, "%-10s F->(E)\n", w + idx);
    idx++;
    if (E() < 0)
      return -1;
    if (w[idx] != ')')
      return -1;
    idx++;
    return 0;
  } else if (w[idx] == 'i') {
    fprintf(stdout, "%-10s F->i\n", w + idx);
    idx++;
    return 0;
  }
  return -1;
}
