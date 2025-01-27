#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
  int coeff;
  int exp;
} Term;

typedef struct Polynomial {
  int term_count;
  Term **terms;
} Polynomial;

Polynomial *create_polynomial(int);
Term *create_term(int, int);
Polynomial *read_polynomial();
Polynomial *add_polynomials(Polynomial *, Polynomial *);
Polynomial *multiply_polynomials(Polynomial *, Polynomial *);
void display_polynomial(Polynomial *, const char *);
Term *get_term_by_exp(Polynomial *, int);

int main() {
  printf("\n---- Polynomial 1 ----\n");
  Polynomial *p1 = read_polynomial();
  display_polynomial(p1, "Polynomial 1: ");
  printf("\n---- Polynomial 2 ----\n");
  Polynomial *p2 = read_polynomial();
  display_polynomial(p2, "Polynomial 2: ");
  printf("\n");
  Polynomial *sum = add_polynomials(p1, p2);
  display_polynomial(sum, "Sum: ");
  Polynomial *product = multiply_polynomials(p1, p2);
  display_polynomial(product, "product: ");
}

Polynomial *create_polynomial(int term_count) {
  Polynomial *p = calloc(1, sizeof(Polynomial));
  p->term_count = term_count;
  p->terms = calloc(term_count, sizeof(Term *));
  return p;
}

Term *create_term(int coeff, int exp) {
  Term *t = calloc(1, sizeof(Term));
  t->exp = exp;
  t->coeff = coeff;
  return t;
}

Polynomial *read_polynomial() {
  printf("Number of terms: ");
  int N = 0;
  scanf("%d", &N);
  Polynomial *p = create_polynomial(N);
  int unique_terms = 0;
  for (int i = 0; i < N; i++) {
    printf("Term %d (coefficient exponent): ", i + 1);
    int coeff = 0;
    int exp = 0;
    scanf("%d %d", &coeff, &exp);
    Term *t = get_term_by_exp(p, exp);
    if (t == NULL)
      p->terms[unique_terms++] = create_term(coeff, exp);
    else
      t->coeff += coeff;
  }
  p->term_count = unique_terms;
  return p;
}

Term *get_term_by_exp(Polynomial *p, int exp) {
  Term *result = NULL;
  for (int i = 0; i < p->term_count; i++) {
    Term *t = p->terms[i];
    if (t == NULL)
      break;
    else if (t->exp == exp) {
      result = t;
      break;
    }
  }
  return result;
}

Polynomial *add_polynomials(Polynomial *p1, Polynomial *p2) {
  Polynomial *result = create_polynomial(p1->term_count + p2->term_count);
  int unique_terms = 0;
  for (int i = 0; i < p1->term_count; i++) {
    Term *current = p1->terms[i];
    Term *t = get_term_by_exp(result, current->exp);
    if (t == NULL)
      result->terms[unique_terms++] = create_term(current->coeff, current->exp);
    else
      t->coeff += current->coeff;
  }

  for (int i = 0; i < p2->term_count; i++) {
    Term *current = p2->terms[i];
    Term *t = get_term_by_exp(result, current->exp);
    if (t == NULL)
      result->terms[unique_terms++] = create_term(current->coeff, current->exp);
    else
      t->coeff += current->coeff;
  }
  result->term_count = unique_terms;
  return result;
}

Polynomial *multiply_polynomials(Polynomial *p1, Polynomial *p2) {
  Polynomial *result = create_polynomial(p1->term_count + p2->term_count);
  int unique_terms = 0;
  for (int i = 0; i < p1->term_count; i++) {
    Term *t1 = p1->terms[i];
    for (int j = 0; j < p2->term_count; j++) {
      Term *t2 = p2->terms[j];
      Term *product_term =
          create_term(t1->coeff * t2->coeff, t1->exp + t2->exp);
      Term *t = get_term_by_exp(result, product_term->exp);
      if (t == NULL)
        result->terms[unique_terms++] =
            create_term(product_term->coeff, product_term->exp);
      else
        t->coeff += product_term->coeff;
    }
  }
  return result;
}

void display_polynomial(Polynomial *p, const char *label) {
  printf("%s", label);
  for (int i = 0; i < p->term_count; i++) {
    Term *t = p->terms[i];
    if (t == NULL)
      break;
    printf("%dx^%d", t->coeff, t->exp);
    if (i < p->term_count - 1)
      printf("+");
  }
  printf("\n");
}
