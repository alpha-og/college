#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 10
#define MAX_TERMS 10
#define MAX_VARIABLES 10

// struct Variable {
//   int exponent;
//   char variable;
// };

struct Term {
  int coefficient;
  int exponent;
  // struct Variable *variables;
};

struct Polynomial {
  int degree;
  int term_count;
  int variable_count;
  struct Term *terms;
};

int main() {
  int polynomial_count = 0;
  printf("How many polynomials would you like to provide? ");
  scanf("%d", &polynomial_count);
  // allocate required memory for as many polynomials as the user wants
  struct Polynomial *polynomials =
      (struct Polynomial *)malloc(sizeof(struct Polynomial));
  if (polynomials == NULL) {
    fprintf(stderr, "Error: Memory allocation failed!");
    return 1;
  }

  struct Term *terms = (struct Term *)malloc(sizeof(struct Term) * MAX_TERMS);
  if (terms == NULL) {
    fprintf(stderr, "Error: Memory allocation failed!");
  }
  struct Polynomial Result = {.degree = MAX_DEGREE,
                              .term_count = MAX_TERMS,
                              .variable_count = MAX_VARIABLES,
                              .terms = terms};
  for (int i = 0; i < MAX_TERMS; i++) {
    Result.terms[i].exponent = i;
    Result.terms[i].coefficient = 0;
  }

  for (int i = 0; i < polynomial_count; i++) {
    struct Polynomial *current_polynomial = &polynomials[i];
    printf("\nPolynomial %d\n", i + 1);
    printf("--------------\n");
    printf("Number of terms: ");
    scanf("%d", &current_polynomial->term_count);
    // printf("Number of variables: ");
    // scanf("%d", &current_polynomial->variable_count);
    printf("Degree of polynomial: ");
    scanf("%d", &current_polynomial->degree);
    current_polynomial->terms = (struct Term *)malloc(
        sizeof(struct Term) * current_polynomial->term_count);
    for (int j = 0; j < current_polynomial->term_count; j++) {
      struct Term *current_term = &current_polynomial->terms[j];
      printf("Exponent of Term %d: ", j + 1);
      scanf("%d", &current_term->exponent);
      printf("Coefficient of Term %d: ", j + 1);
      scanf("%d", &current_term->coefficient);
    }
  }
  for (int i = 0; i < polynomial_count; i++) {

    struct Polynomial *current_polynomial = &polynomials[i];
    for (int j = 0; j < current_polynomial->term_count; j++) {
      struct Term *current_term = &current_polynomial->terms[j];
      for (int k = 0; k < MAX_TERMS; k++) {
        if (Result.terms[k].exponent == current_term->exponent) {
          Result.terms[k].coefficient += current_term->coefficient;
        }
      }
    }
  }
  for (int i = 0; i < MAX_TERMS; i++) {
    struct Term *current_term = &Result.terms[i];
    if (current_term->coefficient == 0) {
      continue;
    }

    printf("%dx^%d", current_term->coefficient, current_term->exponent);
  }
}
