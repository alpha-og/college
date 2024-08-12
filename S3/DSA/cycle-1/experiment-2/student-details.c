/*
 * Experiment - 02
 * A text file contains register number, name and CGPA of students in a class in
 the following format:

   | (10 characters) | (20 characters) | (5 digits) |
   | --------------- | --------------- | ---------- |
   | Register Number | Name            | CGPA       |

   Details of each student is stored in a separate line. Write a menu driven
 program for:

   1. Displaying the list of students in the order of register number
   2. Display the name and CGPA of a student with given register number.

   Use bubble sort for preparing list. Find a particular student's details in
 the list using binary search. Write separate functions for bubble sort and
 binary search.
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
  char register_number[11];
  char name[21];
  float cgpa;
} Student;

Student *read_students(int *record_count);
void display_students(Student *students, int record_count);
void bubble_sort(Student *students, int record_count);
void binary_search(Student *students, int record_count, char key[]);

int main() {
  int record_count = 0;
  Student *students = read_students(&record_count);
  printf("List of students:\n");
  display_students(students, record_count);
  printf("Search for a student: ");
  char query[11] = {'\0'};
  scanf("%10c", query);
  binary_search(students, record_count, query);

  return 0;
}

Student *read_students(int *record_count) {
  Student *students = (Student *)malloc(MAX * sizeof(Student));

  FILE *fptr = fopen("sample.txt", "r");
  if (fptr == NULL) {
    printf("Error opening file\n");
    exit(1);
  }
  while (fscanf(fptr, "%10c%20c%f", students[*record_count].register_number,
                students[*record_count].name,
                &(students[*record_count].cgpa)) != EOF) {
    fgetc(fptr);
    *record_count += 1;
  }
  fclose(fptr);
  return students;
}

void display_students(Student *students, int record_count) {
  bubble_sort(students, record_count);
  for (int i = 0; i < record_count; i++) {
    printf("Register Number: %s Name: %s CGPA: %f\n",
           students[i].register_number, students[i].name, students[i].cgpa);
  }
}

void bubble_sort(Student *students, int record_count) {
  for (int i = 0; i < record_count; i++) {
    for (int j = 0; j < record_count - i - 1; j++) {
      if (strcmp(students[j].register_number, students[j + 1].register_number) >
          0) {
        Student tmp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = tmp;
      }
    }
  }
}

void binary_search(Student *students, int record_count, char key[]) {
  bubble_sort(students, record_count);
  printf("Query: %10s\n", key);
  int beginning = 0;
  int end = record_count - 1;
  int mid = (end - beginning) / 2;
  int count = 0;
  int found = 0;
  while (count < record_count) {
    count++;
    if (strcmp(key, students[mid].register_number) < 0) {
      end = mid - 1;
      mid = (end - beginning) / 2;
    } else if (strcmp(key, students[mid].register_number) > 0) {
      beginning = mid + 1;
      mid = beginning + (end - beginning) / 2;
    } else if (strcmp(key, students[mid].register_number) == 0) {
      found = 1;
      break;
    }
  }
  if (found == 1)
    printf("Register Number: %s Name: %s CGPA: %f\n",
           students[mid].register_number, students[mid].name,
           students[mid].cgpa);
  else
    printf("Record not found\n");
}
