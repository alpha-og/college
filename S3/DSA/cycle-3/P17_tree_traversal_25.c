/*
  Experiment 17
  Tree traversal
  25 Athul Anoop
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// structure representation for node
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// function declarations

void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);
void levelorder(Node *root);
void display_menu();
void handle_choice(Node **root);
Node *create_tree();
Node *create_node(int data);
Node *insert_node(Node **root, Node *node);

int main() {
  Node *root = NULL;

  display_menu();

  while (1) {
    handle_choice(&root);
  }
}

void preorder(Node *root) {
  if (root == NULL)
    return;
  else {
    fprintf(stdout, "%d, ", root->data);
    preorder(root->left);
    preorder(root->right);
  }
}

void inorder(Node *root) {
  if (root == NULL)
    return;
  else {
    inorder(root->left);
    fprintf(stdout, "%d, ", root->data);
    inorder(root->right);
  }
}

void postorder(Node *root) {
  if (root == NULL)
    return;
  else {
    postorder(root->left);
    postorder(root->right);
    fprintf(stdout, "%d, ", root->data);
  }
}

void levelorder(Node *root) {
  if (root == NULL)
    return;
  else {
    Node **queue = calloc(100, sizeof(Node));
    int front = 0;
    int rear = 0;
    queue[rear++] = root;
    int level = 0;
    while (rear > front) {
      Node *tmp = queue[front++];
      if (tmp->left != NULL) {
        queue[rear++] = tmp->left;
      }
      if (tmp->right != NULL) {
        queue[rear++] = tmp->right;
      }
      if (front == (int)pow(2, level)) {
        level += 1;
        fprintf(stdout, "\n");
      }
      fprintf(stdout, "%d, ", tmp->data);
    }
    free(queue);
  }
}

Node *create_node(int data) {
  Node *node = calloc(1, sizeof(Node));
  node->data = data;
  return node;
}

Node *insert_node(Node **root, Node *node) {
  if (*root == NULL)
    return node;
  else {
    Node **queue = calloc(100, sizeof(Node));
    int front = 0;
    int rear = 0;
    queue[rear++] = *root;
    while (rear > front) {
      Node *tmp = queue[front++];
      if (tmp->left != NULL) {
        queue[rear++] = tmp->left;
      } else {
        tmp->left = node;
        break;
      }

      if (tmp->right != NULL) {
        queue[rear++] = tmp->right;
      } else {
        tmp->right = node;
        break;
      }
    }
    free(queue);
  }
  return node;
}

void display_menu() {
  fprintf(stdout, "\n---- Menu ---- \n");
  fprintf(stdout, "1. Insert Node\n");
  fprintf(stdout, "2. Display preorder\n");
  fprintf(stdout, "3. Display inorder\n");
  fprintf(stdout, "4. Display postorder\n");
  fprintf(stdout, "5. Display levelorder\n");
  fprintf(stdout, "6. Display menu\n");
  fprintf(stdout, "7. Exit\n");
}

void handle_choice(Node **root) {
  int choice = -1;
  fprintf(stdout, "\nChoice: ");
  fscanf(stdin, "%d", &choice);
  switch (choice) {
  case 1:
    fprintf(stdout, "Enter a value: ");
    int value = -1;
    fscanf(stdin, "%d", &value);
    if (*root == NULL)
      *root = insert_node(root, create_node(value));
    else
      insert_node(root, create_node(value));
    break;
  case 2:
    preorder(*root);
    break;
  case 3:
    inorder(*root);
    break;
  case 4:
    postorder(*root);
    break;
  case 5:
    levelorder(*root);
    break;
  case 6:
    display_menu();
    break;
  case 7:
    fprintf(stdout, "Exiting...\n");
    exit(0);
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
  }
}
