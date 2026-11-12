#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 5
#define MAX_STATES 10

struct DFA {
  int start_state;
  int symbols[MAX_SYMBOLS];
  int final_states[MAX_STATES];
  int transitions[MAX_STATES][MAX_SYMBOLS];
  int state_count;
  int final_state_count;
  int symbol_count;
} dfa, minimized_dfa;

int reachable[MAX_STATES];
int state_pairs[MAX_STATES][MAX_STATES];
int group_mapping[MAX_STATES];
int group_count;

void initialize_dfa(struct DFA *dfa);
int add_transition(int current_state, char symbol, int next_state);
int is_final_state(struct DFA *dfa, int state);
void compute_reachability(int state);
void map_states_to_group();
int find_symbol(char symbol);
int add_symbol(char symbol);
void display_dfa(struct DFA dfa, const char *msg);

int main(int argc, char *argv[]) {
  FILE *p_file = fopen("input.txt", "r");
  if (argc == 0) {
    fprintf(stderr, "there must be atleast one final state\n");
    exit(EXIT_FAILURE);
  }
  if (argc > MAX_STATES) {
    fprintf(stderr, "cannot assign more final states than %d\n", MAX_STATES);
    exit(EXIT_FAILURE);
  }

  // initialize dfa
  initialize_dfa(&dfa);

  // initialize minimized_dfa
  initialize_dfa(&minimized_dfa);

  memset(reachable, 0, sizeof(int) * MAX_STATES);
  for (int i = 0; i < MAX_STATES; i++) {
    memset(state_pairs[i], 0, sizeof(int) * MAX_STATES);
  }

  memset(group_mapping, -1, sizeof(int) * MAX_STATES);
  group_count = 0;

  // read final states from cli args
  dfa.final_state_count = argc - 1;
  for (int i = 1; i < dfa.final_state_count; i++) {
    dfa.final_states[i] = atoi(argv[i]);
  }

  // read transitions
  int current_state = 0;
  char symbol = '\0';
  int next_state = 0;

  while (fscanf(p_file, "%d %c %d", &current_state, &symbol, &next_state) !=
         EOF) {
    add_symbol(symbol);
    add_transition(current_state, symbol, next_state);
    dfa.state_count =
        dfa.state_count < current_state ? current_state : dfa.state_count;
    dfa.state_count =
        dfa.state_count < next_state ? next_state : dfa.state_count;
  }
  dfa.state_count++;

  // display the parsed DFA
  display_dfa(dfa, "DFA");

  // eliminate unreachable states
  compute_reachability(0);
  for (int current_state = 0; current_state < dfa.state_count;
       current_state++) {
    if (reachable[current_state])
      continue;
    memset(dfa.transitions[current_state], -1, sizeof(int) * MAX_SYMBOLS);
  }

  // mark non-equivalent pairs of reachable states containing exactly one final
  // state
  for (int state_a = 0; state_a < dfa.state_count; state_a++) {
    if (!reachable[state_a])
      continue;
    for (int state_b = 0; state_b < dfa.state_count; state_b++) {
      if (!reachable[state_b])
        continue;
      if ((is_final_state(&dfa, state_a) && !is_final_state(&dfa, state_b)) ||
          (!is_final_state(&dfa, state_a) && is_final_state(&dfa, state_b))) {
        state_pairs[state_a][state_b] = 1;
        state_pairs[state_b][state_a] = 1;
      }
    }
  }

  // mark non-equivalent pairs of reachable states if for an input symbol they
  // transition to the a pair of non equivalent states
  int changed = 0;
  do {
    changed = 0;
    for (int state_a = 0; state_a < dfa.state_count; state_a++) {
      if (!reachable[state_a])
        continue;
      for (int state_b = 0; state_b < dfa.state_count; state_b++) {
        if (!reachable[state_b])
          continue;
        if (state_pairs[state_a][state_b])
          continue;
        for (int symbol_idx = 0; symbol_idx < dfa.symbol_count; symbol_idx++) {
          int next_state_a = dfa.transitions[state_a][symbol_idx];
          int next_state_b = dfa.transitions[state_b][symbol_idx];
          if (!state_pairs[next_state_a][next_state_b])
            continue;
          state_pairs[state_a][state_b] = 1;
          state_pairs[state_b][state_a] = 1;
          changed = 1;
          break;
        }
      }
    }
  } while (changed);

  map_states_to_group();

  minimized_dfa.symbol_count = dfa.symbol_count;
  minimized_dfa.state_count = group_count;
  minimized_dfa.start_state = group_mapping[dfa.start_state];
  memcpy(minimized_dfa.symbols, dfa.symbols, sizeof(int) * dfa.symbol_count);
  for (int group = 0; group < group_count; group++) {
    int representative_state = -1;

    for (int state = 0; state < dfa.state_count; state++) {
      if (group_mapping[state] != group)
        continue;
      representative_state = state;
      break;
    }

    if (representative_state < 0)
      continue;

    if (is_final_state(&dfa, representative_state))
      minimized_dfa.final_states[minimized_dfa.final_state_count++] = group;

    for (int symbol_idx = 0; symbol_idx < dfa.symbol_count; symbol_idx++) {
      int orig_dest = dfa.transitions[representative_state][symbol_idx];
      minimized_dfa.transitions[group][symbol_idx] =
          orig_dest >= 0 ? group_mapping[orig_dest] : -1;
    }
  }

  display_dfa(minimized_dfa, "Minimized DFA");

  return 0;
}
void initialize_dfa(struct DFA *dfa) {
  dfa->start_state = 0;
  memset(dfa->symbols, -1, sizeof(int) * MAX_SYMBOLS);
  memset(dfa->final_states, -1, sizeof(int) * MAX_STATES);
  for (int i = 0; i < MAX_STATES; i++) {
    memset(dfa->transitions[i], -1, sizeof(int) * MAX_SYMBOLS);
  }
  dfa->state_count = 0;
  dfa->final_state_count = 0;
  dfa->symbol_count = 0;
}

