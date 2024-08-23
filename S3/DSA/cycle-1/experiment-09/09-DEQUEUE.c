/*
 * Experiment - 09
 * Write a menu driven program to implement a Double-Ended Queue (DEQUEUE). with
 * the following operations. The elements of the queue are strings. Wherever you
 * are deleting an entry from the queue, display whether that string is
 * palindrome or not.
 * 1. Insert elements to the front of the queue.
 * 2. Insert elements to the rear of the queue
 * 3. Delete elements from the Front of the queue.
 * 4. Delete elements from the Rear of the queue.
 * 5. Display the contents of the queue.
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
  int length;
  int capacity;
  char **front;
  char **rear;
  char **strings;
} Queue;

void display_menu();
void handle_choice(Queue *queue);
int is_full(Queue *queue);
int is_empty(Queue *queue);
void enqueue_at_front(Queue *queue, char *string);
void enqueue_at_rear(Queue *queue, char *string);
char *dequeue_from_front(Queue *queue);
char *dequeue_from_rear(Queue *queue);
void display_queue(Queue *queue);

int main() {
  Queue *queue = (Queue *)calloc(1, sizeof(Queue));
  queue->capacity = MAX;
  char **strings = (char **)calloc(queue->capacity, sizeof(char));
  queue->strings = strings;
  queue->front = queue->strings;
  queue->rear = queue->strings;
  while (1) {
    display_menu();
    handle_choice(queue);
  }
  return 0;
}

int is_full(Queue *queue) {
  if (queue->length == queue->capacity) {
    fprintf(stderr, "\nERROR: Queue is full\n");
    return 1;
  }
  return 0;
}

int is_empty(Queue *queue) {
  if (queue->length == 0) {
    fprintf(stderr, "\nERROR: Queue is empty\n");
    return 1;
  }
  return 0;
}

void enqueue_at_front(Queue *queue, char *string) {
  if (is_full(queue))
    return;
  else {
    if (*(queue->front) != NULL && queue->front == queue->strings)
      queue->front = queue->strings + queue->capacity - 1;
    else if (*(queue->front) != NULL)
      queue->front = queue->front - 1;
    *(queue->front) = string;
  }
};
void enqueue_at_rear(Queue *queue, char *string) {
  if (is_full(queue))
    return;
  else {
    if (*(queue->rear) != NULL &&
        queue->rear == queue->strings + queue->capacity - 1)
      queue->rear = queue->strings;
    else if (*(queue->rear) != NULL)
      queue->rear = queue->rear + 1;
    *(queue->rear) = string;
  }
};
char *dequeue_from_front(Queue *queue) {
  if (is_empty(queue))
    return NULL;
  else {
    char *tmp = *(queue->front);
    *(queue->front) = NULL;
    if (queue->front == queue->strings + queue->capacity - 1)
      queue->front = queue->strings;
    else
      queue->front = queue->front + 1;
    return tmp;
  }
  return NULL;
};
char *dequeue_from_rear(Queue *queue) {
  if (is_empty(queue))
    return NULL;
  else {
    char *tmp = *(queue->rear);
    *(queue->rear) = NULL;
    if (queue->rear == queue->strings)
      queue->rear = queue->strings + queue->capacity - 1;
    else
      queue->rear = queue->rear - 1;
    return tmp;
  }
  return NULL;
};

void display_menu() {
  printf("\n---- MENU ----\n");
  printf("1. Insert elements to the front of the queue.\n");
  printf("2. Insert elements to the rear of the queue\n");
  printf("3. Delete elements from the front of the queue.\n");
  printf("4. Delete elements from the rear of the queue.\n");
  printf("5. Display the contents of the queue.\n");
  printf("6. Exit\n");
  printf("Choice: ");
}

void handle_choice(Queue *queue) {
  int choice;
  char *string = calloc(MAX, sizeof(char));
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    fprintf(stdout, "Provide some text: ");
    fscanf(stdin, "%s", string);
    enqueue_at_front(queue, string);
    break;
  case 2:
    fprintf(stdout, "Provide some text: ");
    fscanf(stdin, "%s", string);
    enqueue_at_rear(queue, string);
    break;
  case 3:
    fprintf(stdout, "Provide some text: ");
    fscanf(stdin, "%s", string);
    dequeue_from_front(queue);
    break;
  case 4:
    fprintf(stdout, "Provide some text: ");
    fscanf(stdin, "%s", string);
    dequeue_from_rear(queue);
    break;
  case 5:
    display_queue(queue);
    break;
  case 6:
    printf("Exiting...\n");
    exit(0);
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}
