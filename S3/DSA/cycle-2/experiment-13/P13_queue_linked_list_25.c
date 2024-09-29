/*
Experiment 13
Implementation of queue using linked list
25 - Athul Anoop - S3B2
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct Queue {
  int capacity;
  int length;
  Node *front;
  Node *rear;
  Node *nodes;
} Queue;

int is_empty(Queue *queue);
Node *create_node(int value);
void enqueue(Queue *queue, Node *node);
Node *dequeue(Queue *queue);
void display_queue(Queue *queue);
void display_menu();
void handle_choice(Queue *queue);

int main() {
  Queue *queue = calloc(1, sizeof(Queue));
  while (1) {
    display_menu();
    handle_choice(queue);
  }
  return 0;
}

int is_empty(Queue *queue) {
  if (queue->front == NULL)
    return 1;
  else
    return 0;
}

Node *create_node(int value) {
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  new_node->value = value;
  return new_node;
}

void enqueue(Queue *queue, Node *new_node) {
  if (is_empty(queue)) {
    queue->nodes = new_node;
    queue->front = queue->nodes;
    queue->rear = queue->nodes;
  } else {
    queue->rear->next = new_node;
    queue->rear = new_node;
  }
}

Node *dequeue(Queue *queue) {
  if (is_empty(queue)) {
    fprintf(stderr, "\nERROR: Queue is empty\n");
    return NULL;
  }
  Node *tmp = queue->front;
  queue->front = queue->front->next;
  return tmp;
}

void display_queue(Queue *queue) {
  if (is_empty(queue)) {
    fprintf(stderr, "\nERROR: Queue is empty\n");
    return;
  }
  Node *current = queue->front;
  fprintf(stdout, "Queue elements: [");
  while (current != NULL) {
    fprintf(stdout, " %d", current->value);
    current = current->next;
    if (current != NULL)
      fprintf(stdout, ", ");
  }
  fprintf(stdout, " ]\n");
}

void display_menu() {
  fprintf(stdout, "\n ---- Menu ---- \n");
  fprintf(stdout, "1. Enqueue\n");
  fprintf(stdout, "2. Dequeue\n");
  fprintf(stdout, "3. Display\n");
  fprintf(stdout, "4. Exit\n");
  fprintf(stdout, "Choice: ");
}

void handle_choice(Queue *queue) {
  int choice = 0;
  int value = 0;
  Node *tmp = NULL;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    fprintf(stdout, "Enter value: ");
    scanf("%d", &value);
    enqueue(queue, create_node(value));
    break;
  case 2:
    tmp = dequeue(queue);
    if (tmp != NULL)
      fprintf(stdout, "Dequeued %d from queue", tmp->value);
    break;
  case 3:
    display_queue(queue);
    break;
  case 4:
    fprintf(stdout, "Exiting...\n");
    exit(0);
    break;
  default:
    fprintf(stderr, "Invalid choice\n");
  }
}
