#include <stdio.h>
#include <string.h>

#define MAX_LEN 16
#define MAX_INSTRUCTIONS 32

char output[MAX_INSTRUCTIONS][MAX_LEN];
int ic;
int rc;

int main() {
  FILE *p_file = fopen("p_03_input.txt", "r");

  int idx = 0;
  while (idx < MAX_INSTRUCTIONS) {
    memset(output[idx], 0, MAX_LEN);
    idx++;
  }

  ic = 0;

  char var1;
  char var2;
  char var3;
  char op;
  int parsed = 0;
  while ((parsed = fscanf(p_file, " %c = %c %c %c ", &var1, &var2, &op,
                          &var3)) != EOF) {
    if (parsed == 2) {
      snprintf(output[ic++], MAX_LEN, "MOV %c, %c", var2, var1);
    } else if (parsed == 4) {
      char opcode[8] = {0};
      switch (op) {
      case '*':
        strcpy(opcode, "MUL");
        break;
      case '/':
        strcpy(opcode, "DIV");
        break;
      case '+':
        strcpy(opcode, "ADD");
        break;
      case '-':
        strcpy(opcode, "SUB");
        break;
      default:
        fprintf(stderr, "invalid operator: %c", op);
        return -1;
      }
      snprintf(output[ic++], MAX_LEN, "MOV %c, R%d", var2, rc);
      snprintf(output[ic++], MAX_LEN, "%s %c, R%d", opcode, var3, rc);
      snprintf(output[ic++], MAX_LEN, "MOV R%d, %c", rc++, var1);
    }
  }

  idx = 0;
  while (idx < MAX_INSTRUCTIONS && output[idx][0] != 0) {
    fprintf(stdout, "%-4d %-16s\n", idx, output[idx]);
    idx++;
  }
  return 0;
}
