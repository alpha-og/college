#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTION_LENGTH 8
#define MAX_PRODUCTIONS 16
#define MAX_SYMBOLS 8
#define END_MARKER '$'
#define EPSILON 'e'
#define START_SYMBOL 'E'

int add(char *set, char symbol);
void display_set(char *set, const char *msg);
void first(char *set, char symbol);
void follow(char *set, char symbol);

char symbols[MAX_SYMBOLS] = {0};
char productions[MAX_PRODUCTIONS][MAX_PRODUCTION_LENGTH];
int production_count = 0;
int symbol_count = 0;

int main() {
  FILE *p_file = fopen("p_01_productions.txt", "r");
  for (int idx = 0; idx < MAX_PRODUCTIONS; idx++) {
    memset(productions[idx], 0, MAX_PRODUCTION_LENGTH);
  }

  char input_buffer[MAX_PRODUCTION_LENGTH] = {0};
  while (fgets(input_buffer, MAX_PRODUCTION_LENGTH, p_file) != NULL) {
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    add(symbols, input_buffer[0]);
    for (int idx = 3; idx < strlen(input_buffer); idx++) {
      add(symbols, input_buffer[idx]);
    }
    strcpy(productions[production_count], input_buffer);
    production_count++;
  }
  symbol_count = strlen(symbols);

  char msg[16] = {0};
  char first_set[MAX_SYMBOLS] = {0};
  char follow_set[MAX_SYMBOLS] = {0};
  for (int idx = 0; idx < MAX_SYMBOLS; idx++) {
    char symbol = symbols[idx];
    memset(first_set, 0, MAX_SYMBOLS);
    snprintf(msg, 16, "First set of %c", symbol);
    first(first_set, symbols[idx]);
    display_set(first_set, msg);

    memset(follow_set, 0, MAX_SYMBOLS);
    snprintf(msg, 16, "Follow set of %c", symbol);
    follow(follow_set, symbols[idx]);
    display_set(follow_set, msg);
    fprintf(stdout, "\n");
  }
  return 0;
}
int add(char *set, char symbol) {
  int idx = 0;
  while (idx < MAX_SYMBOLS && set[idx] != 0) {
    if (set[idx] == symbol)
      return idx;
    idx++;
  }
  if (idx == MAX_SYMBOLS)
    return -1;
  set[idx] = symbol;
  return idx;
}

void display_set(char *set, const char *msg) {
  fprintf(stdout, "%s: { ", msg);
  for (int idx = 0; idx < MAX_SYMBOLS; idx++) {
    if (set[idx] == 0)
      break;
    fprintf(stdout, "%c, ", set[idx]);
  }
  fprintf(stdout, "}\n");
}

void first(char *set, char symbol) {
  if (!isupper(symbol)) {
    add(set, symbol);
    return;
  }

  int idx = 0;
  while (idx < production_count) {
    char *production = productions[idx];
    if (production[0] == symbol) {
      if (production[3] == EPSILON) {
        add(set, EPSILON);
      } else {
        if (production[3] != symbol)
          first(set, production[3]);
      }
    }
    idx++;
  }
  return;
}

void follow(char *set, char symbol) {
  if (symbol == START_SYMBOL)
    add(set, END_MARKER);
  for (int idx = 0; idx < production_count; idx++) {
    char *production = productions[idx];
    for (int inner_idx = 0; inner_idx < MAX_PRODUCTION_LENGTH; inner_idx++) {
      char ch = production[inner_idx];
      if (ch == 0)
        break;
      if (ch == symbol) {
        char next_ch = production[inner_idx + 1];
        if (next_ch == 0) {
          if (production[0] != symbol)
            follow(set, production[0]);
        } else {
          first(set, next_ch);
        }
      }
    }
  }
}
