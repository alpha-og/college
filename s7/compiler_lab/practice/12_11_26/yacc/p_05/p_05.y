%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token A B CENTRE
%%
input: S '\n'{fprintf(stdout, "Accepted\n");return 0;};

S: A S A
 | B S B
 | CENTRE

%%
int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg){
  fprintf(stderr, "Rejected: %s\n", msg);
  return;
}
