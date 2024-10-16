#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// function declarations

int read_members(char **root, int root_index, int *N);
void insert_node(char **root, int root_index, char *data, int child_index);
void display_tree(char **root, int root_index, int N);

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
  display_tree(tree, 0, node_count);
}

// function definitions

int read_members(char **root, int root_index, int *N) {
  if (*N == 0)
    return 0;
  if (root[0] == NULL) {
    fprintf(stdout, "Root member: ");
    char *data = calloc(100, sizeof(char));
    scanf("%s", data);
    if (data[0] == '-') {
      fprintf(stderr, "Root member cannot be empty\n");
      return 0;
    }
    insert_node(root, 0, data, 0);
    *N = *N - 1;
    root_index += 1;
    if (*N == 0)
      return 0;
  }
  int i = 1;
  int level = 1;
  int left = 1;
  int non_null = 1;
  int empty = 0;
  while (non_null <= *N) {
    root_index = (i + empty - left) / 2;
    printf("i=%d | level=%d | left=%d | root_index=%d\n", i, level, left,
           root_index);
    if (root[root_index] == NULL) {
      left = left == 1 ? 2 : 1;
      i++;
      continue;
    }

    fprintf(stdout, "Child of %s: ", root[root_index]);
    char *data = calloc(100, sizeof(char));
    scanf("%s", data);
    if (data[0] == '-') {
      left = left == 1 ? 2 : 1;
      empty++;
      i++;
      continue;
    }
    insert_node(root, root_index, data, left);
    left = left == 1 ? 2 : 1;
    non_null++;
    if (pow(2, level) == i) {
      level++;
    }
    i++;
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

void display_tree(char **root, int root_index, int N) {
  if (N == 0 || root[0] == NULL)
    return;
  int index = 0;
  int level = 0;
  while (index < N) {
    int level_nodes = pow(2, level);
    for (int i = index; i < index + level_nodes && i < N; i++) {
      if (root[i] == NULL) {
        fprintf(stdout, "-, ");
      } else {
        fprintf(stdout, "%s, ", root[i]);
      }
    }
    fprintf(stdout, "\n");
    index += level_nodes;
    level++;
  }
}
