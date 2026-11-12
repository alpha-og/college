#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDENTS 16
#define MAX_INPUT_LENGTH 16
#define MAX_EQUATONS 16
#define MAX_OUTPUT_LENGTH 64

char idents[MAX_IDENTS];
int values[MAX_IDENTS];
char input_buffer[MAX_INPUT_LENGTH];
char outputs[MAX_EQUATONS][MAX_OUTPUT_LENGTH];

int find_ident(char ident);
int add_ident(char ident);
int update_ident_value(char ident, int value);
int get_ident_value(char ident);
int is_operator(char ch);
int calc(int value1, int value2, char op);

int main() {
  memset(idents, 0, MAX_IDENTS);
  memset(values, -1, sizeof(int) * MAX_IDENTS);
  memset(input_buffer, 0, MAX_INPUT_LENGTH);
  for (int idx = 0; idx < MAX_EQUATONS; idx++) {
    memset(outputs[idx], 0, MAX_OUTPUT_LENGTH);
  }

  int equation_idx = 0;
  FILE *p_file = fopen("input.txt", "r");

  while (fgets(input_buffer, sizeof(input_buffer) - 1, p_file) != NULL) {
    input_buffer[strcspn(input_buffer, "\n")] = '\0';

    char result = '\0';
    char op = '\0';
    char token1[MAX_INPUT_LENGTH] = {0};
    char token2[MAX_INPUT_LENGTH] = {0};

    int parsed = sscanf(input_buffer, " %c = %15[^+-*/] %c %15s", &result,
                        token1, &op, token2);
    if (parsed < 2) {
      fprintf(stderr, "invalid equation: %s\n", input_buffer);
      exit(EXIT_FAILURE);
    }

    add_ident(result);

    if (parsed == 2) {
      // Assignment of single value or variable: e.g., a = 30 or d = a
      int value;
      char *endptr;
      long val = strtol(token1, &endptr, 10);

      if (endptr == token1) {
        // It's a variable identifier
        value = get_ident_value(token1[0]);
      } else {
        // It's an integer literal
        value = (int)val;
      }

      update_ident_value(result, value);
      snprintf(outputs[equation_idx++], MAX_OUTPUT_LENGTH - 1, "%s = %d",
               input_buffer, value);

    } else if (parsed == 4) {
      // Binary operation: e.g., b = 2 + a
      int val1, val2;
      char *endptr;

      // Operand 1
      long l1 = strtol(token1, &endptr, 10);
      if (endptr == token1) {
        val1 = get_ident_value(token1[0]);
      } else {
        val1 = (int)l1;
      }

      // Operand 2
      long l2 = strtol(token2, &endptr, 10);
      if (endptr == token2) {
        val2 = get_ident_value(token2[0]);
      } else {
        val2 = (int)l2;
      }

      int value = calc(val1, val2, op);
      update_ident_value(result, value);
      snprintf(outputs[equation_idx++], MAX_OUTPUT_LENGTH - 1,
               "%s = %d %c %d = %d", input_buffer, val1, op, val2, value);
    }
    memset(input_buffer, 0, MAX_INPUT_LENGTH);
  }

  for (int idx = 0; idx < equation_idx; idx++) {
    fprintf(stdout, "%s\n", outputs[idx]);
  }
  return 0;
}

int calc(int value1, int value2, char op) {
  if (!is_operator(op)) {
    fprintf(stderr, "invalid operator: '%c'\n", op);
  }
  switch (op) {
  case '+':
    return value1 + value2;
  case '-':
    return value1 - value2;
  case '*':
    return value1 * value2;
  case '/':
    return value1 / value2;
  default:
    return -1;
  }
}

int is_operator(char ch) {
  switch (ch) {
  case '+':
  case '-':
  case '*':
  case '/':
    return 1;
  default:
    return 0;
  }
}

int find_ident(char ident) {
  int idx = 0;
  while (idx < MAX_IDENTS && idents[idx] != '\0') {
    if (idents[idx] == ident)
      return idx;
    idx++;
  }
  return -1;
}

int add_ident(char ident) {
  int idx = find_ident(ident);
  if (idx >= 0)
    return idx;
  idx = 0;
  while (idx < MAX_IDENTS && idents[idx] != '\0') {
    idx++;
  }
  if (idx == MAX_IDENTS)
    return -1;
  idents[idx] = ident;
  return idx;
}

int get_ident_value(char ident) {
  int ident_idx = find_ident(ident);
  if (ident_idx < 0) {
    fprintf(stderr, "undefined identifier\n");
    return -1;
  }
  return values[ident_idx];
}

int update_ident_value(char ident, int value) {
  int ident_idx = find_ident(ident);
  if (ident_idx < 0) {
    fprintf(stderr, "undefined identifier\n");
    return -1;
  }
  int old_value = values[ident_idx];
  values[ident_idx] = value;
  return old_value;
}
