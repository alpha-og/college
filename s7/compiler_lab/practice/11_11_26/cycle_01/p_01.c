#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char keywords[][20] = {"main", "return", "if",      "else",  "while",
                       "char", "for",    "int",     "float", "double",
                       "void", "break",  "continue"};

void display_token(char *raw, const char *token);
int is_keyword(char *raw);

int main() {
  FILE *p_file = fopen("p_01.c", "r");

  char ch;
  char next_ch;
  while ((ch = fgetc(p_file)) != EOF) {
    if (isspace(ch))
      continue;
    if (ch == '/') {
      next_ch = fgetc(p_file);
      if (next_ch == '/') {
        while ((ch = fgetc(p_file)) != EOF) {
          if (ch == '\n')
            break;
        }
        continue;
      } else if (next_ch == '*') {
        char prev = 0;
        while ((ch = fgetc(p_file)) != EOF) {
          if (prev == '*' && ch == '/')
            break;
          prev = ch;
        }
        continue;
      } else {
        fseek(p_file, -1, SEEK_CUR);
        char buffer[] = {ch, 0};
        display_token(buffer, "OPERATOR");
        continue;
      }
    }

    if (isalpha(ch) || ch == '_') {
      char buffer[32] = {0};
      int idx = 0;
      buffer[idx++] = ch;
      while (idx < 32 && (ch = fgetc(p_file)) != EOF &&
             (isalnum(ch) || ch == '_')) {
        buffer[idx++] = ch;
      }
      buffer[idx] = 0;
      if (ch == EOF)
        fseek(p_file, -1, SEEK_CUR);

      if (is_keyword(buffer))
        display_token(buffer, "KEYWORD");
      else
        display_token(buffer, "IDENTIFIER");
      continue;
    }

    if (isdigit(ch)) {
      char buffer[32] = {0};
      int idx = 0;
      buffer[idx++] = ch;
      while (idx < 32 && (ch = fgetc(p_file)) != EOF && isdigit(ch)) {
        buffer[idx++] = ch;
      }
      buffer[idx] = 0;
      if (ch != EOF)
        fseek(p_file, -1, SEEK_CUR);
      display_token(buffer, "NUMBER");
      continue;
    }

    if (ch == '"') {
      char buffer[32] = {0};
      int idx = 0;
      buffer[idx++] = ch;
      while (idx < 32 && (ch = fgetc(p_file)) != EOF && ch != '"') {
        buffer[idx++] = ch;
      }
      buffer[idx++] = ch;
      buffer[idx++] = 0;

      display_token(buffer, "STRING");
      continue;
    }

    if (strchr("*/+-<>=!%", ch)) {
      char buffer[] = {ch, 0};
      display_token(buffer, "OPERATOR");
      continue;
    }

    if (strchr("()[];{}@#.,", ch)) {

      char buffer[] = {ch, 0};
      display_token(buffer, "SPECIAL");
      continue;
    }
  }
  return EXIT_SUCCESS;
}
void display_token(char *raw, const char *token) {
  fprintf(stdout, "%-16s %-16s\n", raw, token);
}
int is_keyword(char *raw) {
  for (int i = 0; i < 13; i++) {
    if (strcmp(raw, keywords[i]) == 0) {
      return 1;
    }
  }
  return 0;
}
