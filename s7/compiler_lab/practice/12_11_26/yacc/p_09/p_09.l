%{
  #include "y.tab.h"

  int yywrap();
%}

digit [0-9]
number {digit}+(\.{digit}+)?
%%

{number} {
    yylval.val = strtod(yytext,NULL);
    return NUM;
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
