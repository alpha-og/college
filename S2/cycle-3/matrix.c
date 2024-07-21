#include <stdio.h>
#include <stdlib.h>

struct matrix readMatrix();
struct matrix {
  int ndims;
  int shape;
  int *matrix;
};

int main() {
  printf("Operations\n");
  printf("1. Input a matrix\n");
  printf("2. Add matrices\n");
  printf("3. Multiply matrices\n");
  printf("4. Transpose of matrix\n");
  int choice = 0;

  printf("Choose an option (1-4): ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("Matrix:\n");
    for (int i = 0; i < elementCount; i++) {
      printf("%d,", *(matrix + i));
    }
    printf("\n");
  }
  return 0;
}

struct matrix readMatrix(int *ndims, int *shape, int *matrix) {
  printf("Enter the number of dimensions: ");
  scanf("%d", ndims);

  shape = (int *)malloc(sizeof(int) * *ndims);
  int elementCount = 1;

  printf("Enter the dimensions:");
  for (int i = 0; i < *ndims; i++) {
    scanf("%d", shape + i);
    elementCount *= *(shape + i);
    getchar();
  }

  matrix = (int *)malloc(sizeof(int) * elementCount);
  printf("Enter the matrix: ");
  char num[10] = {'\0'};
  int numIndex = 0;
  char ch = '\0';
  int currentElement = 0;
  while (1) {
    scanf("%c", &ch);
    if (ch == '\n') {
      break;
    }
    if (ch != '[' && ch != ',' && ch != ']') {
      *(num + numIndex) = ch;
      numIndex++;
    } else if (*(num + numIndex - 1) != '\0' && (ch == ',' || ch == ']')) {
      int element = atoi(num);
      *(matrix + currentElement) = element;

      numIndex = 0;
      for (int k = 0; k < 10; k++) {
        *(num + k) = '\0';
      }
      currentElement++;
    }
  }
  struct matrix mat;
  mat.ndims = ndims;
  mat.shape = shape

      return
}
