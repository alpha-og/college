%{
#include "y.tab.h"
int yywrap();
%}
%%
"a" {return A;};
"b" {return B;};
[ \t\r\n]+ {};
. {return yytext[0];};
%%

int yywrap() {
  return 1;
}
