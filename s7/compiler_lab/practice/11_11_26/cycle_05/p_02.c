#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 32

void generate();
void gen_code(const char);

char input[MAX_INPUT_LENGTH] = {0};
char reg = 'Z';

int main(int argc, char *args[]) {
  if (argc < 1) {
    fprintf(stderr, "insufficient arguments: expression cannot be empty\n");
  }
  strncpy(input, args[1], MAX_INPUT_LENGTH - 1);
  fprintf(stdout, "%-10s %-10s %-10s %-10s\n", "Operator", "Operand 1",
          "Operand 2", "Result");
  generate();
  return 0;
}

void generate() {
  gen_code('*');
  gen_code('/');
  gen_code('+');
  gen_code('-');
  gen_code('=');
}

void gen_code(const char op) {
  int idx = 0;
  while (idx < strlen(input)) {
    if (input[idx] == op) {
      fprintf(stdout, "%-10c %-10c %-10c %-10c\n", op, input[idx - 1],
              input[idx + 1], reg);
      input[idx - 1] = reg--;
      int swap_idx = idx;
      int next_idx = idx + 2;
      while (next_idx < strlen(input)) {
        input[swap_idx++] = input[next_idx++];
      }
      input[swap_idx] = '\0';
      continue;
    }
    idx++;
  }
}
