#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *p_file = fopen("input.txt", "r");
  char result;
  char operand1;
  char operand2;
  char op;
  char output[16][64];
  int rc = 0;
  for (int idx = 0; idx < 16; idx++) {
    memset(output[idx], 0, 64);
  }

  int ic = 0;
  while (fscanf(p_file, " %c = %c %c %c ", &result, &operand1, &op,
                &operand2) != EOF) {
    char op_code[4] = {0};
    switch (op) {
    case '+':
      strcpy(op_code, "ADD");
      break;
    case '-':
      strcpy(op_code, "SUB");
      break;
    case '*':
      strcpy(op_code, "MUL");
      break;
    case '/':
      strcpy(op_code, "DIB");
      break;
    }
    snprintf(output[ic++], 63, "MOV %c, R%d", operand1, rc);
    snprintf(output[ic++], 63, "%s %c, R%d", op_code, operand2, rc);
    snprintf(output[ic++], 63, "MOV R%d, %c", rc, result);
    rc++;
  }
  for (int i = 0; i < ic; i++) {
    fprintf(stdout, "%s\n", output[i]);
  }
  return 0;
}
