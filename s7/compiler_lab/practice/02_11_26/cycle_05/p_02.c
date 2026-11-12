/* ICG for simple expressions
 *
 * 1. Read expression
 * 2. For each binary operator in decreasing order of precedence,
 *      3.1 identify the operands and replace the combination of operands and
 *          operator with a temporary variable (destination)
 *      3.2 emit the corresponding three address code containing operator,
 *          destination, operand1 and operand2
 * 3. Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void emit_tac(char *, char);

char tmp_var = 'Z';

int main() {
  fprintf(stdout, "Expression>> ");
  char input_buffer[64] = {};
  fgets(input_buffer, sizeof(input_buffer) - 1, stdin);
  input_buffer[strcspn(input_buffer, "\n")] = '\0';

  fprintf(stdout, "Operator Destination Operand 1 Operand 2\n");
  emit_tac(input_buffer, '*');
  emit_tac(input_buffer, '/');
  emit_tac(input_buffer, '+');
  emit_tac(input_buffer, '-');
  emit_tac(input_buffer, '=');

  return EXIT_SUCCESS;
}

void emit_tac(char *expression, char op) {
  while (1) {
    int found = 0;
    int j = 0;
    for (int i = j; i < strlen(expression); i++) {
      if (!found && *(expression + i) == op) {
        fprintf(stdout, "%c: %s\n", op, expression);
        fprintf(stdout, "%-8c %-11c %-9c %-9c\n", op, tmp_var,
                expression[i - 1], expression[i + 1]);
        expression[i - 1] = tmp_var;
        i += 1;
        tmp_var--;
        found = 1;
        continue;
      }
      expression[j] = expression[i];
      j++;
    }
    expression[j] = '\0';
    if (!found)
      break;
  }
}
