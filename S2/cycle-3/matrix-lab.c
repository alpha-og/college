#include <stdio.h>
#include <stdlib.h>

void displayMatrix(int *matrix, int row, int col) {
  printf("Matrix:\n");
  printf("[");
  for (int i = 0; i < row; i++) {
    printf("[");
    for (int j = 0; j < col; j++) {
      printf("%d,", *(matrix + i * col + j));
    }
    printf("],");
  }
  printf("]\n");
}

void readMatrix(int *matrix, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("Enter the element (%d,%d): ", i, j);
      scanf("%d", (matrix + i * col + j));
    }
  }

  displayMatrix(matrix, row, col);
}

void add(int *matrixA, int *matrixB, int rowA, int colA, int rowB, int colB) {
  if (!(rowA == rowB && colA == colB)) {
    printf("Incompatible dimensions\n");
    exit(1);
  }
  int row = rowA, col = colA;
  int *result = (int *)malloc(sizeof(int) * row * col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      *(result + i * col + j) =
          *(matrixA + i * col + j) + *(matrixB + i * col + j);
    }
  }
  displayMatrix(result, row, col);
  free(result);
}

void multiply(int *matrixA, int *matrixB, int rowA, int colA, int rowB,
              int colB) {
  if (colA != rowB) {
    printf("Incompatible dimensions\n");
    exit(1);
  }
  int row = rowA, col = colB;
  int *result = (int *)malloc(sizeof(int) * row * col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      *(result + i * col + j) = 0;
      for (int k = 0; k < colA; k++) {
        *(result + i * col + j) +=
            *(matrixA + i * colA + k) * *(matrixB + k * colB + j);
      }
    }
  }
  displayMatrix(result, row, col);
  free(result);
}

void transpose(int *matrix, int row, int col) {
  int *result = (int *)malloc(sizeof(int) * row * col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      *(result + j * row + i) = *(matrix + i * col + j);
    }
  }
  displayMatrix(result, row, col);
  free(result);
}

int main() {
  int ch = 0, rowA = 0, colA = 0, rowB = 0, colB = 0;

  printf("Enter the dimensions of matrix A: ");
  scanf("%d,%d", &rowA, &colA);
  int *matrixA = (int *)malloc(sizeof(int) * rowA * colA);
  printf("Enter the first matrix: \n");
  readMatrix(matrixA, rowA, colA);

  printf("Enter the dimensions of matrix B: ");
  scanf("%d,%d", &rowB, &colB);
  int *matrixB = (int *)malloc(sizeof(int) * rowB * colB);
  printf("Enter the second matrix: \n");
  readMatrix(matrixB, rowB, colB);

  printf("Options:\n");
  printf("1. Add the matrices\n");
  printf("2. Multiply the matrices\n");
  printf("3. Transpose the matrix\n");
  printf("Choose an option (1-3): ");
  scanf("%d", &ch);
  switch (ch) {
  case 1:
    add(matrixA, matrixB, rowA, colA, rowB, colB);
    break;
  case 2:
    multiply(matrixA, matrixB, rowA, colA, rowA, colB);
    break;
  case 3:
    transpose(matrixA, rowA, colA);
    break;
  default:
    printf("Invalid option\n");
  }

  return 0;
}
