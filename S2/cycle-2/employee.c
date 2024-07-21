
// Using structure, read and print data of n employees (Name, Employee Id and
// Salary)

#include <stdio.h>
struct employee {
  char name[1000];
  int employeeId;
  float salary;
};

int main() {
  int n = 0;

  printf("Enter number of employees: ");
  scanf("%d", &n);
  getchar();
  struct employee employees[n];

  for (int i = 0; i < n; i++) {
    printf("Enter employee name: ");
    scanf("%[^\n]%*c", employees[i].name);

    printf("Enter employee id: ");
    scanf("%d", &employees[i].employeeId);

    printf("Enter employee salary: ");
    scanf("%f", &employees[i].salary);
    getchar();
  }
  for (int i = 0; i < n; i++) {
    printf("%d %s %f\n", employees[i].employeeId, employees[i].name,
           employees[i].salary);
  }
  return 0;
}
