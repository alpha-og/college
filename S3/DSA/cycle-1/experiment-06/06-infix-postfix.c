/*
 * Experiment - 06
 * Write a menu-driven program for the following operations:
 * Convert an infix expression to a postfix expression.
 * Evaluate the postfix expression.
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void display_menu();
void handle_choice(char *expression);
int precedence(char operand);
void convert_infix_to_postfix(char *expression);
// void evaluate_postfix(char *expression);

int main() {
  char expression[MAX] = {'\0'};
  while (1) {
    display_menu();
    handle_choice(expression);
  }
}

void display_menu() {
  printf("\n---- Menu ----\n");
  printf("1. Convert infix to postfix\n");
  printf("2. Evaluate postfix\n");
  printf("3. Exit\n");
  printf("Choice: ");
}

void handle_choice(char *expression) {
  int choice;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    convert_infix_to_postfix(expression);
    break;
  case 2:
    // evaluate_postfix(expression);
    break;
  case 3:
    printf("\nExiting...\n");
    exit(0);
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}

void convert_infix_to_postfix(char *expression) {
  char tmp[MAX] = {'\0'};
  char ch = {'\0'};
  char *topTmp = tmp;
  char *topExp = expression;
  int isTerm = 0;
  getchar();
  while (ch != '\n') {
    ch = getchar();
    if (ch >= '0' && ch <= '9') {
      if (isTerm == 0) {
        *topExp = ' ';
        topExp = topExp + 1;
        isTerm = 1;
      }
      *topExp = ch;
      topExp = topExp + 1;

    } else if (ch == ')') {
      while (*topTmp != '(') {
        *topExp = ' ';
        topExp = topExp + 1;
        *topExp = *topTmp;
        topExp = topExp + 1;
        topTmp = topTmp + 1;
      }
      *topTmp = '\0';
    } else if (ch == '(') {
      if (isTerm == 1) {
        *topTmp = ' ';
        topTmp = topTmp + 1;
        isTerm = 0;
      }
      *topTmp = ch;
      topTmp = topTmp + 1;
    } else {
      if (precedence(ch) >= precedence(*(topTmp - 1))) {
      }
    }
    while (topTmp != tmp) {
      *topExp = ' ';
      topExp = topExp + 1;
      *topExp = *topTmp;
      topExp = topExp + 1;
      topTmp = topTmp + 1;
    }
    printf("Tmp: %s\n", tmp);
    printf("Expression: %s\n", expression);
  }
}
int precedence(char operand) {
  if (operand == '+' || operand == '-')
    return 0;
  else if (operand == '*' || operand == '/')
    return 1;
  else if (operand == '^')
    return 2;
  else
    return -1;
}
