/*
 * Experiment - 04
 *Write a C program to input two sparse matrices in normal form.
 *With the help of a menu do the following operations, each implemented as
 *separate functions: Convert matrix to tuple form. Display the matrix in tuple
 *form. Find the transpose of a matrix represented in tuple form. Find the sum
 *of the two matrices in tuple form.
 *Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int columns;
  int rows;
} Size;

typedef struct {
  int column;
  int row;
} Position;

typedef struct {
  Position position;
  int value;
} TupleElement;

typedef struct Matrix {
  Size size;
  int non_zero_element_count;
  int *normal_form_elements;
  TupleElement *tuple_form_elements;
} Matrix;

void create_matrix(Matrix *matrix);
void convert_matrix_to_tuple_form(Matrix *matrix);
void display_matrix_in_normal_form(Matrix *matrix);
void display_matrix_in_tuple_form(Matrix *matrix);
void transpose_matrix(Matrix *matrix);
Matrix *add_matrices(Matrix *matrices);
void display_menu();
void handle_choice(Matrix *matrices);

int main() {
  Matrix *matrices = (Matrix *)calloc(3, sizeof(Matrix));
  while (1) {
    display_menu();
    handle_choice(matrices);
  }
  return 0;
}

void create_matrix(Matrix *matrix) {
  if (matrix->normal_form_elements != NULL) {
    free(matrix->normal_form_elements);
    matrix->normal_form_elements = NULL;
    free(matrix->tuple_form_elements);
    matrix->tuple_form_elements = NULL;
    matrix->non_zero_element_count = 0;
    matrix->size = (Size){.rows = 0, .columns = 0};
  }
  printf("\n---- Matrix ----\n");
  printf("Matrix size (NxM): ");
  scanf("%dx%d", &(matrix->size.rows), &(matrix->size.columns));

  matrix->normal_form_elements =
      (int *)calloc(matrix->size.rows * matrix->size.columns, sizeof(int));
  ;
  printf("Provide the matrix elements row by row (x1,x2,...)\n");
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      int value = 0;
      scanf("%d,", &value);
      if (value != 0) {
        matrix->non_zero_element_count++;
      }
      matrix->normal_form_elements[matrix->size.columns * row + column] = value;
    }
  }
}

void display_matrix_in_normal_form(Matrix *matrix) {
  if (matrix->normal_form_elements == NULL) {
    fprintf(stderr, "\nCreate the matrix first\n");
    return;
  }
  printf("\nMatrix in normal form:\n");
  printf("[");
  for (int row = 0; row < matrix->size.rows; row++) {
    printf("[");
    for (int column = 0; column < matrix->size.columns; column++) {
      printf("%d",
             matrix->normal_form_elements[matrix->size.columns * row + column]);
      if (column != matrix->size.columns - 1) {
        printf(", ");
      }
    }
    printf("]");
    if (row != matrix->size.rows - 1) {
      printf(",\n");
    }
  }
  printf("]\n");
}
void display_matrix_in_tuple_form(Matrix *matrix) {
  convert_matrix_to_tuple_form(matrix);
  printf("\nMatrix in tuple form:\n");
  for (int index = 0; index < matrix->non_zero_element_count; index++) {
    TupleElement *current_element = &matrix->tuple_form_elements[index];
    int value = current_element->value;
    int row = current_element->position.row;
    int column = current_element->position.column;
    printf("(%d-(%d,%d))", value, row, column);
  }
  printf("\n");
}

void convert_matrix_to_tuple_form(Matrix *matrix) {
  if (matrix->normal_form_elements == NULL) {
    fprintf(stderr, "\nCreate the matrix first\n");
    return;
  }
  if (matrix->tuple_form_elements != NULL) {
    free(matrix->tuple_form_elements);
    matrix->tuple_form_elements = NULL;
  }

  matrix->tuple_form_elements = (TupleElement *)calloc(
      matrix->non_zero_element_count, sizeof(TupleElement));
  int current_index = 0;
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      int value =
          matrix->normal_form_elements[matrix->size.columns * row + column];
      if (value != 0) {
        if (current_index >= matrix->non_zero_element_count) {
          return;
        }
        matrix->tuple_form_elements[current_index].position =
            (Position){.row = row, .column = column};
        matrix->tuple_form_elements[current_index].value = value;
        current_index++;
      }
    }
  }
}
void transpose_matrix(Matrix *matrix) {
  if (matrix->normal_form_elements == NULL) {
    fprintf(stderr, "\nCreate the matrix first\n");
    return;
  }
  for (int index = 0; index < matrix->non_zero_element_count; index++) {
    matrix->tuple_form_elements[index].position =
        (Position){.row = matrix->tuple_form_elements[index].position.column,
                   .column = matrix->tuple_form_elements[index].position.row};
  }
  int *tmp =
      (int *)calloc(matrix->size.rows * matrix->size.columns, sizeof(int));
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      int old_index = matrix->size.columns * row + column;
      int new_index = matrix->size.rows * column + row;
      tmp[new_index] = matrix->normal_form_elements[old_index];
    }
  }
  matrix->normal_form_elements = tmp;
  matrix->size =
      (Size){.rows = matrix->size.columns, .columns = matrix->size.rows};
}
Matrix *add_matrices(Matrix *matrices) {
  if (matrices[0].size.rows != matrices[1].size.rows ||
      matrices[0].size.columns != matrices[1].size.columns) {
    fprintf(stderr, "Incompatible dimensions!\n");
    return NULL;
  }
  Matrix *result = (Matrix *)calloc(1, sizeof(Matrix));

  result->size = (Size){.rows = matrices[0].size.rows,
                        .columns = matrices[0].size.columns};
  int *result_elements =
      (int *)calloc(result->size.rows * result->size.columns, sizeof(int));
  result->normal_form_elements = result_elements;
  for (int row = 0; row < result->size.rows; row++) {
    for (int column = 0; column < result->size.columns; column++) {
      int index = result->size.columns * row + column;
      result_elements[index] = matrices[0].normal_form_elements[index] +
                               matrices[1].normal_form_elements[index];
    }
  }
  return result;
}

void display_menu() {
  printf("\n---- Menu ----\n");
  printf("1. Input matrix \n");
  printf("2. Display matrix in normal form \n");
  printf("3. Display matrix in tuple form \n");
  printf("4. Transpose matrix \n");
  printf("5. Add matrices \n");
  printf("6. Exit \n");
  printf("Enter your choice: ");
}

int read_matrix_choice() {
  printf("Enter the matrix index (0-1): ");
  int index;
  scanf("%d", &index);
  if (index != 0 && index != 1) {
    fprintf(stderr, "Invalid matrix index\n");
    return -1;
  }
  return index;
}

void handle_choice(Matrix *matrices) {
  int choice;
  int index = -1;
  Matrix *result = NULL;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    index = read_matrix_choice();
    if (index == -1) {
      return;
    }
    create_matrix(&matrices[index]);
    break;
  case 2:
    index = read_matrix_choice();
    if (index == -1) {
      break;
    }
    display_matrix_in_normal_form(&matrices[index]);
    break;
  case 3:
    index = read_matrix_choice();
    if (index == -1) {
      break;
    }
    display_matrix_in_tuple_form(&matrices[index]);
    break;
  case 4:
    index = read_matrix_choice();
    if (index == -1) {
      return;
    }
    transpose_matrix(&matrices[index]);
    break;
  case 5:
    result = add_matrices(matrices);
    if (result == NULL) {
      return;
    }
    matrices[2] = *result;
    display_matrix_in_normal_form(&matrices[2]);
    break;
  case 6:
    exit(0);
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
    break;
  }
}
