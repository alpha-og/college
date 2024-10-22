#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure representation for node
typedef struct Node {
  int operand;
  char operator;
  int is_operand;
  struct Node *left;
  struct Node *right;
} Node;

// function declarations
Node *create_node(int data);
int insert(Node **tree, Node *node, int mode);
void display_tree(Node *tree);

int main() { Node *tree = NULL; }

// function definitions

// function to insert a node into the tree
int insert(Node **tree, Node *node, int mode) {
  if (*tree == NULL) {
    *tree = node;
    return 1;
  } else {
    if (mode == 1) {
      insert(&((*tree)->right), node, mode);
    }
  }
  return 0;
}

int get_precedence(char operand) {
  if (operand == '+' || operand == '-')
    return 0;
  else if (operand == '*' || operand == '/')
    return 1;
  else if (operand == '^')
    return 2;
  else
    return -1;
}

Node *read_expression() {
  Node *infix_exp = NULL;
  char ch = '\0';

  while ((ch = getchar()) != '\n') {
    if (infix_exp == NULL) {
      infix_exp = create_node(ch);
    } else {
      insert(&infix_exp, create_node(ch), 0);
    }
  }
  return infix_exp;
}
