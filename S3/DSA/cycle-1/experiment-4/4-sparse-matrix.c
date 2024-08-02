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

void display_matrix_elements(MatrixElement *current_element) {
  printf("(%d,(%d,%d)),", current_element->value, current_element->position.row,
         current_element->position.column);
  if (current_element->next == NULL)
    return;
  else
    return display_matrix_elements(current_element->next);
}

void display_matrix_in_tuple_form(Matrix *matrix) {
  printf("\n[");
  display_matrix_elements(matrix->elements);
  printf("]\n");
}

void transpose_matrix_elements(MatrixElement *current_element) {
  Position new_position = {.row = current_element->position.column,
                           .column = current_element->position.row};
  current_element->position = new_position;
  if (current_element->next == NULL)
    return;
  return transpose_matrix_elements(current_element->next);
}

void transpose_matrix(Matrix *matrix) {
  transpose_matrix_elements(matrix->elements);
  Size size = {.rows = matrix->size.rows, .columns = matrix->size.columns};
  matrix->size = size;
}

MatrixElement *search_matrix_elements(MatrixElement *current_element,
                                      Position query) {
  if (current_element->position.row == query.row &&
      current_element->position.column == query.column)
    return current_element;
  if (current_element->next == NULL)
    return current_element;
  else
    return search_matrix_elements(current_element->next, query);
}

void traverse_and_add_elements(Matrix *result, MatrixElement *result_element,
                               MatrixElement *matrixB_element) {
  MatrixElement *element =
      search_matrix_elements(result_element, matrixB_element->position);
  if (element->position.row == matrixB_element->position.row &&
      element->position.column == matrixB_element->position.column) {
    element->value += matrixB_element->value;
  } else {
    create_matrix_element(result, matrixB_element->position,
                          matrixB_element->value);
  }
  if (matrixB_element->next == NULL)
    return;
  return traverse_and_add_elements(result, result_element,
                                   matrixB_element->next);
}

Matrix add_matrix(Matrix *matrixA, Matrix *matrixB) {
  if (matrixA->size.rows != matrixB->size.rows ||
      matrixA->size.columns != matrixB->size.columns) {
    fprintf(stderr, "Incompatible dimensions! Exiting...");
    exit(1);
  }
  Matrix result = *matrixA;
  traverse_and_add_elements(&result, result.elements, matrixB->elements);

  return result;
}

int main() {
  Matrix *matrixA = create_matrix(read_size());
  read_elements(matrixA);
  display_matrix_in_tuple_form(matrixA);
  // transpose_matrix(matrix);
  // display_matrix_in_tuple_form(matrix);
  Matrix *matrixB = create_matrix(read_size());
  read_elements(matrixB);
  display_matrix_in_tuple_form(matrixB);

  Matrix result = add_matrix(matrixA, matrixB);
  display_matrix_in_tuple_form(&result);
  return 0;
}
