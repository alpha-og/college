#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 32
#define MAX_PRODUCTIONS 16
#define MAX_PRODUCTION_LENGTH 16
#define MAX_SYMBOLS 16

int add_item(char item, char *set, int max_size);
int first(char *set, char symbol);
int follow(char *set, char symbol);
void display_set(char *set, const char *msg);

int productions_count;
char productions[MAX_PRODUCTIONS][MAX_PRODUCTION_LENGTH];
char start_symbol;

int main(int argc, char *argv[]) {
  FILE *p_file = fopen("input.txt", "r");

  // initialize productions array
  productions_count = 0;
  for (int production_idx = 0; production_idx < MAX_PRODUCTIONS;
       production_idx++) {
    memset(productions[production_idx], '\0', MAX_PRODUCTION_LENGTH);
  }

  // declare first set
  char first_set[MAX_SYMBOLS];

  // declare follow set
  char follow_set[MAX_SYMBOLS];

  char symbols[MAX_SYMBOLS];
  memset(symbols, '\0', MAX_SYMBOLS);

  // read start symbol
  if (argc < 2) {
    fprintf(stderr, "insufficient arguments: start state must be provided\n");
    exit(EXIT_FAILURE);
  }
  start_symbol = argv[1][0];

  // read productions
  int production_idx = 0;
  while ((production_idx < MAX_PRODUCTIONS) &&
         (fgets(productions[production_idx], MAX_PRODUCTION_LENGTH, p_file) !=
          NULL)) {
    productions[production_idx][strcspn(productions[production_idx], "\n")] =
        '\0';
    int idx = 0;
    while (idx < strlen(productions[production_idx])) {
      if (idx == 1 || idx == 2) {
        idx++;
        continue;
      }
      if (productions[production_idx][idx] == 'e') {
        idx++;
        continue;
      }
      add_item(productions[production_idx][idx], symbols, MAX_SYMBOLS);
      idx++;
    }
    production_idx++;
  }
  productions_count = production_idx;

  char message[32];
  for (int symbol_idx = 0; symbol_idx < strlen(symbols); symbol_idx++) {

    char symbol = symbols[symbol_idx];

    memset(first_set, '\0', MAX_SYMBOLS);
    memset(message, 0, 32);
    snprintf(message, 32, "First Set of %c", symbol);
    first(first_set, symbols[symbol_idx]);
    display_set(first_set, message);

    memset(follow_set, '\0', MAX_SYMBOLS);
    memset(message, 0, 32);
    snprintf(message, 32, "Follow Set of %c", symbol);
    follow(follow_set, symbols[symbol_idx]);
    display_set(follow_set, message);

    fprintf(stdout, "\n");
  }
  return -1;
}

void display_set(char *set, const char *msg) {
  fprintf(stdout, "%s: { ", msg);
  int idx = 0;
  while (idx < MAX_SIZE && set[idx] != '\0') {
    fprintf(stdout, "%c, ", set[idx]);
    idx++;
  }
  fprintf(stdout, "}\n");
}

int add_item(char item, char *set, int max_size) {
  int idx = 0;

  while (idx < max_size && set[idx] != '\0') {
    if (set[idx] == item)
      return idx;
    idx++;
  }
  if (idx == max_size)
    return -1;

  set[idx] = item;
  return idx;
}

int first(char *set, char symbol) {
  if (!isupper(symbol))
    return add_item(symbol, set, MAX_SYMBOLS);
  int production_idx = 0;
  while (production_idx < productions_count) {
    char *production = productions[production_idx];
    if (production[0] != symbol) {
      production_idx++;
      continue;
    }
    char rhs = production[3];
    if (rhs == 'e') {
      if (add_item('e', set, MAX_SYMBOLS) < 0)
        return -1;
      production_idx++;
      continue;
    }
    if (first(set, rhs) < 0)
      return -1;
    production_idx++;
  }
  return 0;
}

int follow(char *set, char symbol) {
  if (symbol == start_symbol)
    add_item('$', set, MAX_SYMBOLS);
  int production_idx = 0;
  while (production_idx < productions_count) {
    char *production = productions[production_idx];
    int idx = 3;
    while (idx < MAX_PRODUCTION_LENGTH && production[idx] != '\0') {
      if (production[idx] != symbol) {
        idx++;
        continue;
      }
      if (idx + 1 == MAX_PRODUCTION_LENGTH || production[idx + 1] == '\0') {
        if (production[0] != symbol)
          follow(set, production[0]);
        break;
      }
      first(set, production[idx + 1]);
      idx++;
      continue;

      idx++;
    }
    production_idx++;
  }
  return 0;
}
