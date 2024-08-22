/*
 * In a relief camp food packets are supplied to persons based on the following
 * conditions. Only 3 packets are supplied to a person at a time. He will be
 * supplied with tokens according to the number of persons in his family. Only
 * one person from a family is allowed in the queue. There can be a maximum of
 * only N persons in the queue at any time. A person can be allowed to enter the
 * end of the queue if he has to collect more packets. Simulate these conditions
 * using a circular queue with the following operations:
 * 1. Allow a new person at the end of the queue, if the queue is not full.
 * 2. Number of persons in the queue.
 * 3. Display all persons in the queue with the number of tokens they have.
 * 4. Supplying food to the person in front of the queue.
 * Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int token_number;
  int food_coupons;
} Token;

typedef struct {
  int length;
  int capacity;
  Token **front;
  Token **rear;
  Token **tokens;
} Queue;

void display_menu();
void handle_choice(Queue *queue);
int is_full(Queue *queue);
int is_empty(Queue *queue);
void enqueue(Queue *queue, int food_coupons);
Token *dequeue(Queue *queue);

int main() {
  Queue *queue = (Queue *)calloc(1, sizeof(Queue));
  printf("How many people can the queue have at-most? ");
  scanf("%d", &(queue->capacity));
  Token **tokens = (Token **)calloc(queue->capacity, sizeof(Token));
  queue->tokens = tokens;
  queue->front = queue->tokens;
  queue->rear = queue->tokens;
  while (1) {
    display_menu();
    handle_choice(queue);
  }
  return 0;
}

int is_full(Queue *queue) {
  if (queue->length == queue->capacity)
    return 1;
  return 0;
}

int is_empty(Queue *queue) {
  if (queue->length == 0)
    return 1;
  return 0;
}

void enqueue(Queue *queue, int food_coupons) {
  if (is_full(queue)) {
    fprintf(stderr, "\nQueue is full!\n");
    return;
  } else if (is_empty(queue)) {
    Token *token = (Token *)calloc(1, sizeof(Token));
    *token = (Token){
        .token_number = 1,
        .food_coupons = food_coupons,
    };
    *(queue->rear) = token;
  } else {
    printf("Test 4\n");
    Token *token = (Token *)calloc(1, sizeof(Token));
    *token = (Token){.token_number = (*(queue->rear))->token_number + 1,
                     .food_coupons = food_coupons};
    if (queue->rear == queue->tokens + queue->capacity) {

      printf("Test 5\n");
      queue->rear = queue->tokens;

      printf("Test 6\n");
    } else {
      printf("Test 7\n");
      queue->rear = queue->rear + 1;
    }
    *(queue->rear) = token;
    printf("Test 8\n");
  }
  queue->length = queue->length + 1;
}

Token *dequeue(Queue *queue) {
  if (is_empty(queue)) {
    fprintf(stderr, "\nQueue is empty\n");
    return NULL;
  } else {
    Token *tmp = *(queue->front);
    if (queue->front == queue->tokens + queue->capacity)
      queue->front = queue->tokens;
    else
      queue->front = queue->front + 1;
    if (queue->front == queue->rear) {
      queue->front = queue->tokens;
      queue->rear = queue->tokens;
    }
    queue->length = queue->length - 1;
    return tmp;
  }
}

void display_menu() {
  printf("1. Add a new person to the queue\n");
  printf("2. Display the number of people in the queue\n");
  printf("3. Display all people in the queue\n");
  printf("4. Supply food to the person in front of the queue\n");
  printf("5. Exit\n");
  printf("Choice: ");
}

void handle_choice(Queue *queue) {
  int choice;
  Token *token = NULL;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    printf("How many food coupons are required? ");
    int food_coupons;
    scanf("%d", &food_coupons);
    enqueue(queue, food_coupons);
    break;
  case 2:
    printf("Number of people in the queue: %d\n", queue->length);
    break;
  case 3:
    printf("People in the queue: ");
    for (int i = 0; i < queue->length; i++) {
      printf("%d, ", (*(queue->front + i))->token_number);
    }
    printf("\n");
    break;
  case 4:
    token = dequeue(queue);
    if (token != NULL) {
      int pending = token->food_coupons - 3;
      if (pending > 0) {
        enqueue(queue, pending);
      }
      printf("Supplied food to person with token number %d and has %d pending "
             "food coupons",
             token->token_number, pending);
    }
    break;
  case 5:
    printf("Exiting...\n");
    exit(0);
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}
