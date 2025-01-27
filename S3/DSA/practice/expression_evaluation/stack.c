#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct Stack {
  int top;
  char array[MAX_SIZE];
} Stack;

Stack *create_stack();
void push(Stack *, char);
char pop(Stack *);
char peek(Stack *);
int get_precedence(char);
int evaluate(char *);

int main() {
  Stack *postfix = create_stack();
  Stack *tmp = create_stack();
  printf("Infix expression: ");
  char ch = '\0';
  while ((ch = getchar()) != '\n') {
    if (isdigit(ch)) {
      push(postfix, ch);
    } else {
      if (ch == '(')
        push(tmp, ch);
      else if (ch == ')') {
        while (tmp->top != -1 && peek(tmp) != '(') {
          push(postfix, pop(tmp));
        }
        pop(tmp);

      } else {
        while (tmp->top != -1 && peek(tmp) != '(' &&
               get_precedence(peek(tmp)) >= get_precedence(ch)) {
          push(postfix, pop(tmp));
        }
        push(tmp, ch);
      }
    }
  }
  while (tmp->top != -1) {
    push(postfix, pop(tmp));
  }
  push(postfix, '\0');
  printf("Postfix expression: %s\n", postfix->array);
  int result = evaluate(postfix->array);
  printf("Result: %d\n", result);
}

Stack *create_stack() {
  Stack *stack = calloc(1, sizeof(Stack));
  stack->top = -1;
  return stack;
}

void push(Stack *stack, char data) { stack->array[++(stack->top)] = data; }
char pop(Stack *stack) { return stack->array[stack->top--]; }
char peek(Stack *stack) { return stack->array[stack->top]; }
int get_precedence(char operator) {
  if (operator== '*' || operator== '/')
    return 2;
  else if (operator== '+' || operator== '-')
    return 1;
  else
    return -1;
}
int evaluate(char *postfix) {
  int result[MAX_SIZE];
  int top = -1;
  int i = 0;
  char ch = postfix[i];
  do {
    printf("%c\n", ch);
    if (isdigit(ch))
      result[++top] = ch - '0';
    else {
      int operand1 = result[top];
      result[top--] = '\0';
      int operand2 = result[top];
      result[top--] = '\0';
      int tmp = 0;
      if (ch == '+')
        tmp = operand2 + operand1;
      else if (ch == '-')
        tmp = operand2 - operand1;
      else if (ch == '*')
        tmp = operand2 * operand1;
      else if (ch == '/')
        tmp = operand2 / operand1;
      else {
        exit(1);
      }
      result[++top] = tmp;
    }
    i++;
    ch = postfix[i];

  } while (ch != '\0');
  return result[0];
}
