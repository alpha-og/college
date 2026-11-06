#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_INPUT_SYMBOLS 5

int epsilon_closure(int state, int states[MAX_STATES]);
int find_input_symbol(char symbol);
int add_input_symbol(char symbol);
int add_transition(int current_state, char symbol, int next_state);
void display_transitions();

int state_count = 0;
int input_symbol_count = 0;
int transitions[MAX_STATES][MAX_INPUT_SYMBOLS][MAX_STATES] = {};
int epsilon_closures[MAX_STATES][MAX_STATES] = {};
char input_symbols[MAX_INPUT_SYMBOLS] = {};

int main() {
  FILE *p_file = fopen("input.txt", "r");
  int current_state = 0;
  int next_state = 0;
  char transition_symbol = '\0';

  for (int i = 0; i < MAX_STATES; i++) {
    for (int j = 0; j < MAX_STATES; j++) {
      epsilon_closures[i][j] = -1;
    }
  }

  for (int i = 0; i < MAX_STATES; i++) {
    for (int j = 0; j < MAX_INPUT_SYMBOLS; j++) {
      for (int k = 0; k < MAX_STATES; k++) {
        transitions[i][j][k] = -1;
      }
    }
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

  fprintf(stdout, "\ne-NFA\n");
  display_transitions();

  fprintf(stdout, "\nEpsilon Closures\n");
  for (int i = 0; i < state_count; i++) {
    if (epsilon_closure(i, epsilon_closures[i]) < 0)
      continue;
    fprintf(stdout, "q%d: { ", i);
    for (int j = 0; j < state_count && epsilon_closures[i][j] > -1; j++) {
      fprintf(stdout, "q%d ", epsilon_closures[i][j]);
    }
    fprintf(stdout, "}\n");
  }

  for (int i = 0; i < state_count; i++) {
    for (int j = 0; j < state_count; j++) {
      int epsilon_index = find_input_symbol('e');
      if (epsilon_index < 0) {
        fprintf(stderr, "given NFA does not have epsilon transitions");
        exit(EXIT_FAILURE);
      }

      int state = epsilon_closures[i][j];
      if (state < 0)
        break;
      for (int k = 0; k < input_symbol_count; k++) {
        if (k == epsilon_index)
          continue;
        for (int l = 0; l < state_count; l++) {
          int next_state = transitions[state][k][l];
          if (next_state < 0)
            break;
          add_transition(i, input_symbols[k], next_state);
        }
      }
      memset(transitions[i][epsilon_index], -1, MAX_STATES * sizeof(int));
    }
  }

  fprintf(stdout, "\nNFA\n");
  display_transitions();
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

int epsilon_closure(int state, int states[MAX_STATES]) {
  int epsilon_index = find_input_symbol('e');
  if (epsilon_index < 0) {
    fprintf(stderr, "given NFA does not have epsilon transitions");
    return -1;
  }
  int index = 0;
  int exists = 0;
  while (index < state_count && states[index] != -1) {
    if (states[index] == state) {
      exists = 1;
      break;
    }
    index++;
  }
  if (exists)
    return 0;
  states[index] = state;

  for (int i = 0; i < state_count; i++) {
    int next_state = transitions[state][epsilon_index][i];
    if (next_state < 0)
      break;
    epsilon_closure(next_state, states);
  }
  return 0;
}
