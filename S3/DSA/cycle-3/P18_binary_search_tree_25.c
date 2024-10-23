/*
  Experiment 18
  Binary search tree
  25 Athul Anoop
*/

#include <stdio.h>
#include <stdlib.h>

// structure representation for node
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// function declarations

Node *create_node(int data);
int insert(Node **tree, Node *node);
int delete(Node **tree, int key);
int search(Node *tree, int key);
int read_data();
void display_tree(Node *tree);
void display_menu();
void handle_choice(Node **tree);

int main() {
  Node *tree = NULL;
  display_menu();

  // main loop
  while (1) {
    handle_choice(&tree);
  }
}

// function definitions

// function to create a new node
Node *create_node(int data) {
  Node *node = calloc(1, sizeof(Node));
  node->data = data;
  return node;
}

// function to insert a node into the tree
int insert(Node **tree, Node *node) {
  if (*tree == NULL) {
    *tree = node;
    return 1;
  } else {
    if (node->data < (*tree)->data) {
      if ((*tree)->left == NULL) {
        (*tree)->left = node;
        return 1;
      } else {
        return insert(&(*tree)->left, node);
      }
    } else if (node->data > (*tree)->data) {
      if ((*tree)->right == NULL) {
        (*tree)->right = node;
        return 1;
      } else {
        return insert(&(*tree)->right, node);
      }
    } else {
      return 0;
    }
  }
  return 1;
}

// function to search for a node in the tree
int search(Node *tree, int key) {
  if (tree == NULL) {
    return 0;
  } else {
    if (tree->data == key) {
      return 1;
    } else if (key < tree->data) {
      return search(tree->left, key);
    } else if (key > tree->data) {
      return search(tree->right, key);
    }
  }
  return 0;
}

Node *find_min(Node *node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

// function to delete a node from the tree
int delete(Node **tree, int key) {
  if (*tree == NULL) {
    return 0; // Node not found
  }

  if (key < (*tree)->data) {
    // Go left
    return delete (&(*tree)->left, key);
  } else if (key > (*tree)->data) {
    // Go right
    return delete (&(*tree)->right, key);
  } else {
    // Node to delete found
    if ((*tree)->left == NULL && (*tree)->right == NULL) {
      // Case 1: No children
      free(*tree);
      *tree = NULL;
    } else if ((*tree)->left == NULL) {
      // Case 2: Only right child
      Node *tmp = *tree;
      *tree = (*tree)->right;
      free(tmp);
    } else if ((*tree)->right == NULL) {
      // Case 3: Only left child
      Node *tmp = *tree;
      *tree = (*tree)->left;
      free(tmp);
    } else {
      // Case 4: Two children
      Node *tmp = find_min((*tree)->right); // Find the in-order successor
      (*tree)->data = tmp->data;            // Replace data
      delete (&(*tree)->right, tmp->data);  // Recursively delete successor
    }
    return 1; // Node deleted successfully
  }
  return 0; // Node not found
}
// function to display the tree
void display_tree(Node *tree) {
  if (tree == NULL) {
    return;
  }
  display_tree(tree->left);
  fprintf(stdout, "%d ", tree->data);
  display_tree(tree->right);
}

// function to display the menu
void display_menu() {
  fprintf(stdout, "\n---- MENU ----\n");
  fprintf(stdout, "1. Insert\n");
  fprintf(stdout, "2. Delete\n");
  fprintf(stdout, "3. Search\n");
  fprintf(stdout, "4. Display tree\n");
  fprintf(stdout, "5. Display menu\n");
  fprintf(stdout, "6. Exit\n");
}

// function to read data from the user
int read_data() {
  int data = 0;
  fprintf(stdout, "Enter a value: ");
  fscanf(stdin, "%d", &data);
  return data;
}

// function to handle the choice of the user
void handle_choice(Node **tree) {
  int choice;
  fprintf(stdout, "\nChoice: ");
  fscanf(stdin, "%d", &choice);
  getchar();
  int value = 0;
  int result = 0;
  switch (choice) {
  case 1:
    value = read_data();
    result = insert(tree, create_node(value));
    if (result) {
      fprintf(stdout, "Successfully inserted\n");
    } else {
      fprintf(stderr, "ERROR: Duplicate entry\n");
    }
    break;
  case 2:
    result = delete (tree, read_data());
    if (result) {
      fprintf(stdout, "Successfully deleted\n");
    } else {
      fprintf(stdout, "Entry not found\n");
    }
    break;
  case 3:
    result = search(*tree, read_data());
    if (result) {
      fprintf(stdout, "Key found\n");
    } else {
      fprintf(stdout, "Key not found\n");
    }
    break;
  case 4:
    display_tree(*tree);
    break;
  case 5:
    display_menu();
    break;
  case 6:
    fprintf(stdout, "Exiting...\n");
    exit(0);
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
    break;
  }
}
