%{
  #include "y.tab.h"
  int yywrap();
%}

digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit}|_)*
%%

"int"|"float"|"double"|"char"|"long"|"short"|"unsigned"|"signed" {return TYPE;};
{digit}+ {return NUM;};
{identifier} {return ID;};
"*" {return STAR;};
";" {return SEMI;};
"," {return COMMA;};
"[" {return LBRACKET;};
"]" {return RBRACKET;};
"=" {return ASSIGN;};
\n {return '\n';};
[ \t\r]+ {};
. {return yytext[0];};

%%

int yywrap(){
  return 1;
}
