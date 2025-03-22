/* Athul Anoop
 * Roll no: 25
 * Description: C program implementing memory allocation methods for fixed
 * partition
 */

#include <stdbool.h>
#include <stdio.h>

#define MAX_PARTITIONS 5

typedef struct {
  int size;
  bool allocated;
} Partition;

void display_menu();

Partition partitions[MAX_PARTITIONS] = {
    {100, false}, {500, false}, {200, false}, {300, false}, {600, false}};

// helper function to display partitions
void display_partitions() {
  printf("\nPartition Status:\n");
  for (int i = 0; i < MAX_PARTITIONS; i++) {
    printf("Partition %d: Size = %d, %s\n", i, partitions[i].size,
           partitions[i].allocated ? "Allocated" : "Free");
  }
}

// First Fit Allocation
int first_fit(int request_size) {
  for (int i = 0; i < MAX_PARTITIONS; i++) {
    if (!partitions[i].allocated && partitions[i].size >= request_size) {
      partitions[i].allocated = true;
      return i;
    }
  }
  return -1;
}

// Worst Fit Allocation
int worst_fit(int request_size) {
  int index = -1, max_size = -1;
  for (int i = 0; i < MAX_PARTITIONS; i++) {
    if (!partitions[i].allocated && partitions[i].size >= request_size &&
        partitions[i].size > max_size) {
      max_size = partitions[i].size;
      index = i;
    }
  }
  if (index != -1) {
    partitions[index].allocated = true;
  }
  return index;
}

// Best Fit Allocation
int best_fit(int request_size) {
  int index = -1, min_size = __INT_MAX__;
  for (int i = 0; i < MAX_PARTITIONS; i++) {
    if (!partitions[i].allocated && partitions[i].size >= request_size &&
        partitions[i].size < min_size) {
      min_size = partitions[i].size;
      index = i;
    }
  }
  if (index != -1) {
    partitions[index].allocated = true;
  }
  return index;
}

int main() {
  int choice, request_size, allocated_partition;

  display_menu();
  while (1) {
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter request size: ");
      scanf("%d", &request_size);
      allocated_partition = first_fit(request_size);
      if (allocated_partition != -1)
        printf("Allocated at partition %d\n", allocated_partition);
      else
        printf("No suitable partition found.\n");
      break;

    case 2:
      printf("Enter request size: ");
      scanf("%d", &request_size);
      allocated_partition = worst_fit(request_size);
      if (allocated_partition != -1)
        printf("Allocated at partition %d\n", allocated_partition);
      else
        printf("No suitable partition found.\n");
      break;

    case 3:
      printf("Enter request size: ");
      scanf("%d", &request_size);
      allocated_partition = best_fit(request_size);
      if (allocated_partition != -1)
        printf("Allocated at partition %d\n", allocated_partition);
      else
        printf("No suitable partition found.\n");
      break;

    case 4:
      display_partitions();
      break;

    case 5:
      display_menu();
      break;
    case 6:
      return 0;

    default:
      printf("Invalid choice! Try again.\n");
    }
  }
}

void display_menu() {
  printf("\nMemory Allocation Methods:\n");
  printf("1. First Fit\n2. Worst Fit\n3. Best Fit\n4. Display Partitions\n5. "
         "Display Menu\n6. "
         "Exit\n");
}
