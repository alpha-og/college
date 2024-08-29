/*
Experiment - 11
Write a menu driven program for performing the following operations on a Linked
List:
a. Display the contents
b. Insert at the Beginning
c. Insert at the End
d. Insert after a given node
e. Delete from Beginning
f. Delete from End
g. Delete a node with a key value
Athul Anoop
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  struct Node *head;
  struct Node *items;
} LinkedList;

Node *create_node(int value);
void insert_node(LinkedList *list, Node *new_node, int mode);
Node *get_node(LinkedList *list, int mode);
void delete_node(LinkedList *list, int mode);
void display_linked_list(LinkedList *list);
void display_menu();
void handle_choice(LinkedList *list);

int main() {
  LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
  while (1) {
    display_menu();
    handle_choice(list);
  }
  return 0;
}

Node *create_node(int value) {
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  new_node->value = value;
  return new_node;
}

void insert_node(LinkedList *list, Node *new_node, int mode) {
  if (mode == 0) {
    new_node->next = list->head;
    list->head = new_node;
  } else if (mode == 1) {
    Node *current = get_node(list, mode);
    current->next = new_node;
  } else {
    Node *current = get_node(list, mode);
    new_node->next = current->next;
    current->next = new_node;
  }
}

Node *get_node(LinkedList *list, int mode) {
  Node *current = list->head;
  if (mode == 1) {
    while (current->next != NULL) {
      current = current->next;
    }
  } else {
    int key = 0;
    fprintf(stdout, "Enter key value: ");
    scanf("%d", &key);
    while (current->value != key) {
      current = current->next;
    }
  }
  return current;
}

void delete_node(LinkedList *list, int mode) {
  if (list->head == NULL) {
    fprintf(stderr, "List is empty\n");
    return;
  }
  Node *tmp = NULL;
  if (mode == 0) {
    tmp = list->head;
    (list->head) = list->head->next;
  } else if (mode == 1) {
    Node *current = list->head;
    while (current->next->next != NULL) {
      current = current->next;
    }
    tmp = current->next;
    current->next = NULL;
  } else {
    int key = 0;
    fprintf(stdout, "Enter key value: ");
    scanf("%d", &key);
    Node *current = list->head;
    while (current->next->value != key) {
      current = current->next;
    }
    tmp = current->next;
    current->next = current->next->next;
  }
  free(tmp);
}

void display_linked_list(LinkedList *list) {
  Node *current = list->head;
  fprintf(stdout, "[ ");
  while (current != NULL) {
    fprintf(stdout, "%d, ", current->value);
    current = current->next;
  }
  fprintf(stdout, " ]\n");
}

void display_menu() {
  fprintf(stdout, "\n ---- MENU ----\n");
  fprintf(stdout, "1. Display\n");
  fprintf(stdout, "2. Insert at Beginning\n");
  fprintf(stdout, "3. Insert at End\n");
  fprintf(stdout, "4. Insert After\n");
  fprintf(stdout, "5. Delete from Beginning\n");
  fprintf(stdout, "6. Delete from End\n");
  fprintf(stdout, "7. Delete with Key\n");
  fprintf(stdout, "8. Exit\n");
  fprintf(stdout, "Choice: ");
}

void handle_choice(LinkedList *list) {
  int choice = 0;
  int value = 0;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    display_linked_list(list);
    break;
  case 2:
    fprintf(stdout, "Enter the value to be inserted: ");
    scanf("%d", &value);
    if (list->head == NULL) {
      list->items = create_node(value);
      list->head = list->items;
    } else {
      insert_node(list, create_node(value), 0);
    }
    break;
  case 3:
    fprintf(stdout, "Enter the value to be inserted: ");
    scanf("%d", &value);
    if (list->head == NULL) {
      list->items = create_node(value);
      list->head = list->items;
    } else {
      insert_node(list, create_node(value), 1);
    }
    break;
  case 4:
    fprintf(stdout, "Enter the value to be inserted: ");
    scanf("%d", &value);
    if (list->head == NULL) {
      list->items = create_node(value);
      list->head = list->items;
    } else {
      insert_node(list, create_node(value), 2);
    }
    break;
  case 5:
    delete_node(list, 0);
    break;
  case 6:
    delete_node(list, 1);
    break;
  case 7:
    delete_node(list, 2);
    break;
  case 8:
    fprintf(stdout, "Exiting...\n");
    exit(0);
  default:
    fprintf(stdout, "Invalid Choice\n");
    break;
  }
}
