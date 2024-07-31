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

void create_matrix_element(Matrix *matrix) {
  MatrixElement *matrix_element =
      (MatrixElement *)malloc(sizeof(MatrixElement));
  if (matrix->elements == NULL) {
    matrix->elements = matrix_element;
  } else {
    matrix_element->next = matrix->elements;
    matrix->elements = matrix_element;
  }
}

Size read_size() {
  Size size = {.columns = 0, .rows = 0};
  printf("Matrix size (NxM): ");
  scanf("%dx%d", &(size.rows), &(size.columns));
  return size;
}

Matrix *create_matrix(Size size) {
  Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
  matrix->size = size;
  matrix->elements = NULL;
  return matrix;
}

int main() { return 0; }
