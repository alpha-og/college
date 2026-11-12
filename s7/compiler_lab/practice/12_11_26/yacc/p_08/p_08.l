%{
  #include "y.tab.h"
  int yywrap();
%}

digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit}|_)*
%%
"for" {return FOR;}
"int"|"char"|"double"|"float"|"short"|"long"|"unsigned" {return TYPE;}
{identifier} {return ID;}
{digit}+ {return NUM;}
"++" {return INC;}
"--" {return DEC;}
"=" {return ASSIGN;}
">="|"!="|"=="|"<="|">"|"<" {return RELOP;}
"*" {return ASTERISK;}
"/" {return SLASH;}
"+" {return PLUS;}
"-" {return MINUS;}
";" {return SEMI;}
"," {return COMMA;}
"[" {return LBRACKET;}
"]" {return RBRACKET;}
"(" {return LPAREN;}
")" {return RPAREN;}
"{" {return LBRACE;}
"}" {return RBRACE;}
[ \t\r]+ {};
\n {return '\n';}
. {return yytext[0];};
%%
int yywrap(){
  return 1;
}
