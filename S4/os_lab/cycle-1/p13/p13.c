/* Athul Anoop
 * Roll no: 25
 * Description: C program to simulate banker's algorithm on a process mix
 */

#include <stdio.h>
#include <stdlib.h>

void print_matrix(int rows, int columns, int *matrix, const char *desc);
int *read_matrix(int rows, int columns, const char *prompt);
int *compute_need(int rows, int columns, int *allocated, int *max);
int is_process_safe(int nr, int *need, int *work);
int find_safe_process(int np, int nr, int *need, int *available,
                      int *completed);

int main() {
  // read number of processes (rows)
  int np;
  printf("\nNumber of processes\n>> ");
  scanf("%d", &np);
  getchar();

  // read number of distinct resource types (columns)
  int nr;
  printf("\nNumber of distinct resource types\n>> ");
  scanf("%d", &nr);
  getchar();

  // initialize available vector
  int *available = calloc(nr, sizeof(int));
  int *work = calloc(nr, sizeof(int));
  // read available vector
  printf("\nProvide the available resources:\n>> ");
  for (int i = 0; i < nr; i++) {
    scanf(" %d", (available + i));
    work[i] = available[i];
  }

  print_matrix(1, nr, available, "Available resources");

  // initialize the completed vector
  int *completed = calloc(np, sizeof(int));

  // initialize the safe sequence vector
  int *safe_sequence = calloc(np, sizeof(int));
  int safe_sequence_index = 0;

  // read max and allocated matrices
  int *max = read_matrix(np, nr, "Provide the max matrix");
  print_matrix(np, nr, max, "Max");
  int *allocated = read_matrix(np, nr, "Provide the allocation matrix");
  print_matrix(np, nr, allocated, "Allocated");

  // compute the need matrix
  int *need = compute_need(np, nr, allocated, max);
  print_matrix(np, nr, need, "Need");

  while (1) {
    int safe_process = find_safe_process(np, nr, need, work, completed);
    if (safe_process == -1) {
      int completed_all = 1;
      for (int i = 0; i < np; i++) {
        if (completed[i] == 0) {
          completed_all = 0;
          break;
        }
      }
      if (completed_all) {

        printf("\nSystem is in a safe state and the following is the safe "
               "sequence: ");
        for (int i = 0; i < np; i++) {
          printf("P%d, ", *(safe_sequence + i));
        }
        printf("\n");
      } else
        printf("\nSystem is in an unsafe state\n");
      break;
    } else {
      completed[safe_process] = 1;
      safe_sequence[safe_sequence_index++] = safe_process;
      for (int i = 0; i < nr; i++) {
        work[i] += *(allocated + safe_process * nr + i);
      }
    }
  }

  return 0;
}

void print_matrix(int rows, int columns, int *matrix, const char *desc) {
  printf("\n%s: ", desc);
  for (int i = 0; i < rows; i++) {
    printf("\n\t");
    for (int j = 0; j < columns; j++) {
      printf("%d ", *(matrix + i * columns + j));
    }
  }
  printf("\n");

  return;
}

int *read_matrix(int rows, int columns, const char *prompt) {
  int *matrix =
      calloc(rows * columns,
             sizeof(int)); // allocate and initialize matrix with null elements
  printf("\n%s", prompt);
  for (int i = 0; i < rows; i++) {
    printf("\n>> (process %d) ", i);
    for (int j = 0; j < columns; j++) {
      scanf(" %d", (matrix + i * columns + j)); // read each element
    }
  }
  return matrix;
}

int *compute_need(int rows, int columns, int *allocated, int *max) {
  int *need = calloc(
      rows * columns,
      sizeof(int)); // allocate and initialize need matrix with null elements
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      *(need + i * columns + j) =
          *(max + i * columns + j) -
          *(allocated + i * columns +
            j); // compute the difference of corresponding
                // elements and store into need matrix
    }
  }
  return need;
}

int is_process_safe(int nr, int *process_need, int *work) {
  for (int i = 0; i < nr; i++) {
    if (*(work + i) < *(process_need + i)) {
      return 0;
    }
  }
  return 1;
}

int find_safe_process(int np, int nr, int *need, int *work, int *completed) {
  print_matrix(1, nr, work, "Work");
  int process = -1;
  for (int i = 0; i < np; i++) {
    if (*(completed + i) == 0 && is_process_safe(nr, need + i * nr, work)) {
      process = i;
      break;
    }
  }
  return process;
}
