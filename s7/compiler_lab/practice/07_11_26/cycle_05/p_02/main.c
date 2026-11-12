#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *expression;
char temporary_variable = 'Z';

void generate();
void generate_code(char op);

int main(int argc, char *argv[]) {
  if (argc < 1) {
    fprintf(stderr, "insufficient arguments: equation cannot be empty\n");
    exit(EXIT_FAILURE);
  }
  expression = argv[1];
  fprintf(stdout, "%-10s %-10s %-10s %-10s\n", "Result", "Operator",
          "Operand 1", "Operand 2");
  generate();
}

void generate() {
  generate_code('*');
  generate_code('/');
  generate_code('+');
  generate_code('-');
  generate_code('=');
}
void generate_code(char op) {
  int idx = 0;
  while (idx < strlen(expression)) {
    if (expression[idx] == op) {
      fprintf(stdout, "%-10c %-10c %-10c %-10c\n", temporary_variable, op,
              expression[idx - 1], expression[idx + 1]);
      expression[idx - 1] = temporary_variable--;
      int swap_idx = idx;
      int next_idx = idx + 2;
      while (next_idx < strlen(expression)) {
        expression[swap_idx++] = expression[next_idx++];
      }
      expression[swap_idx] = '\0';
    }
    idx++;
  }
}
