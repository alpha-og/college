/*
  Experiment 11
  Matrix Operations - addition and multiplication
  25 Athul Anoop
  23-09-24
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
  MatrixElement *head;
} Matrix;

// function declarations

MatrixElement *createMatrixElement(Position position, int value);
Matrix *createMatrix(Size size);
void appendMatrixElement(Matrix *matrix, MatrixElement *matrixElement);
void readMatrix(Matrix *matrix);
MatrixElement *getMatrixElementByPosition(Matrix *matrix, Position position);
void displayMatrix(Matrix *matrix);

// function definitions

MatrixElement *createMatrixElement(Position position, int value) {
  MatrixElement *matrixElement = calloc(1, sizeof(MatrixElement));
  matrixElement->position = position;
  matrixElement->value = value;
  matrixElement->next = NULL;
  return matrixElement;
}

Matrix *createMatrix(Size size) {
  Matrix *matrix = calloc(1, sizeof(Matrix));
  matrix->size = size;
  *(matrix->head) = (MatrixElement){
      .value = -1, .position = {.column = -1, .row = -1}, .next = NULL};
  return matrix;
}

void appendMatrixElement(Matrix *matrix, MatrixElement *matrixElement) {
  MatrixElement *tail = matrix->head;
  while (tail->next != NULL) {
    tail = tail->next;
  }
  tail->next = matrixElement;
}

void readMatrix(Matrix *matrix) {
  printf("Provide the matrix elements row by row (x1, x2, ...)\n");
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      int element = 0;
      scanf("%d,", &element);
      if (element != 0) {
        Position position = {.row = row, .column = column};
        MatrixElement *matrixElement = createMatrixElement(position, element);
        appendMatrixElement(matrix, matrixElement);
      }
    }
  }
}

MatrixElement *getMatrixElementByPosition(Matrix *matrix, Position position) {
  MatrixElement *matrixElement = matrix->head;
  while (matrixElement->position.row != position.row ||
         matrixElement->position.column != position.column) {
    matrixElement = matrixElement->next;
  }
  return matrixElement;
}

void displayMatrix(Matrix *matrix) {
  printf("Matrix:\n");
  for (int row = 0; row < matrix->size.rows; row++) {
    for (int column = 0; column < matrix->size.columns; column++) {
      MatrixElement *matrixElement = getMatrixElementByPosition(
          matrix, (Position){.row = row, .column = column});
      if (matrixElement->position.column == column &&
          matrixElement->position.row == row) {
        printf("%d ", matrixElement->value);
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
  printf("\n");
}
