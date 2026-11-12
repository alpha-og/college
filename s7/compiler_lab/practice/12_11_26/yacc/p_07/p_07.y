%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token TYPE ID NUM ASSIGN SEMI COMMA LBRACKET RBRACKET STAR
%%

input: TYPE declarator_list SEMI '\n'{fprintf(stdout, "Accepted\n");return 0;};
  
declarator_list: declarator
               | declarator_list COMMA declarator;

declarator:
          pointer ID array initializer;

pointer: STAR
       | /* empty */;
array: LBRACKET NUM RBRACKET
     | /* empty */;
initializer: ASSIGN NUM
           | ASSIGN ID
           | /* empty */;

%%

void yyerror(const char *s) { fprintf(stderr,"Invalid variable declaration: %s\n",s); }
int main(void) { fprintf(stdout,"Enter a C variable declaration (subset): "); return yyparse(); }
