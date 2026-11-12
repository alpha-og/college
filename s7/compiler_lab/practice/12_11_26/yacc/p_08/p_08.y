%{
#include <stdio.h>

int yylex();
void yyerror(const char * msg);
%}

%token TYPE ID NUM FOR RELOP ASSIGN ASTERISK SEMI COMMA LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE INC DEC PLUS SLASH MINUS
%%
input: FOR LPAREN init SEMI cond SEMI update RPAREN LBRACE RBRACE '\n'{
       fprintf(stdout, "Accepted\n");
       return 0;
     };

init: TYPE declaration_list
    | /* empty */;

cond: expr
    | /* empty */;

update: expr
      | /* empty */;

declaration_list: declaration
                | declaration_list COMMA declaration;

declaration: pointer ID array assignment;

pointer: ASTERISK
       | /* empty */;


array: LBRACKET NUM RBRACKET 
       | /* empty */;

assignment: ASSIGN expr;

expr: ID assignment
    | ID INC
    | ID DEC
    | rel_expr;

rel_expr: arith_expr RELOP arith_expr
        | arith_expr;

arith_expr: arith_expr PLUS term
    | arith_expr MINUS term
    | term;

term: term ASTERISK factor
    | term SLASH factor
    | factor;

factor: ID
      | NUM
      | LPAREN expr RPAREN;

%%

int main(){
  fprintf(stdout, "Input string: ");
  yyparse();
  return 0;
}

void yyerror(const char * msg){
  fprintf(stderr, "Rejected: %s\n", msg);
}

