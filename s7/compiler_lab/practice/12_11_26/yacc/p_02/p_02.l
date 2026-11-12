%{
#include "y.tab.h"
int yywrap();
%}

%%
"a" {return A;};
"b" {return B;};
\n {return '\n';};
[ \t\r]+ {};
. {return yytext[0];};
%%

int yywrap(){
  return 1;
}
