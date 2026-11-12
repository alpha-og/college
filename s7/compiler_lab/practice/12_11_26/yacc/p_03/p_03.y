%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token A B C D
%%
input: A S D '\n' {fprintf(stdout,"Accepted\n"); return 0;};

S: A S D
 | B T C;

T: B T C
 | /* empty */;

%%

int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg) {
  fprintf(stderr, "Rejected: %s\n", msg);
  return;
}
