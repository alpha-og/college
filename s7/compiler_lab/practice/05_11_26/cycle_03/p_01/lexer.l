%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>

int line_no = 1;
%}

identifier [a-zA-Z][a-zA-Z0-9_]*
number [0-9]+|[0-9]+\.[0-9]+
%%

"main()" {return MAIN;}
if {return IF;}
else {return ELSE;}
while {return WHILE;}
int|float|char {return TYPE;}
{identifier} {strcpy(yylval.var, yytext); return VAR;}
{number} {strcpy(yylval.var, yytext); return NUM;}
"=="|">="|"<="|">"|"<" {strcpy(yylval.var, yytext); return RELOP;}
[ \r\t]+ ;
\n {line_no++;}
. {return yytext[0];}
%%

int yywrap() {
  return 1;
}

