/*
 * TAC to ASM
 *
 * 1. Read TAC one line at a time
 * 2. Initialize register count to rc=1 (selects R1 initially)
 * 2. If TAC is of the form x=y op z then,
 *      2.1 emit "MOV y, R_rc"
 *      2.2 emit "op z, R_rc" where op maybe "ADD", "SUB"
 *      2.3 emit "MOV R_rc, x"
 *      2.4 INCREMENT rc
 * 3. else if TAC is of the form x=y then,
 *      3.1 emit "MOV y, x" (y maybe a register)
 * 4. Quit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set_op(char, char *);
void validate_operand(int);

int main() {
  char output[32][128] = {};
  char input_buffer[64] = {};
  int input_length = 0;
  int rc = 1;
  int ic = 0;

  while (ic < 32 &&
         fgets(input_buffer, sizeof(input_buffer) - 1, stdin) != NULL) {
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    input_length = strlen(input_buffer);
    if (strcmp("exit", input_buffer) == 0) {
      fprintf(stdout, "Instructions\n");
      break;
    }
    char variables[3][32] = {};
    int vc = 1;
    int vi = 0;
    char op[4] = {};

    for (int i = 0; i < input_length; i++) {
      if (vc == 1 && input_buffer[i] == '=') {
        validate_operand(vi);
        vc++;
        vi = 0;
        continue;
      } else if (vc == 2) {
        if (set_op(input_buffer[i], op) > 0) {
          validate_operand(vi);

          vc++;
          vi = 0;
          continue;
        } else if (input_buffer[i] == '\0') {
          validate_operand(vi);
          break;
        }
      } else if (vc == 3 && input_buffer[i] == '\0') {
        validate_operand(vi);
        break;
      }
      variables[vc - 1][vi++] = input_buffer[i];
    }
    if (vc == 3) {
      snprintf(output[ic++], sizeof(output[0]) - 1, "MOV %s, R%d", variables[1],
               rc);
      snprintf(output[ic++], sizeof(output[0]) - 1, "%s %s, R%d", op,
               variables[2], rc);
      snprintf(output[ic++], sizeof(output[0]) - 1, "MOV R%d, %s", rc,
               variables[0]);
      rc++;
    } else {
      snprintf(output[ic++], sizeof(output[0]) - 1, "MOV %s, %s", variables[1],
               variables[0]);
    }
  }
  for (int i = 0; i < ic; i++) {
    fprintf(stdout, "%s\n", output[i]);
  }
  return 0;
}

int set_op(char c, char *op) {
  switch (c) {
  case '*':
    strcpy(op, "MUL");
    return 1;
  case '/':
    strcpy(op, "DIV");
    return 1;
  case '+':
    strcpy(op, "ADD");
    return 1;
  case '-':
    strcpy(op, "SUB");
    return 1;
  default:
    return 0;
  }
}

void validate_operand(int vi) {
  if (vi < 1) {
    fprintf(stderr, "Validation error: operand cannot be empty\n");
    exit(EXIT_FAILURE);
  }
}
