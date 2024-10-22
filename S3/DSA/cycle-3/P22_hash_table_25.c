#include <stdio.h>
#include <stdlib.h>

// structure representing node
typedef struct Node {
  int data;
  struct Node *next;
} Node;

#define TABLE_SIZE 10
#define EMPTY -1 // marker for empty slots

// function declarations
int hash_function(int key);
Node *create_node(int data);
void insert_chaining(Node *hash_table[], int value);
void display_chaining(Node *hash_table[]);
void insert_linear_probing(int hash_table[], int value);
void display_linear_probing(int hash_table[]);
void display_menu();
void handle_choice();

int main() {
  display_menu();

  // main loop
  while (1) {
    handle_choice();
  }
  return 0;
}

// hash function to compute index
int hash_function(int key) { return key % TABLE_SIZE; }

// create a new node
Node *create_node(int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

// insert value into hash table (chaining)
void insert_chaining(Node *hash_table[], int value) {
  int index = hash_function(value);
  Node *new_node = create_node(value);
  new_node->next = hash_table[index];
  hash_table[index] = new_node;
}

// display the hash table (chaining)
void display_chaining(Node *hash_table[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    printf("index %d: ", i);
    Node *temp = hash_table[i];
    while (temp != NULL) {
      printf("%d -> ", temp->data);
      temp = temp->next;
    }
    printf("NULL\n");
  }
}

// insert value using linear probing
void insert_linear_probing(int hash_table[], int value) {
  int index = hash_function(value);

  // find the next available slot
  while (hash_table[index] != EMPTY) {
    index = (index + 1) % TABLE_SIZE;
  }
  hash_table[index] = value;
}

// display the hash table (linear probing)
void display_linear_probing(int hash_table[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == EMPTY) {
      printf("index %d: NULL\n", i);
    } else {
      printf("index %d: %d\n", i, hash_table[i]);
    }
  }
}

// display menu options
void display_menu() {
  printf("\nHash Table Operations:\n");
  printf("1. Chaining\n");
  printf("2. Linear Probing\n");
  printf("3. Display menu\n");
  printf("4. Exit\n");
}

// handle user's choice
void handle_choice() {
  int choice, num_values;
  printf("\nChoose an option: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1: { // Chaining
    Node *hash_table[TABLE_SIZE] = {NULL};

    printf("Enter number of values to insert: ");
    scanf("%d", &num_values);
    for (int i = 0; i < num_values; i++) {
      int value;
      printf("Enter value %d: ", i + 1);
      scanf("%d", &value);
      insert_chaining(hash_table, value);
    }

    printf("\nHash Table (Chaining):\n");
    display_chaining(hash_table);
    break;
  }
  case 2: { // Linear Probing
    int hash_table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
      hash_table[i] = EMPTY; // initialize with EMPTY values
    }

    printf("Enter number of values to insert: ");
    scanf("%d", &num_values);
    for (int i = 0; i < num_values; i++) {
      int value;
      printf("Enter value %d: ", i + 1);
      scanf("%d", &value);
      insert_linear_probing(hash_table, value);
    }

    printf("\nHash Table (Linear Probing):\n");
    display_linear_probing(hash_table);
    break;
  }
  case 3:
    display_menu();
    break;
  case 4: // Exit
    printf("Exiting the program...\n");
    exit(0);
    break;
  default:
    printf("Invalid choice. Please try again.\n");
  }
}
