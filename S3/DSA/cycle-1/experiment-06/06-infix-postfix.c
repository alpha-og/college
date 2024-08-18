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
void handle_choice(char **expression);
void push(char *end, char **top, char ch);
char pop(char *start, char **top);
int precedence(char operand);
void convert_infix_to_postfix(char **expression);
void evaluate_postfix(char **expression);
void operate(int *index, int *tokens, char operator);

int main() {
  char *expression = (char *)calloc(MAX, sizeof(char));
  while (1) {
    display_menu();
    handle_choice(&expression);
  }
}

void display_menu() {
  printf("\n---- Menu ----\n");
  printf("1. Convert infix to postfix\n");
  printf("2. Evaluate postfix\n");
  printf("3. Exit\n");
  printf("Choice: ");
}

void handle_choice(char **expression) {
  int choice;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    convert_infix_to_postfix(expression);
    break;
  case 2:
    evaluate_postfix(expression);
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

void push(char *end, char **top, char ch) {
  if (**top == '\0') {
    **top = ch;
    return;
  }
  if (*top != end) {
    *top = *top + 1;
    **top = ch;
  }
}

char pop(char *start, char **top) {
  char tmp = **top;
  **top = '\0';
  if (*top != start)
    *top = *top - 1;
  return tmp;
}

void convert_infix_to_postfix(char **expression) {
  char tmp[MAX] = {'\0'};
  char ch = {'\0'};
  char *topTmp = tmp;
  *expression = calloc(MAX, sizeof(char));
  char *topExp = *expression;
  int isTerm = 0;
  getchar();
  while (ch != '\n') {
    ch = getchar();
    if (ch >= '0' && ch <= '9') {
      if (isTerm == 0) {
        if (*topExp != '\0') {
          push(*expression + MAX, &topExp, ' ');
        }
        isTerm = 1;
      }
      push(*expression + MAX, &topExp, ch);
    } else if (ch == ')') {
      isTerm = 0;
      while (*topTmp != '(') {
        push(*expression + MAX, &topExp, ' ');
        push(*expression + MAX, &topExp, pop(tmp, &topTmp));
      }
      pop(tmp, &topTmp);
    } else if (ch == '(') {
      isTerm = 0;
      push(tmp + MAX, &topTmp, ch);
    } else if (ch == '\n') {
      while (topTmp != tmp) {
        push(*expression + MAX, &topExp, ' ');
        push(*expression + MAX, &topExp, pop(tmp, &topTmp));
      }
      push(*expression + MAX, &topExp, ' ');
      push(*expression + MAX, &topExp, pop(tmp, &topTmp));
    } else {
      isTerm = 0;
      while (*topTmp != '\0' && precedence(ch) <= precedence(*topTmp)) {
        push(*expression + MAX, &topExp, ' ');
        push(*expression + MAX, &topExp, pop(tmp, &topTmp));
      }
      push(tmp + MAX, &topTmp, ch);
    }
  }
  printf("Final Expression: %s\n", *expression);
}

void evaluate_postfix(char **expression) {
  int *tokens = (int *)calloc(MAX, sizeof(int));
  int index = -1;
  char *current = *expression;
  while (*current != '\0') {
    if (*current >= '0' && *current <= '9') {
      char token[MAX] = {'\0'};
      char *topToken = token;
      while (*current != ' ') {
        push(token + MAX, &topToken, *current);
        current = current + 1;
      }
      index++;
      sscanf(token, "%d", &tokens[index]);
    } else if (*current == ' ') {
      current = current + 1;
      continue;
    } else {

      operate(&index, tokens, *current);
      current = current + 1;
    }
  }
  printf("Evaluated Expression: %d\n", tokens[0]);
}

void operate(int *index, int *tokens, char operator) {
  int result = 0;
  switch (operator) {
  case '-':
    result = tokens[*index - 1] - tokens[*index];
    break;
  case '+':
    result = tokens[*index - 1] + tokens[*index];
    break;
  case '*':
    result = tokens[*index - 1] * tokens[*index];
    break;
  case '/':
    result = tokens[*index - 1] / tokens[*index];
    break;
  default:
    fprintf(stderr, "ERROR: Invalid operator! Exiting...");
    exit(1);
    break;
  }
  tokens[*index] = 0;
  *index = *index - 1;
  tokens[*index] = result;
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
