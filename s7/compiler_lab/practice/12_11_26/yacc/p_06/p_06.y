%{
#include <stdio.h>

int yylex();
void yyerror(const char *msg);
%}
%token A B
%%

input: X Y '\n' {fprintf(stdout, "Accepted\n");return 0;};

X: X A 
 | /*empty*/;
Y: Y B
 | /*empty*/;
%%

int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char *msg){
  fprintf(stderr, "Rejected: %s\n",msg);
}
