%{
#include <stdio.h>
#include <string.h>

int yylex();
void yyerror(const char *);
%}

%token A B
%%
input: S {fprintf(stdout, "Accepted\n");return 0;};
S: A B;
 | A S B;
%%

int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg){
  fprintf(stderr, "Rejected %s\n",msg);
}
