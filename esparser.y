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

input:    /* empty string */
        | input line
;

line:     '\n'
        | exp '\n'  { printf ("\t%.10g\n", $1); }
;

exp:      NUM                { $$ = $1;         }
        | exp '+' exp        { $$ = $1 + $3;    }
        | exp '-' exp        { $$ = $1 - $3;    }
        | exp '*' exp        { $$ = $1 * $3;    }
        | exp '/' exp        { $$ = $1 / $3;    }
        | '-' exp  %prec NEG { $$ = -$2;        }
        | exp '^' exp        { $$ = pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }
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
