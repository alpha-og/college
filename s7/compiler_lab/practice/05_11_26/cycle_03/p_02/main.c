#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10

int epsilon_transition_matrix[MAX_STATES][MAX_STATES];
int state_count = 0;

void epsilon_closure(int state, int visited[MAX_STATES]);

int main() {
  FILE *p_file = fopen("input.txt", "r");

  for (int i = 0; i < MAX_STATES; i++) {
    for (int j = 0; j < MAX_STATES; j++) {
      epsilon_transition_matrix[i][j] = 0;
    }
  }

  int current_state, next_state = -1;
  char transition_symbol[2];
  while (fscanf(p_file, "%d %s %d", &current_state, transition_symbol,
                &next_state) != EOF) {
    if (strcmp("e", transition_symbol) == 0)
      epsilon_transition_matrix[current_state][next_state] = 1;
    state_count = state_count < current_state ? current_state
                  : state_count < next_state  ? next_state
                                              : state_count;
  }
  state_count++;

  for (int i = 0; i < state_count; i++) {
    int visited[MAX_STATES] = {0};
    fprintf(stdout, "q%d: { ", i);
    epsilon_closure(i, visited);

    for (int i = 0; i < MAX_STATES; i++) {
      if (visited[i])
        fprintf(stdout, "q%d ", i);
    }
    fprintf(stdout, "}\n");
  }
  return 0;
}

void epsilon_closure(int state, int visited[MAX_STATES]) {
  if (visited[state])
    return;
  visited[state] = 1;
  for (int i = 0; i < state_count; i++) {
    if (epsilon_transition_matrix[state][i]) {
      epsilon_closure(i, visited);
    }
  }
}
