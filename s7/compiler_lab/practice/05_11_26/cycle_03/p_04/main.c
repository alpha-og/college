#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_DFA_STATES (1 << MAX_STATES)
#define MAX_INPUT_SYMBOLS 5
#define QUEUE_SIZE MAX_DFA_STATES

int find_input_symbol(char symbol);
int add_input_symbol(char symbol);
int add_transition(int current_state, char symbol, int next_state);
int add_dfa_transition(int current_state, char symbol, int next_state);
void display_transitions();
int enqueue(int dfa_state[MAX_STATES]);
int deqeue(int dfa_state[MAX_STATES]);
void display_dfa_transitions();

int state_count = 0;
int input_symbol_count = 0;
int transitions[MAX_STATES][MAX_INPUT_SYMBOLS][MAX_STATES] = {};
char input_symbols[MAX_INPUT_SYMBOLS] = {};
int QUEUE[QUEUE_SIZE][MAX_STATES] = {};
int dequeued_dfa_state[MAX_STATES];
int front = -1;
int rear = -1;
int dfa_states[MAX_DFA_STATES][MAX_STATES];
int dfa_transitions[MAX_DFA_STATES][MAX_INPUT_SYMBOLS] = {};

int main() {
  FILE *p_file = fopen("input.txt", "r");
  int current_state = 0;
  int next_state = 0;
  char transition_symbol = '\0';

  for (int i = 0; i < MAX_DFA_STATES; i++) {
    memset(dfa_states[i], -1, MAX_STATES * sizeof(int));
  }

  for (int i = 0; i < MAX_STATES; i++) {
    for (int j = 0; j < MAX_INPUT_SYMBOLS; j++) {
      for (int k = 0; k < MAX_STATES; k++) {
        transitions[i][j][k] = -1;
      }
    }
  }

  for (int i = 0; i < MAX_DFA_STATES; i++) {
    memset(dfa_transitions[i], -1, MAX_INPUT_SYMBOLS * sizeof(int));
  }

  while (fscanf(p_file, "%d %c %d", &current_state, &transition_symbol,
                &next_state) != EOF) {
    int transition_symbol_index = -1;
    if ((transition_symbol_index = find_input_symbol(transition_symbol)) < 0)
      transition_symbol_index = add_input_symbol(transition_symbol);

    if (transition_symbol_index < 0) {
      fprintf(stderr, "max transition symbol count exceeded\n");
      exit(EXIT_FAILURE);
    }

    add_transition(current_state, transition_symbol, next_state);

    state_count = state_count < current_state ? current_state : state_count;
    state_count = state_count < next_state ? next_state : state_count;
  }
  state_count++;

  fprintf(stdout, "states(%d): { ", state_count);
  for (int i = 0; i < state_count; i++) {
    fprintf(stdout, "%d ", i);
  }
  fprintf(stdout, "}\n");

  fprintf(stdout, "input_symbols(%d): { ", input_symbol_count);
  for (int i = 0; i < input_symbol_count; i++) {
    fprintf(stdout, "%c ", input_symbols[i]);
  }
  fprintf(stdout, "}\n");

  fprintf(stdout, "\nNFA\n");
  display_transitions();

  int start_state[MAX_STATES] = {};
  memset(start_state, -1, MAX_STATES * sizeof(int));
  start_state[0] = 0;
  dfa_states[0][0] = start_state[0];
  enqueue(start_state);

  while (deqeue(dequeued_dfa_state) >= 0) {
    for (int i = 0; i < input_symbol_count; i++) {
      int dfa_state[MAX_STATES];
      int dfa_state_count = 0;
      memset(dfa_state, -1, MAX_STATES * sizeof(int));
      for (int j = 0; j < state_count; j++) {
        int state = dequeued_dfa_state[j];
        if (state < 0)
          break;
        for (int k = 0; k < state_count; k++) {
          int next_state = transitions[state][i][k];
          if (next_state < 0)
            break;
          int index = 0;
          int exists = 0;
          while (index < MAX_STATES && dfa_state[index] != -1) {
            if (dfa_state[index] == next_state) {
              exists = 1;
              break;
            }
            index++;
          }
          if (index != MAX_STATES && !exists) {
            dfa_state[index] = next_state;
            dfa_state_count++;
          }
        }
      }
      int index = 0;
      int exists = 0;
      while (index < MAX_DFA_STATES && dfa_states[index][0] != -1) {
        int match = dfa_state_count;
        for (int j = 0; j < MAX_STATES; j++) {
          if (dfa_states[index][j] < 0)
            break;
          for (int k = 0; k < MAX_STATES; k++) {
            if (dfa_state[k] < 0)
              break;
            if (dfa_states[index][j] == dfa_state[k]) {
              match--;
            }
          }
        }
        if (!match && dfa_state_count > 0) {
          exists = 1;
          break;
        }
        index++;
      }
      if (index < MAX_DFA_STATES && !exists) {
        memset(dfa_states[index], -1, MAX_STATES * sizeof(int));
        memcpy(dfa_states[index], dfa_state, dfa_state_count * sizeof(int));
        enqueue(dfa_state);
      }
      int new_dfa_state_index = index;

      int dequeued_dfa_state_length = 0;
      while (dequeued_dfa_state_length < MAX_STATES &&
             dequeued_dfa_state[dequeued_dfa_state_length] != -1) {
        dequeued_dfa_state_length++;
      }

      index = 0;
      exists = 0;
      while (index < MAX_DFA_STATES && dfa_states[index][0] != -1) {
        int match = dequeued_dfa_state_length;
        for (int j = 0; j < MAX_STATES; j++) {
          if (dfa_states[index][j] == -1)
            break;
          for (int k = 0; k < MAX_STATES; k++) {
            if (dequeued_dfa_state[k] == -1)
              break;
            if (dfa_states[index][j] == dequeued_dfa_state[k]) {
              match--;
            }
          }
        }
        if (!match && dequeued_dfa_state_length > 0) {
          exists = 1;
          break;
        }
        index++;
      }
      if (index < MAX_DFA_STATES && exists) {
        add_dfa_transition(index, input_symbols[i], new_dfa_state_index);
      }
    }
  }

  fprintf(stdout, "\nDFA\n");
  display_dfa_transitions();
}

