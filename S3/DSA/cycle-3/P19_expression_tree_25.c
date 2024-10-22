#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// structure for tree node
typedef struct Node {
  char data;
  struct Node *left;
  struct Node *right;
} Node;

// structure for stack
typedef struct Stack {
  int top;
  Node *array[MAX_SIZE];
} Stack;

Stack *create_stack();
void push(Stack *stack, Node *node);
Node *pop(Stack *stack);
int is_operator(char c);
int precedence(char c);
Node *new_node(char data);
void infix_to_postfix(char *infix, char *postfix);
Node *construct_tree(char *postfix);
void inorder_traversal(Node *root);
void preorder_traversal(Node *root);
void postorder_traversal(Node *root);
int evaluate(Node *root);

int main() {
  char infix[MAX_SIZE], postfix[MAX_SIZE];

  printf("Enter infix expression: ");
  scanf("%s", infix);

  // convert infix to postfix
  infix_to_postfix(infix, postfix);
  printf("\nPostfix expression: %s\n", postfix);

  // construct expression tree
  Node *root = construct_tree(postfix);

  // display expressions in different forms
  printf("\nInfix expression: ");
  inorder_traversal(root);
  printf("\nPrefix expression: ");
  preorder_traversal(root);
  printf("\nPostfix expression: ");
  postorder_traversal(root);

  // evaluate expression
  printf("\nEvaluation result: %d\n", evaluate(root));

  return 0;
}

// function to create stack
Stack *create_stack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;
  return stack;
}

// function to push node to stack
void push(Stack *stack, Node *node) { stack->array[++stack->top] = node; }

// function to pop node from stack
Node *pop(Stack *stack) {
  if (stack->top == -1)
    return NULL;
  return stack->array[stack->top--];
}

// function to check if character is operator
int is_operator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

// function to get precedence of operator
int precedence(char c) {
  if (c == '*' || c == '/')
    return 2;
  if (c == '+' || c == '-')
    return 1;
  return 0;
}

// function to create a new node
Node *new_node(char data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

// function to convert infix to postfix
void infix_to_postfix(char *infix, char *postfix) {
  Stack *stack = create_stack();
  int i, j = 0;
  char token;

  for (i = 0; infix[i] != '\0'; i++) {
    token = infix[i];

    // check if the character is a digit
    if (token >= '0' && token <= '9') {
      postfix[j++] = token;
    } else if (token == '(') {
      push(stack, new_node(token));
    } else if (token == ')') {
      while (stack->top != -1 && stack->array[stack->top]->data != '(') {
        postfix[j++] = pop(stack)->data;
      }
      if (stack->top != -1) {
        pop(stack); // remove '('
      }
    } else if (is_operator(token)) {
      while (stack->top != -1 && stack->array[stack->top]->data != '(' &&
             precedence(stack->array[stack->top]->data) >= precedence(token)) {
        postfix[j++] = pop(stack)->data;
      }
      push(stack, new_node(token));
    }
  }

  while (stack->top != -1) {
    if (stack->array[stack->top]->data != '(') {
      postfix[j++] = pop(stack)->data;
    } else {
      pop(stack);
    }
  }

  postfix[j] = '\0';
  free(stack);
}

// function to construct expression tree from postfix
Node *construct_tree(char *postfix) {
  Stack *stack = create_stack();
  Node *t, *t1, *t2;

  for (int i = 0; postfix[i] != '\0'; i++) {
    if (!is_operator(postfix[i])) {
      t = new_node(postfix[i]);
      push(stack, t);
    } else {
      t = new_node(postfix[i]);
      t1 = pop(stack);
      t2 = pop(stack);
      t->right = t1;
      t->left = t2;
      push(stack, t);
    }
  }
  t = pop(stack);
  free(stack);
  return t;
}

// tree traversal functions
void inorder_traversal(Node *root) {
  if (root) {
    if (is_operator(root->data))
      printf("(");
    inorder_traversal(root->left);
    printf("%c", root->data);
    inorder_traversal(root->right);
    if (is_operator(root->data))
      printf(")");
  }
}

void preorder_traversal(Node *root) {
  if (root) {
    printf("%c", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
  }
}

void postorder_traversal(Node *root) {
  if (root) {
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%c", root->data);
  }
}

// function to evaluate expression tree
int evaluate(Node *root) {
  if (!root)
    return 0;

  // if the node is a digit, return its integer value
  if (!is_operator(root->data)) {
    return root->data - '0';
  }

  int left_val = evaluate(root->left);
  int right_val = evaluate(root->right);

  switch (root->data) {
  case '+':
    return left_val + right_val;
  case '-':
    return left_val - right_val;
  case '*':
    return left_val * right_val;
  case '/':
    return left_val / right_val;
  }
  return 0;
}
