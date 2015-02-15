%option noyywrap
%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: bison.y

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int yylex (voic);
void yyerror (char const*);

%}

%token NUM


%%

input:
  %empty
  | input line
  ;
  
line: 
  '\n'
  | exp '\n'  {printf("%.10g\n", $1);}
  ;




%%

void yyerror(char const *s){
  fprintf(stderr, "Error: %s\n", s);
}

main(){

  while(yyparse())
    ;
  
  printf("EOF\n");
}
