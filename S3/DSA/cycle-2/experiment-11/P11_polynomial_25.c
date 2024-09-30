/*
  Experiment 11
  Polynomial addition and multiplication using linked list
  25 Athul Anoop
  23-09-24
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
  int coefficient;
  int exponent;
  struct Term *next;
} Term;

typedef struct Polynomial {
  Term *head;
  int termCount;
} Polynomial;

// function declarations
Polynomial *addPolynomials(Polynomial **p);
Polynomial *multiplyPolynomials(Polynomial *p1, Polynomial *p2);
Polynomial *createPolynomial();
Polynomial *choosePolynomial();
Term *createTerm(int coefficient, int exponent);
Term *getTerm(Term *head, int exponent);
void displayPolynomial(Polynomial *p);
void displayMenu();
void handleChoice(Polynomial **p);

int main() {
  Polynomial **polynomials = calloc(1, sizeof(Polynomial *));
  while (1) {
    displayMenu();
    handleChoice(polynomials);
  }
}

// function definitions

Term *getTermByExponent(Term *head, int exponent) {
  Term *result = head->next;
  while (result != NULL) {
    if (result->exponent == exponent) {
      break;
    }
    result = result->next;
  }
  return result;
}

Term *getLastTerm(Term *head) {
  Term *result = head;
  while (result->next != NULL) {
    result = result->next;
  }
  return result;
}

Term *createTerm(int coefficient, int exponent) {
  Term *t = calloc(1, sizeof(Term));
  t->coefficient = coefficient;
  t->exponent = exponent;
  t->next = NULL;
  return t;
}

Polynomial *createPolynomial() {
  Polynomial *p = calloc(1, sizeof(Polynomial));
  Term *head = calloc(1, sizeof(Term));
  p->head = head;
  printf("Enter the number of terms for the polynomial: ");
  scanf("%d", &p->termCount);
  for (int i = 0; i < p->termCount; i++) {
    printf("Term %d (nx^m): ", i + 1);
    int coefficient;
    scanf("%d", &coefficient);
    getchar();
    int exponent;
    getchar();
    scanf("%d", &exponent);
    Term *t = createTerm(coefficient, exponent);
    Term *tmp = getTermByExponent(p->head, exponent);
    if (tmp == NULL) {
      tmp = getLastTerm(p->head);
      tmp->next = t;
    } else {
      *tmp = *t;
    }
  }
  return p;
}

Polynomial *addPolynomials(Polynomial **p) {
  if (p[0] == NULL || p[1] == NULL || p[0]->head == NULL ||
      p[1]->head == NULL) {
    printf("Test ok\n");
    return NULL;
  }
  Polynomial *result = calloc(1, sizeof(Polynomial));
  Term *head = calloc(1, sizeof(Term));
  result->head = head;
  int i = 0;
  for (i = 0; i < 2; i++) {
    Term *t = p[i]->head->next;
    while (t != NULL) {
      Term *tmp = getTermByExponent(result->head, t->exponent);
      if (tmp == NULL) {
        tmp = getLastTerm(result->head);
        tmp->next = createTerm(t->coefficient, t->exponent);
      } else {
        tmp->coefficient += t->coefficient;
      }
      t = t->next;
    }
  }
  return result;
}

Polynomial *multiplyPolynomials(Polynomial *p1, Polynomial *p2) {
  if (p1 == NULL || p2 == NULL || p1->head == NULL || p2->head == NULL) {
    printf("Test ok\n");
    return NULL;
  }
  Polynomial *result = calloc(1, sizeof(Polynomial));
  Term *head = calloc(1, sizeof(Term));
  result->head = head;
  Term *current = p1->head->next;
  while (current != NULL) {
    Term *current2 = p2->head->next;
    while (current2 != NULL) {
      Term *resultTmp = createTerm(current->coefficient * current2->coefficient,
                                   current->exponent + current2->exponent);

      Term *tmp = getTermByExponent(result->head, resultTmp->exponent);
      if (tmp == NULL) {
        tmp = getLastTerm(result->head);
        tmp->next = resultTmp;
      } else {
        tmp->coefficient += resultTmp->coefficient;
      }
      current2 = current2->next;
    }
    current = current->next;
  }
  return result;
}

void displayPolynomial(Polynomial *p) {
  if (p == NULL) {
    printf("Polynomial is empty\n");
    return;
  }
  Term *t = p->head->next;
  while (t->next != NULL) {
    printf("%dx^%d + ", t->coefficient, t->exponent);
    t = t->next;
  }
  printf("%dx^%d", t->coefficient, t->exponent);
}

void displayMenu() {
  printf("\n---- Menu ----\n");
  printf("1. Create a polynomial\n");
  printf("2. Add two polynomials\n");
  printf("3. Multiply two polynomials\n");
  printf("4. Display the polynomial\n");
  printf("5. Exit\n");
  printf("Choice: ");
}

int choosePolynomialIndex() {
  int choice;
  printf("Enter the index of the polynomial to be chosen: ");
  scanf("%d", &choice);
  getchar();
  switch (choice) {
  case 0:
    return choice;
  case 1:
    return choice;
  default:
    printf("Invalid choice\n");
    return -1;
  }
}

void handleChoice(Polynomial **polynomials) {
  int choice;
  scanf("%d", &choice);
  Polynomial *p = NULL;
  int index = -1;
  switch (choice) {
  case 1:
    index = choosePolynomialIndex();
    if (index < 0) {
      break;
    }
    p = createPolynomial();
    free(polynomials[index]);
    polynomials[index] = p;
    displayPolynomial(p);
    break;
  case 2:
    p = addPolynomials(polynomials);
    if (p == NULL) {
      printf("Polynomials cannot be added\n");
    } else {
      printf("Result: ");
      displayPolynomial(p);
    }
    break;
  case 3:
    p = multiplyPolynomials(polynomials[0], polynomials[1]);
    if (p == NULL) {
      printf("Polynomials cannot be multiplied\n");
    } else {
      displayPolynomial(p);
    }
    break;
  case 4:
    index = choosePolynomialIndex();
    if (index < 0) {
      break;
    }
    p = polynomials[index];
    displayPolynomial(p);
    break;
  case 5:
    exit(0);
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}
