/*
  Experiment 16
  Family tree
  25 Athul Anoop
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declarations

int read_members(char **root, int root_index, int *N);
void insert_node(char **root, int root_index, char *data, int child_index);
void display_tree(char **root, int root_index, int N);
void display_children(char **root, int root_index, int child_index);
void display_parent(char **root, int root_index, int child_index);
void display_grandparent(char **root, int root_index, int child_index);
void search(char **root, int root_index, int N,
            void cb(char **root, int root_index, int child_index));
void display_menu();
void handle_choice(char **root, int *node_count);

int main() {
  int N = 0;
  fprintf(stdout, "Number of members in the family: ");
  fscanf(stdin, "%d", &N);
  if (N <= 0) {
    fprintf(stderr, "Invalid input\n");
    exit(1);
  }
  char **tree = calloc(100, sizeof(char *));
  int tmp = N;
  int node_count = read_members(tree, 0, &tmp);
  display_menu();
  while (1) {
    handle_choice(tree, &node_count);
  }
}

// function definitions

int read_members(char **root, int root_index, int *N) {
  if (*N == 0)
    return 0;
  else if (root[root_index] == NULL) {
    fprintf(stdout, "Root member: ");
    char *data = calloc(100, sizeof(char));
    fscanf(stdin, "%s", data);
    insert_node(root, root_index, data, 0);
    *N = *N - 1;
    if (*N == 0) {
      return 1;
    }
  }
  int non_null_nodes = 0;
  int child_index = 1;
  int i = 2;
  for (; i < 1002; i++) {
    root_index = i / 2 - 1;
    if (root[root_index] == NULL) {
      child_index = child_index == 1 ? 2 : 1;
      continue;
    }
    char *sub_tree_root = root[root_index];
    char *data = malloc(100 * sizeof(char));
    fprintf(stdout, "Child of member %s: ", sub_tree_root);
    fscanf(stdin, "%s", data);
    if (data[0] != '-') {
      insert_node(root, root_index, data, child_index);
      non_null_nodes++;
      if (non_null_nodes == *N) {
        break;
      }
    }
    child_index = child_index == 1 ? 2 : 1;
  }

  return i;
}

void insert_node(char **root, int root_index, char *data, int child_index) {
  if (child_index == 0) {
    root[0] = data;
  } else {
    root[2 * root_index + child_index] = data;
  }
}

void search(char **root, int root_index, int N,
            void cb(char **root, int root_index, int child_index)) {
  char *data = calloc(100, sizeof(char));
  fprintf(stdout, "Query member: ");
  fscanf(stdin, "%s", data);
  if (root == NULL || root[root_index] == NULL) {
    fprintf(stderr, "ERROR: Tree is empty\n");
    return;
  } else if (strcmp(root[root_index], data) == 0) {
    return cb(root, root_index, 0);
  } else {
    int child_index = 1;
    for (int i = 2; i < N + 1; i++) {
      root_index = i / 2 - 1;
      if (root[root_index] == NULL) {
      } else {
        int current_index = 2 * root_index + child_index;
        char *current = root[current_index];
        if (current != NULL && strcmp(current, data) == 0)
          return cb(root, root_index, child_index);
      }
      child_index = child_index == 1 ? 2 : 1;
    }
  }
  fprintf(stderr, "ERROR: Queried member not found\n");
}

void display_tree(char **root, int root_index, int N) {
  fprintf(stdout, "\nGenerations:\n");
  if (N == 0 || root[0] == NULL)
    return;
  else {
    int child_index = 1;
    fprintf(stdout, "%s", root[0]);
    int level = 1;
    for (int i = 2; i < N + 1; i++) {
      root_index = i / 2 - 1;
      if (pow(2, level) == i) {
        fprintf(stdout, "\n");
        level++;
      }
      if (root[root_index] == NULL) {
      } else {
        fprintf(stdout, "%s,", root[2 * root_index + child_index]);
      }
      child_index = child_index == 1 ? 2 : 1;
    }
  }
  fprintf(stdout, "\n");
}

void display_children(char **root, int root_index, int child_index) {
  int child1_index = 2 * (2 * root_index + child_index) + 1;
  int child2_index = 2 * (2 * root_index + child_index) + 2;
  int has_children = 0;

  fprintf(stdout, "\nChildren of %s: ", root[2 * root_index + child_index]);
  if (root[child1_index] != NULL) {
    has_children = 1;
    fprintf(stdout, "%s, ", root[child1_index]);
  }

  if (root[child2_index] != NULL) {
    has_children = 1;
    fprintf(stdout, "%s\n", root[child2_index]);
  }
  if (has_children == 0)
    fprintf(stdout, "No children\n");
}

void display_parent(char **root, int root_index, int child_index) {
  fprintf(stdout, "\nParent of %s: ", root[2 * root_index + child_index]);
  if (root[root_index] == NULL)
    fprintf(stdout, "Parent not found\n");
  else
    fprintf(stdout, "%s\n", root[root_index]);
}

void display_grandparent(char **root, int root_index, int child_index) {
  fprintf(stdout, "Grandparent of %s: ", root[2 * root_index + child_index]);
  int grandparent_index = (root_index + 1) / 2 - 1;
  if (grandparent_index < 0 || root[grandparent_index] == NULL)
    fprintf(stdout, "Grandparent not found\n");
  else
    fprintf(stdout, "%s\n", root[grandparent_index]);
}

void display_menu() {
  fprintf(stdout, "\n---- MENU ----\n");
  fprintf(stdout, "1. Display tree\n");
  fprintf(stdout, "2. Display children\n");
  fprintf(stdout, "3. Display parent\n");
  fprintf(stdout, "4. Display grandparent\n");
  fprintf(stdout, "5. Display menu\n");
  fprintf(stdout, "6. Exit\n");
}

void handle_choice(char **root, int *node_count) {
  int choice;
  fprintf(stdout, "\nChoice: ");
  fscanf(stdin, "%d", &choice);
  getchar();
  switch (choice) {
  case 1:
    display_tree(root, 0, *node_count);
    break;
  case 2:
    search(root, 0, *node_count, display_children);
    break;
  case 3:
    search(root, 0, *node_count, display_parent);
    break;
  case 4:
    search(root, 0, *node_count, display_grandparent);
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
