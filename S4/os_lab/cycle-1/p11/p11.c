/*
 * Athul Anoop
 * Roll no: 25
 * Description: C program to display odd and even numbers in input using two
 * processes
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_odd_numbers(int arr[], int size) {
  printf("Odd numbers: ");
  for (int i = 0; i < size; ++i) {
    if (arr[i] % 2 != 0) {
      printf("%d ", arr[i]);
    }
  }
  printf("\n");
}

void print_even_numbers(int arr[], int size) {
  printf("Even numbers: ");
  for (int i = 0; i < size; ++i) {
    if (arr[i] % 2 == 0) {
      printf("%d ", arr[i]);
    }
  }
  printf("\n");
}

int main() {
  int arr[100], n;

  // Input integer array
  printf("Enter the number of elements: ");
  scanf("%d", &n);

  printf("Enter the elements: ");
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  pid_t pid1, pid2;

  pid1 = fork();

  if (pid1 < 0) {
    perror("Fork failed");
    return 1;
  } else if (pid1 == 0) {
    print_odd_numbers(arr, n);
    return 0;
  } else {
    waitpid(pid1, NULL, 0);

    pid2 = fork();

    if (pid2 < 0) {
      perror("Fork failed");
      return 1;
    } else if (pid2 == 0) {
      print_even_numbers(arr, n);
      return 0;
    } else {
      // Parent process
      waitpid(pid2, NULL, 0); // Wait for the second child process to finish
    }
  }

  return 0;
}
