%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: parser.y

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int yylex (void);
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
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

void yyerror(const char *s){
  fprintf(stderr, "Error: unrecognized syntax %s\n", s);
}

main(){

  while(yyparse())
    ;
  
  printf("EOF\n");
}
