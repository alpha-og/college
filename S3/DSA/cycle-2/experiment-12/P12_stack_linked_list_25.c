/*
Experiment 12
Implementation of stack using linked list
25 - Athul Anoop - S3B2
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	struct Node * next;
} Node;

typedef struct Stack {
	Node * top;
	Node * nodes;
} Stack;

int is_empty(Stack * stack);
Node * create_node(int value);
void push(Stack * stack, Node * node);
Node * pop(Stack * stack);
void display_stack(Stack * stack);
void display_menu();
void handle_choice(Stack * stack);

int main(){
	Stack * stack = calloc(1,sizeof(Stack));
	while (1){
		display_menu();
		handle_choice(stack);
	}
	return 0;
}

int is_empty(Stack * stack){
	if (stack->top == NULL)
		return 1;
	else
		return 0;
}

Node *create_node(int value) {
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  new_node->value = value;
  return new_node;
}

void push(Stack * stack, Node *new_node) {
	if (is_empty(stack) == 0)
    	new_node->next = stack->top;
    stack->top = new_node;
}

Node * pop(Stack * stack) {
  if (is_empty(stack)) {
    fprintf(stderr, "\nERROR: Stack is empty\n");
    return NULL;
  }
  Node *tmp = stack->top;
  stack->top = stack->top->next;
  return tmp;
}

void display_stack (Stack * stack){
	if (is_empty(stack)){
		fprintf(stderr, "\nERROR: Stack is empty\n");
		return;
	}
	Node * current = stack->top;
	fprintf(stdout, "Stack elements: [");
	while (current != NULL){
		fprintf(stdout, " %d", current->value);
		current = current->next;
		if (current != NULL)
			fprintf(stdout, ", ");
	}
	fprintf(stdout, " ]\n");
}
 
void display_menu(){
	fprintf(stdout, "\n ---- Menu ---- \n");
	fprintf(stdout, "1. Push\n");
	fprintf(stdout, "2. Pop\n");
	fprintf(stdout, "3. Display\n");
	fprintf(stdout, "4. Exit\n");
	fprintf(stdout, "Choice: ");
}

void handle_choice(Stack * stack){
	int choice = 0;
	int value = 0;
	Node * tmp = NULL;
	scanf("%d", &choice);
	switch (choice){
		case 1:
			fprintf(stdout, "Enter value: ");
			scanf("%d", &value);
			push(stack,create_node(value));
			break;
		case 2:
			tmp = pop(stack);
			if (tmp != NULL)
				fprintf(stdout, "Popped %d from stack", tmp->value);
			break;
		case 3:
			display_stack(stack);
			break;
		case 4:
			fprintf(stdout, "Exiting...\n");
			exit(0);
			break;
		default:
			fprintf(stderr, "Invalid choice\n");
	}
}
