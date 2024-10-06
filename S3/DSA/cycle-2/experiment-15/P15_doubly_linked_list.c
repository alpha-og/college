#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct DoublyLinkedList {
  Node *head;
  Node *tail;
} DoublyLinkedList;

int is_empty(DoublyLinkedList *list);
Node *create_node(int data);
DoublyLinkedList *create_list(void);
void insert_at(DoublyLinkedList *list, int data, int index);
void insert_after_key(DoublyLinkedList *list, int data);
void delete_at(DoublyLinkedList *list, int index);
void delete_by_key(DoublyLinkedList *list);
void display_list(DoublyLinkedList *list, int order);
Node *find_node_by_key(DoublyLinkedList *list, int key);
int read_data();
int read_key();
void display_menu();
void handle_choice(DoublyLinkedList *list);

int main(void) {
  DoublyLinkedList *list = create_list();

  display_menu();
  while (1) {
    handle_choice(list);
  }
  return 0;
}

int is_empty(DoublyLinkedList *list) { return list->head->next == list->tail; }

Node *create_node(int data) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

DoublyLinkedList *create_list() {
  DoublyLinkedList *list = calloc(1, sizeof(DoublyLinkedList));
  list->head = create_node(0);
  list->tail = create_node(0);
  list->head->next = list->tail;
  list->tail->prev = list->head;
  return list;
}

void insert_at(DoublyLinkedList *list, int data, int index) {
  Node *node = create_node(data);
  if (index == 0) {
    node->next = list->head->next;
    node->prev = list->head;
    list->head->next->prev = node;
    list->head->next = node;
  } else if (index == -1) {
    node->next = list->tail;
    node->prev = list->tail->prev;
    list->tail->prev->next = node;
    list->tail->prev = node;
  }
}

void insert_after_key(DoublyLinkedList *list, int data) {
  int key = read_key();
  Node *node = create_node(data);
  Node *match = find_node_by_key(list, key);
  if (match == NULL) {
    return;
  }
  node->next = match->next;
  match->next->prev = node;
  match->next = node;
  node->prev = match;
}

void delete_at(DoublyLinkedList *list, int index) {
  Node *node = NULL;
  if (index == 0) {
    node = list->head->next;
    list->head->next = list->head->next->next;
    list->head->next->prev = list->head;
  } else if (index == -1) {
    node = list->tail->prev;
    list->tail->prev = list->tail->prev->prev;
    list->tail->prev->next = list->tail;
  }
  fprintf(stdout, "Deleted node with data %d\n", node->data);
  free(node);
}

void delete_by_key(DoublyLinkedList *list) {
  int key = read_key();
  Node *match = find_node_by_key(list, key);
  if (match == NULL) {
    return;
  }
  match->prev->next = match->next;
  match->next->prev = match->prev;
  fprintf(stdout, "Deleted node with data %d\n", match->data);
  free(match);
}

int read_key() {
  int key;
  printf("Enter key: ");
  scanf("%d", &key);
  return key;
}

int read_data() {
  int data;
  printf("Enter data: ");
  scanf("%d", &data);
  getchar();
  return data;
}

Node *find_node_by_key(DoublyLinkedList *list, int key) {
  Node *node = list->head->next;
  while (node->data != key && node->next != list->tail) {
    node = node->next;
  }
  if (node->data == key) {
    return node;
  } else {
    fprintf(stderr, "Key not found\n");
    return NULL;
  }
  return node;
}

void display_list(DoublyLinkedList *list, int order) {
  if (order == 1) {
    Node *node = list->head->next;
    while (node != list->tail) {
      fprintf(stdout, "%d ", node->data);
      node = node->next;
    }
  } else if (order == 2) {
    Node *node = list->tail->prev;
    while (node != list->head) {
      fprintf(stdout, "%d ", node->data);
      node = node->prev;
    }
  }
  fprintf(stdout, "\n");
}

void display_menu() {
  fprintf(stdout, "\n---- Menu ----\n");
  fprintf(stdout, "1. Display menu\n");
  fprintf(stdout, "2. Insert at beginning\n");
  fprintf(stdout, "3. Insert at end\n");
  fprintf(stdout, "4. Insert after key\n");
  fprintf(stdout, "5. Delete at beginning\n");
  fprintf(stdout, "6. Delete at end\n");
  fprintf(stdout, "7. Delete by key\n");
  fprintf(stdout, "8. Display list from beginning\n");
  fprintf(stdout, "9. Display list from end\n");
  fprintf(stdout, "10. Exit\n");
}

void handle_choice(DoublyLinkedList *list) {
  fprintf(stdout, "\nChoice: ");
  int choice;
  scanf("%d", &choice);
  if (is_empty(list) && (choice > 4 && choice < 10)) {
    fprintf(stderr, "List is empty\n");
    return;
  }
  switch (choice) {
  case 1:
    display_menu();
    break;
  case 2:
    insert_at(list, read_data(), 0);
    break;
  case 3:
    insert_at(list, read_data(), -1);
    break;
  case 4:
    insert_after_key(list, read_data());
    break;
  case 5:
    delete_at(list, 0);
    break;
  case 6:
    delete_at(list, -1);
    break;
  case 7:
    delete_by_key(list);
    break;
  case 8:
    display_list(list, 1);
    break;
  case 9:
    display_list(list, 2);
    break;
  case 10:
    fprintf(stdout, "Exiting...\n");
    exit(0);
    break;
  default:
    fprintf(stdout, "Invalid choice\n");
    break;
  }
}