void display_transitions() {
  for (int i = 0; i < state_count; i++) {
    for (int j = 0; j < input_symbol_count; j++) {
      for (int k = 0; k < state_count; k++) {
        if (transitions[i][j][k] < 0)
          break;
        fprintf(stdout, "%d --%c-> %d\n", i, input_symbols[j],
                transitions[i][j][k]);
      }
    }
  }
}

void display_dfa_transitions() {
  for (int i = 0; i < MAX_DFA_STATES; i++) {
    for (int j = 0; j < input_symbol_count; j++) {
      int next_state = dfa_transitions[i][j];
      if (next_state < 0)
        break;
      fprintf(stdout, "{ ");
      for (int k = 0; k < state_count; k++) {
        if (dfa_states[i][k] == -1)
          break;
        fprintf(stdout, "q%d ", dfa_states[i][k]);
      }
      fprintf(stdout, "}");
      fprintf(stdout, " --%c-> ", input_symbols[j]);
      fprintf(stdout, "{ ");
      for (int k = 0; k < state_count; k++) {
        if (dfa_states[next_state][k] == -1)
          break;
        fprintf(stdout, "q%d ", dfa_states[next_state][k]);
      }
      fprintf(stdout, "}\n");
    }
  }
}

int find_input_symbol(char symbol) {
  int index = 0;
  while (input_symbols[index] != symbol && index < input_symbol_count) {
    index++;
  }
  if (index == input_symbol_count)
    return -1;
  else
    return index;
}

int add_input_symbol(char symbol) {
  if (find_input_symbol(symbol) >= 0 || input_symbol_count >= MAX_INPUT_SYMBOLS)
    return -1;

  input_symbols[input_symbol_count] = symbol;
  int tmp = input_symbol_count;
  input_symbol_count++;
  return tmp;
}

int add_transition(int current_state, char symbol, int next_state) {
  int symbol_index = find_input_symbol(symbol);
  if (symbol_index < 0) {
    fprintf(stderr, "unknown symbol\n");
    exit(EXIT_FAILURE);
  }
  int index = 0;
  int exists = 0;
  while (index < MAX_STATES &&
         transitions[current_state][symbol_index][index] != -1) {
    if (transitions[current_state][symbol_index][index] == next_state) {
      exists = 1;
      break;
    }
    index++;
  }
  if (index == MAX_STATES || exists) {
    return -1;
  }
  transitions[current_state][symbol_index][index] = next_state;
  return index;
}

int add_dfa_transition(int current_state, char symbol, int next_state) {
  int symbol_index = find_input_symbol(symbol);
  if (symbol_index < 0) {
    fprintf(stderr, "unknown symbol\n");
    exit(EXIT_FAILURE);
  }
  dfa_transitions[current_state][symbol_index] = next_state;
  return 0;
}

int enqueue(int dfa_state[MAX_STATES]) {
  if (rear == front - 1)
    return -1;
  rear = (rear + 1) % QUEUE_SIZE;
  for (int i = 0; i < MAX_STATES; i++) {
    QUEUE[rear][i] = dfa_state[i];
  }
  return rear;
}

int deqeue(int dfa_state[MAX_STATES]) {
  memset(dfa_state, -1, MAX_STATES * sizeof(int));
  if (rear == front)
    return -1;
  front = (front + 1) % QUEUE_SIZE;
  for (int i = 0; i < MAX_STATES; i++) {
    dfa_state[i] = QUEUE[front][i];
  }
  return front;
}
