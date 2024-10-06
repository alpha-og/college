#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

LinkedList *read_number();
int is_empty(LinkedList *list);
Node *create_node(int value);
Node *get_last_node(LinkedList *list);
Node *swap_nodes(Node *first, Node *second, Node *third);
void reverse_linked_list(LinkedList *list);
void display_linked_list(LinkedList *list);
LinkedList *add(LinkedList **lists);
void add_digits(Node *first, Node *second);
void display_menu();
void handle_choice(LinkedList **list);
int choose_linked_list();

int main() {
  LinkedList **numbers = calloc(2, sizeof(LinkedList *));
  while (1) {
    display_menu();
    handle_choice(numbers);
  }
  return 0;
}

int is_empty(LinkedList *list) {
  if (list == NULL || list->head->next == NULL)
    return 1;
  else
    return 0;
}

Node *create_node(int value) {
  Node *new_node = calloc(1, sizeof(Node));
  new_node->value = value;
  return new_node;
}

LinkedList *create_linked_list() {
  LinkedList *list = calloc(1, sizeof(LinkedList));
  list->head = create_node(0);
  return list;
}

Node *get_last_node(LinkedList *list) {
  Node *current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }
  return current;
}

LinkedList *read_number() {
  LinkedList *number = create_linked_list();
  fprintf(stdout, "Enter a number: ");
  char ch = '\0';
  while ((ch = getchar()) != '\n') {
    if (ch >= '0' && ch <= '9') {
      Node *new_node = create_node(ch - '0');
      get_last_node(number)->next = new_node;
    } else {
      fprintf(stderr, "Invalid input\n");
      break;
    }
  }
  return number;
}

void display_linked_list(LinkedList *list) {
  if (is_empty(list)) {
    fprintf(stderr, "\nERROR: List is empty\n");
    return;
  }
  Node *current = list->head->next;
  fprintf(stdout, "Number: ");
  while (current != NULL) {
    fprintf(stdout, "%d", current->value);
    current = current->next;
  }
  fprintf(stdout, "\n");
}

Node *swap_nodes(Node *first, Node *second, Node *third) {
  if (third == NULL)
    return second;
  Node *tmp = third->next;
  third->next = second;
  second->next = first;
  return swap_nodes(second, third, tmp);
}

void reverse_linked_list(LinkedList *list) {
  if (is_empty(list))
    return;
  list->head->next = swap_nodes(NULL, list->head->next, list->head->next->next);
}

LinkedList *add(LinkedList **lists) {
  if (is_empty(lists[0]) || is_empty(lists[1])) {
    fprintf(stderr, "\nERROR: List(s) is/ are empty\n");
    return NULL;
  }

  reverse_linked_list(lists[0]);
  reverse_linked_list(lists[1]);

  Node *current1 = lists[0]->head->next;
  Node *current2 = lists[1]->head->next;

  while (1) {
    if (current1 != NULL && current2 != NULL) {
      add_digits(current1, current2);
      if (current1->next == NULL && current2->next != NULL) {
        current1->next = current2->next;
        break;
      } else {
        current1 = current1->next;
      }
    } else {
      break;
    }
    current2 = current2->next;
  }
  reverse_linked_list(lists[0]);
  free(lists[0]);
  free(lists[1]);
  lists[0] = NULL;
  lists[1] = NULL;
  return lists[0];
}

void add_digits(Node *first, Node *second) {
  int sum = first->value + second->value;
  int ones_digit = sum % 10;
  first->value = ones_digit;
  int tens_digit = sum / 10;
  if (tens_digit == 0) {
    return;
  }
  if (first->next != NULL)
    add_digits(first->next, create_node(tens_digit));
  else
    first->next = create_node(tens_digit);
}

int choose_linked_list() {
  int choice = 0;
  fprintf(stdout, "Choose a number index (0-1): ");
  scanf("%d", &choice);
  getchar();
  switch (choice) {
  case 0:
  case 1:
    return choice;
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
    return -1;
    break;
  }
}

void display_menu() {
  fprintf(stdout, "\n ---- Menu ---- \n");
  fprintf(stdout, "1. Create a number\n");
  fprintf(stdout, "2. Display the number\n");
  fprintf(stdout, "3. Add the numbers\n");
  fprintf(stdout, "4. Exit\n");
  fprintf(stdout, "Choice: ");
}

void handle_choice(LinkedList **numbers) {
  int choice = 0;
  int index = -1;
  Node *tmp = NULL;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    index = choose_linked_list();
    if (index == -1)
      break;
    numbers[index] = read_number();
    break;
  case 2:
    index = choose_linked_list();
    if (index == -1)
      break;
    display_linked_list(numbers[index]);
    break;
  case 3:
    display_linked_list(add(numbers));
    break;
  case 4:
    fprintf(stdout, "Exiting...\n");
    exit(0);
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
    break;
  }
}
