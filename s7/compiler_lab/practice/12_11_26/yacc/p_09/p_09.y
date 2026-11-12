%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}
%union {
  double val;
}
%token PLUS MINUS ASTERISK SLASH LPAREN RPAREN UMINUS
%token <val> NUM 
%type <val> expr
%left PLUS MINUS
%left ASTERISK SLASH
%right UMINUS
%%

input: | input expr '\n' {fprintf(stdout, "Result: %.2f\n", $2);}; 

expr: expr PLUS expr {$$=$1 + $3;}
    | expr MINUS expr {$$=$1 - $3;}
    | expr ASTERISK expr {$$=$1 * $3;}
    | expr SLASH expr {$$=$1 / $3;}
    | MINUS expr %prec UMINUS {$$=-$2;}
    | LPAREN expr RPAREN {$$=$2;}
    | NUM {$$=$1;};
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
