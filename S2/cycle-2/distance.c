// Read two input each representing the distances between two points in the
// Euclidean space,

#include <math.h>
#include <stdio.h>

int main() {
  int x1, y1, x2, y2;
  printf("Enter the two points: ");
  scanf("(%d,%d) (%d,%d)", &x1, &y1, &x2, &y2);
  printf("Distance between the two points is: %lf",
         sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
  return 0;
}
