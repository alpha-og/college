#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct Stack {
  int top;
  char array[MAX_SIZE];
} Stack;

typedef struct Node {
  char data;
  struct Node *left;
  struct Node *right;
} Node;

Stack *create_stack();
Node *create_node(char);
void push(Stack *, char);
char pop(Stack *);
char peek(Stack *);
int get_precedence(char);
int evaluate(Node *);
Node *construct_tree(char *);
void inorder(Node *);
void preorder(Node *);
void postorder(Node *);

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
  Node *tree = construct_tree(postfix->array);
  printf("Infix expression: ");
  inorder(tree);
  printf("\n");
  printf("Postfix expression: ");
  postorder(tree);
  printf("\n");
  printf("Prefix expression: ");
  preorder(tree);
  printf("\n");
  printf("Result: %d\n", evaluate(tree));
}

Stack *create_stack() {
  Stack *stack = calloc(1, sizeof(Stack));
  stack->top = -1;
  return stack;
}

Node *create_node(char data) {
  Node *node = calloc(1, sizeof(Node));
  node->data = data;
  return node;
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

Node *construct_tree(char *postfix) {
  Node **tree_stack = calloc(strlen(postfix), sizeof(Node *));
  int top = -1;
  int i = 0;
  char ch = postfix[i];
  do {
    Node *node = create_node(ch);
    if (isdigit(ch)) {
      tree_stack[++top] = node;
    } else {
      Node *right = tree_stack[top];
      tree_stack[top--] = NULL;
      Node *left = tree_stack[top];
      tree_stack[top--] = NULL;
      node->left = left;
      node->right = right;
      tree_stack[++top] = node;
    }
    i++;
    ch = postfix[i];
  } while (ch != '\0');
  return *tree_stack;
}

void inorder(Node *root) {
  if (root == NULL)
    return;
  if (!isdigit(root->data))
    printf("(");
  inorder(root->left);
  printf("%c", root->data);
  inorder(root->right);
  if (!isdigit(root->data))
    printf(")");
}
void preorder(Node *root) {
  if (root == NULL)
    return;
  printf("%c ", root->data);
  preorder(root->left);
  preorder(root->right);
}
void postorder(Node *root) {
  if (root == NULL)
    return;
  postorder(root->left);
  postorder(root->right);
  printf("%c ", root->data);
}

int evaluate(Node *root) {
  if (isdigit(root->data))
    return root->data - '0';
  else {
    char operator= root->data;
    int left = evaluate(root->left);
    int right = evaluate(root->right);
    if (operator== '+')
      return left + right;
    else if (operator== '-')
      return left - right;
    else if (operator== '*')
      return left * right;
    else if (operator== '/')
      return left / right;
    else {
      exit(1);
    }
  }
}
