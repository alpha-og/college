/*
 * Experiment - 04
 * Program to store sparse matrices in tuple form and perform operations on them
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Size {
  int columns;
  int rows;
} Size;

typedef struct Position {
  int column;
  int row;
} Position;

typedef struct MatrixElement {
  Position position;
  int value;
  struct MatrixElement *next;
} MatrixElement;

typedef struct Matrix {
  Size size;
  MatrixElement *elements;
} Matrix;

MatrixElement *get_tail(MatrixElement *current_element) {
  if (current_element->next == NULL) {
    return current_element;
  } else {
    return get_tail(current_element->next);
  }
}

void create_matrix_element(Matrix *matrix, Position position, int value) {
  MatrixElement *matrix_element =
      (MatrixElement *)malloc(sizeof(MatrixElement));
  matrix_element->next = NULL;
  matrix_element->position = position;
  matrix_element->value = value;
  if (matrix->elements == NULL) {
    matrix->elements = matrix_element;
  } else {
    MatrixElement *tail = get_tail(matrix->elements);
    tail->next = matrix_element;
  }
}

Size read_size() {
  Size size = {.columns = 0, .rows = 0};
  printf("Matrix size (NxM): ");
  scanf("%dx%d", &(size.rows), &(size.columns));
  return size;
}

void read_elements(Matrix *matrix) {
  printf("Provide the matrix elements row by row (x1, x2, ...)\n");
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      int element = 0;
      scanf("%d,", &element);
      if (element != 0) {
        Position position = {.row = row, .column = column};
        create_matrix_element(matrix, position, element);
      }
    }
  }
}

Matrix *create_matrix(Size size) {
  Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
  matrix->size = size;
  matrix->elements = NULL;
  return matrix;
}

void display_matrix_elements(Matrix *matrix, Position *current_position,
                             MatrixElement *current_element) {
  int inserted = 0;
  for (int i = 0; i < matrix->size.rows; i++) {
    if (inserted == 1)
      break;
    for (int j = 0; j < matrix->size.columns; j++) {
      if (j == 0)
        printf("[");
      if (current_element->position.row == i &&
          current_element->position.column == j) {
        printf("%d, ", current_element->value);
        inserted = 1;
        current_position->row = i;
        current_position->column = j;

        break;
      }
      if (j == (matrix->size.columns - 1))
        printf("],\n");
    }
  }
  if (current_element->next == NULL)
    return;
  return display_matrix_elements(matrix, current_position,
                                 current_element->next);
}

void display_matrix(Matrix *matrix) {
  printf("[");
  Position current_position = {.row = 0, .column = 0};
  display_matrix_elements(matrix, &current_position, matrix->elements);
  printf("]");
}

int main() {
  Matrix *matrix = create_matrix(read_size());
  read_elements(matrix);
  display_matrix(matrix);
  return 0;
}
