%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token A B C
%%

input: X Y {fprintf(stdout, "Accepted\n");return 0;};

X: A X B
 | A B;

Y: B Y C
 | B C;
%%

int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg){
  fprintf(stderr, "Rejected: %s\n", msg);
}
