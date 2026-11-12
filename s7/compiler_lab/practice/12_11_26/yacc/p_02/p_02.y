%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token A B
%%

input: Q0 {fprintf(stdout, "Accepted\n"); return 0;};

Q0: A Q1
  | B Q0;

Q1: A Q1
  | B Q2;

Q2: A Q1
  | B Q3;

Q3: /* empty*/
  | A Q1
  | B Q0;

%%

int main() {
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg) {
  fprintf(stderr, "Rejected: %s\n", msg);
  return;
}
