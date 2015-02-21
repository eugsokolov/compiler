%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: parser.y

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "sym_table.h"

int debug = 0;

extern int yylex();
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
void yyerror (char const*);

struct sym_table *curr_scope;

%}

%token NUM
%left '-' '+'
%left '*' '/'
%left NEG     /* negation--unary minus */
%right '^'    /* exponentiation        */


%%

input:    /* empty string */
        | input line
;

line:     '\n'
        | exp '\n'  { printf ("\t%.10g\n", $1); }
	| error '\n' {yyerrok;}
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
	fprintf(stderr, "Error: unrecognized syntax:: %s\n", s);
}

main(){

	char *in;
	int c;

	
	
 
	yyparse();
	printf("EOF\n");
}
