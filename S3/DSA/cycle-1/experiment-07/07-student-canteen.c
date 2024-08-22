/*
 * Experiment - 07
 *To regulate the crowd in the college students-only-canteen during lunch break,
 *it is decided to implement a token system. You have to program a token
 *management system wherein a student when entering the canteen, proceeds to a
 *token machine. The machine issues him/her a token bearing a number (in the
 *increasing order of the time at which the student arrives) on it. The students
 *are to be served in the order of token numbers. Have a menu to display the
 *following in your program:
 * 1. The current student being served after dequeue
 * 2. Number of students waiting and queue contents
 * 3. The last token number issued
 * 4. Issue token
 * 5. Exit
 *Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int length;
  int *tokens;
  int *front;
  int *rear;
} Queue;

void display_menu();
void handle_choice(Queue *queue);
int enqueue(Queue *queue, int token);
int dequeue(Queue *queue);
int main() {
  Queue *queue = (Queue *)calloc(1, sizeof(Queue));
  queue->tokens = (int *)calloc(MAX, sizeof(int));
  queue->front = queue->tokens;
  queue->rear = queue->tokens;
  while (1) {
    display_menu();
    handle_choice(queue);
  }
  return 0;
}
void display_menu() {
  printf("\n ---- MENU ----\n");
  printf("1. Display current student being served\n");
  printf("2. Display number of students waiting\n");
  printf("3. Display last token number issued\n");
  printf("4. Issue token\n");
  printf("5. Exit\n");
  printf("Enter your choice: ");
}

void handle_choice(Queue *queue) {
  int choice;
  int token = -1;
  scanf("%d", &choice);
  printf("\n");
  switch (choice) {
  case 1:
    if (queue->length > 0) {
      token = dequeue(queue);
      if (token != -1)
        printf("\nServed token number %d\n", token);
    } else
      printf("\nNo tokens have been issued yet\n");
    break;
  case 2:
    if (queue->length > 0) {
      printf("\nNumber of students waiting is %d\n", queue->length);
      printf("\nQueue contents: ");
      for (int i = 0; i < queue->length; i++) {
        printf("%d ", *(queue->front + i));
      }
      printf("\n");

    } else
      printf("\nNo tokens have been issued yet\n");
    break;
  case 3:
    if (queue->length > 0) {
      printf("\nLast token number issued is %d\n", *(queue->rear));
    } else
      printf("\nNo tokens have been issued yet\n");

    break;
  case 4:
    token = enqueue(queue, *(queue->rear) + 1);
    if (token != -1)
      printf("\nYour token number is %d\n", token);
    break;
  case 5:
    printf("\nExiting...\n");
    exit(0);
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}

int enqueue(Queue *queue, int token) {
  if (queue->length < MAX) {
    if (queue->length != 0)
      queue->rear = queue->rear + 1;
    *(queue->rear) = token;
    queue->length = queue->length + 1;
    return token;
  } else {
    fprintf(stderr, "Queue is full");
    return -1;
  }
}

int dequeue(Queue *queue) {
  if (queue->length > 0) {
    int tmp = *(queue->front);
    *(queue->front) = 0;
    if (queue->length > 1)
      queue->front = queue->front + 1;
    else {
      queue->front = queue->tokens;
      queue->rear = queue->tokens;
    }
    queue->length = queue->length - 1;
    return tmp;
  } else {
    fprintf(stderr, "Queue is empty");
    return -1;
  }
}
