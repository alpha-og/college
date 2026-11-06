%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Quad {
  char op[10];
  char operand1[10];
  char operand2[10];
  char result[10];
} QUAD[30];

struct Stack {
  int items[100];
  int top;
} stack;

void add_quad(char op[5], char operand1[10], char operand2[10], char result_var[10], char result[10]);
void get_temporary_variable();
void patch();
void push(int value);
int pop();
int yyerror(const char *message);
int yylex();

extern int line_no;
int quad_index;
int temporary_var_no;
char temporary_variable[5];
int st_index;
int patch_index;

%}

%union {
  char var[10];
}

%token <var> NUM VAR TYPE RELOP
%token MAIN IF ELSE WHILE 
%type <var> EXPR ASSIGNMENT CONDITION IFST ELSEST WHILELOOP

%left '-' '+'
%left '*' '/'
%right UMIN
%%

PROGRAM: MAIN BLOCK ;

BLOCK: '{' CODE '}';

CODE: BLOCK | STATEMENT CODE | STATEMENT;

STATEMENT: DEFST | ASSIGNMENT | CONDST | WHILEST;

DEFST: TYPE VAR ';';

ASSIGNMENT: VAR '=' EXPR ';'{
            add_quad("=", $3, "", $1, $$);
          };

EXPR: EXPR '+' EXPR {
      get_temporary_variable();
      add_quad("+", $1, $3, temporary_variable, $$);
    }
    | EXPR '-' EXPR {
      get_temporary_variable();
      add_quad("-", $1, $3, temporary_variable, $$);
    } 
    | EXPR '*' EXPR {
      get_temporary_variable();
      add_quad("*", $1, $3, temporary_variable, $$);
    } 
    | EXPR '/' EXPR {
      get_temporary_variable();
      add_quad("/", $1, $3, temporary_variable, $$);
    } 
    | '-' EXPR %prec UMIN{
      get_temporary_variable();
      add_quad("UMIN", $2, "",temporary_variable , $$);
    } 
    | '(' EXPR ')' {strcpy($$,$2);} 
    | VAR {strcpy($$,$1);} 
    | NUM {strcpy($$,$1);};

CONDST: IFST {
        patch();
      }
      | IFST ELSEST;

IFST: IF '(' CONDITION ')' {
      add_quad("IF_FALSE", $3, "FALSE", NULL, NULL);
      push(quad_index-1);
    } BLOCK;

ELSEST: ELSE {
       add_quad("GOTO", "", "", NULL, NULL);
       push(quad_index-1);

       int tmp = pop();
       patch_index = pop();
       push(tmp);
       sprintf(QUAD[patch_index].result, "%d", quad_index);
     } BLOCK {
       patch();
     };

CONDITION: VAR RELOP VAR {
           get_temporary_variable();
           add_quad($2, $1, $3, temporary_variable, $$);
           st_index = quad_index-1;
         }
         | VAR
         | NUM;
      
WHILEST: WHILELOOP {
         patch();
       };

WHILELOOP: WHILE '(' CONDITION ')' {
          add_quad("IF_FALSE", $3, "FALSE", NULL, NULL);
          push(quad_index-1);
         } BLOCK {
          add_quad("GOTO", "", "", NULL, NULL);
          sprintf(QUAD[quad_index-1].result, "%d", st_index);
         };


%%

extern FILE * yyin;

int main(int argc, char *argv[]){
  quad_index = 0;
  temporary_var_no = 0;
  st_index = 0;
  patch_index = -1;
  stack.top = -1;

  yyin = fopen(argv[1], "r");
  yyparse();

  fprintf(stdout, "%-10s %-10s %-10s %-10s %-10s\n", "Position", "Operator", "Operand 1", "Operand 2", "Result");
  for (int i=0; i< quad_index; i++) {
    fprintf(stdout, "%-10d %-10s %-10s %-10s %-10s\n", i, QUAD[i].op, QUAD[i].operand1, QUAD[i].operand2, QUAD[i].result);
  }

  return 0;
}


void add_quad(char op[5], char operand1[10], char operand2[10], char result_var[10],  char result[10]){
  strcpy(QUAD[quad_index].op, op);
  strcpy(QUAD[quad_index].operand1, operand1 ? operand1 : "");
  strcpy(QUAD[quad_index].operand2, operand2 ? operand2 : "");
  strcpy(QUAD[quad_index].result, result_var? result_var: "-1");
  if (result)
    strcpy(result, QUAD[quad_index].result);
  quad_index++;
}

void get_temporary_variable(){
  sprintf(temporary_variable, "t%d", temporary_var_no++);
}

void patch(){
  patch_index = pop();
  sprintf(QUAD[patch_index].result, "%d", quad_index);
}

void push(int value){
  if (stack.top == 100) {fprintf(stderr, "stack overflow\n");exit(EXIT_FAILURE);}
  stack.top++;
  stack.items[stack.top] = value;
}

int pop(){
  if (stack.top == -1) {fprintf(stderr, "stack underflow\n"); exit(EXIT_FAILURE);}
  return stack.items[stack.top--];
}

int yyerror(const char *message){
  fprintf(stderr, "Error on line %d: %s\n", line_no, message);
  return 0;
}
