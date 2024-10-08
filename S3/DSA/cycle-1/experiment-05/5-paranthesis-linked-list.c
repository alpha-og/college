/*
 * Experiment - 05
 * Program to extract valid string that satisfies the condition of being present
 * within a pair of paranthesis (with nesting) Athul Anoop
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct ValidChar {
  char character;
  struct ValidChar *next;
} ValidChar;

typedef struct ValidString {
  ValidChar *content;
  struct ValidString *next;
} ValidString;

ValidChar *get_last_valid_char(ValidChar *head) {
  if (head->next == NULL)
    return head;
  else
    return get_last_valid_char(head->next);
}

ValidChar *append_valid_char(char character, ValidChar *head) {
  ValidChar *next = (ValidChar *)malloc(sizeof(ValidChar));
  next->next = NULL;
  next->character = character;
  if (head == NULL)
    head = next;
  else
    get_last_valid_char(head)->next = next;
  return head;
}

void clear_valid_char(ValidChar *head) {
  while (head->next != NULL) {
    ValidChar *tmp = head;
    while (tmp->next != NULL && tmp->next->next != NULL) {
      tmp = tmp->next;
    }
    free(tmp->next);
    tmp->next = NULL;
  }
  free(head);
}

void display_valid_string(ValidChar *head) {
  printf("%c", head->character);
  if (head->next == NULL) {
    printf("\n");
    return;
  }
  return display_valid_string(head->next);
}

ValidString *append_valid_string(ValidString *head) {
  ValidString *next = (ValidString *)malloc(sizeof(ValidString));
  next->next = NULL;
  next->content = NULL;
  if (head == NULL)
    head = next;
  else
    head->next = next;
  return head;
}

ValidString *get_last_valid_string(ValidString *head) {
  if (head->next == NULL)
    return head;
  else
    return get_last_valid_string(head->next);
}
ValidString *pop_valid_string(ValidString *head) {
  ValidString *tmp = head;
  while (tmp->next != NULL && tmp->next->next != NULL) {
    tmp = tmp->next;
  }
  free(tmp->next);
  tmp->next = NULL;
  return tmp;
}
int main() {
  printf("Provide some text: ");
  char character = '\0';
  int inside = 0;
  int is_empty = 1;
  ValidString *valid_string_head = NULL;
  while ((character = fgetc(stdin)) != '\n') {
    if (character == '(') {
      inside = 1;
      if (is_empty == 1) {
        valid_string_head = append_valid_string(NULL);
        is_empty = 0;

      } else {
        append_valid_string(get_last_valid_string(valid_string_head));
      }
      continue;
    } else if (character == ')' && inside == 1) {
      if (valid_string_head->next == NULL) {
        inside = 0;
        display_valid_string(valid_string_head->content);
        clear_valid_char(valid_string_head->content);
        free(valid_string_head);
        valid_string_head = NULL;
        is_empty = 1;
      } else {
        ValidString *tail = get_last_valid_string(valid_string_head);
        ValidChar *tail_content = tail->content;
        display_valid_string(tail_content);
        clear_valid_char(tail_content);

        pop_valid_string(valid_string_head);
        continue;
      }
    }
    if (inside == 1) {
      get_last_valid_string(valid_string_head)->content = append_valid_char(
          character, get_last_valid_string(valid_string_head)->content);
    }
  }
  return 0;
}
