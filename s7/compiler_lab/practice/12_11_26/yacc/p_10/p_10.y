%{
#include <stdio.h>
#include <string.h>

int yylex();
void yyerror(const char * msg);
%}
%union {
 char text[32];
}
%token PLUS MINUS ASTERISK SLASH LPAREN RPAREN
%token <text> NUM ID
%type <text> expr
%left PLUS MINUS
%left ASTERISK SLASH
%right UMINUS
%%

input: | input expr '\n' {fprintf(stdout, "Result: %s", $2);}; 

expr: NUM {strncpy($$, $1, sizeof($$));}
    | ID {strncpy($$, $1, sizeof($$));}
    | expr PLUS expr {snprintf($$, sizeof($$),"%s %s %c", $1, $3, '+');}
    | expr MINUS expr {snprintf($$, sizeof($$),"%s %s %c", $1, $3, '-');}
    | expr ASTERISK expr {snprintf($$, sizeof($$),"%s %s %c", $1, $3, '*');}
    | expr SLASH expr {snprintf($$, sizeof($$),"%s %s %c", $1, $3, '/');}
    | MINUS expr %prec UMINUS {snprintf($$, sizeof($$),"%s %c", $2, '-');}
%%

int main(){
  fprintf(stdout, "Input expression: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg){
  fprintf(stderr, "Rejected: %s\n",msg);
  return;
}