void display_dfa(struct DFA dfa, const char *msg) {
  if (msg) {
    fprintf(stdout, "%s\n", msg);
  }
  for (int current_state = 0; current_state < dfa.state_count;
       current_state++) {
    for (int symbol_idx = 0; symbol_idx < dfa.symbol_count; symbol_idx++) {
      char symbol = dfa.symbols[symbol_idx];
      int next_state = dfa.transitions[current_state][symbol_idx];
      fprintf(stdout, "%d%c ", current_state,
              is_final_state(&dfa, current_state) ? '*' : ' ');
      fprintf(stdout, "--%c-> ", symbol);
      fprintf(stdout, "%d%c \n", next_state,
              is_final_state(&dfa, next_state) ? '*' : ' ');
    }
  }
}

int add_transition(int current_state, char symbol, int next_state) {
  int idx = find_symbol(symbol);
  if (idx < 0) {
    fprintf(stderr, "unknown symbol: %c", symbol);
    return -1;
  }
  dfa.transitions[current_state][idx] = next_state;
  return 0;
}

int find_symbol(char symbol) {
  int idx = 0;
  while (idx < MAX_SYMBOLS && dfa.symbols[idx] != -1) {
    if (dfa.symbols[idx] == symbol)
      return idx;
    idx++;
  }
  return -1;
}

int add_symbol(char symbol) {
  int idx = find_symbol(symbol);
  if (idx >= 0) {
    return idx;
  }
  idx = 0;
  while (idx < MAX_SYMBOLS && dfa.symbols[idx] != -1) {
    idx++;
  }
  if (idx == MAX_SYMBOLS) {
    fprintf(stderr, "insufficient storage: symbol cannot be added\n");
  }
  dfa.symbols[idx] = symbol;
  dfa.symbol_count++;
  return idx;
}

int is_final_state(struct DFA *dfa, int state) {
  for (int final_state_idx = 0; final_state_idx < dfa->final_state_count;
       final_state_idx++) {
    if (state == dfa->final_states[final_state_idx])
      return 1;
  }
  return 0;
}

void compute_reachability(int state) {
  if (reachable[state])
    return;
  reachable[state] = 1;
  for (int symbol_idx = 0; symbol_idx < dfa.symbol_count; symbol_idx++) {
    int next_state = dfa.transitions[state][symbol_idx];
    if (next_state < 0)
      continue;
    compute_reachability(next_state);
  }
}

void map_states_to_group() {
  for (int state_a = 0; state_a < dfa.state_count; state_a++) {
    if (!reachable[state_a] || group_mapping[state_a] != -1)
      continue;
    group_mapping[state_a] = group_count;
    for (int state_b = state_a + 1; state_b < dfa.state_count; state_b++) {
      if (!reachable[state_b] || group_mapping[state_b] != -1)
        continue;
      if (state_pairs[state_a][state_b])
        continue;

      group_mapping[state_b] = group_count;
    }
    group_count++;
  }
}
