%{
  #include "y.tab.h"
  #include <string.h>

  int yywrap();
%}

digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit}|_)*
number {digit}+(\.{digit}+)?
%%

{number} {
    strncpy(yylval.text, yytext, sizeof(yylval.text)-1);
    yylval.text[sizeof(yylval.text)-1] = 0;
    return NUM;
  }
{identifier} {
    strncpy(yylval.text, yytext, sizeof(yylval.text)-1);
    yylval.text[sizeof(yylval.text)-1] = 0;
    return ID;
  }
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return ASTERISK;}
"/" {return SLASH;}
"(" {return LPAREN;}
")" {return RPAREN;}
[ \t\r]+ {};
\n {return '\n';}
. {return yytext[0];}
%% 

int yywrap(){
  return 1;
}
