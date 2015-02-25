%error-verbose
%{
/*
http://www.csc.villanova.edu/~tway/courses/csc4181/s2012/handouts/Tiny%20Symbol%20Table%20Info.pdf
http://research.microsoft.com/en-us/um/people/rgal/ar_language/external/compiler.pdf
http://www.mactech.com/articles/mactech/Vol.16/16.07/UsingFlexandBison/index.html
*/

//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: parser.y

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "esparser.tab.h"
#include "hash.h"
#include "sym_table.h"

int debug = 0;

extern int yylex();
extern int yyparse();
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
void yyerror (const char *s);

struct sym_table *curr;

%}

%union{

	char yychar;
        char *yystring;

        struct number{
                enum number_type num_type;
                enum number_type num_sign;
                unsigned long long int yyint;
                long double yydouble;
        }number;
}


%token <yychar> CHARLIT
%token <yystring> IDENT STRING
%token <number.yyint> NUMBER 
%token TIMESEQ DIVEQ MODEQ SHLEQ SHREQ ANDEQ OREQ XOREQ PLUSEQ MINUSEQ
%token INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR
%token AUTO BREAK CASE CHAR CONST ELLIPSIS CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY




%left '-' '+'
%left '*' '/'
%left NEG     /* negation--unary minus */
%right '^'    /* exponentiation        */

%type <number.yyint> exp

%start translation_unit

%%

translation_unit
	: top_level_declartaion
	| translation_unit top_level_declaration
	;

top_level_declaration
	: declaration
	| function_def
	;

function_def
	: function_def_specifier compound_statement	
	;



compound_statement: '{' statement_list '}' {


	}
	;

statement_list
	: statement
	| statement_list statement
	;

statement
	: declaration
	| 

declaration
	: INT identifier_list ';'
	;

identifier_list
	: IDENT {insert_symbol($1); }
	| identifier_list ',' IDENT {insert_symbol($3); }
	;












val
	: IDENT	{
		struct symbol *s = curr->symTable_getSymbol(curr, $1);
		if(s != FALSE)
			$$=s;
		else{
			$$=0;
			fprintf(stderr, "Error: undefinied identifier %s", $1);
		}
	}
	;


line: '\n'
	| exp '\n' { printf("\tResult: %i\n", $1); }
;

exp:      NUMBER                { $$ = $1;         }
        | exp '+' exp        { $$ = $1 + $3;  }
        | exp '-' exp        { $$ = $1 - $3;    }
        | exp '*' exp        { $$ = $1 * $3;    }
        | exp '/' exp        { $$ = $1 / $3;    }
        | '-' exp  %prec NEG { $$ = -$2;        }
        | exp '^' exp        { $$ = pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }
;

%%

void insert_symbol(char *s){

	struct *st = symTable_new(SCOPE , lineno, filename, curr);
	if(curr->symTable_push(curr, s, st) != FALSE){
		st = curr->symTable_getSymbol(curr,s);
		fprintf(stderr, "Error: %s previously defined in %s:%d\n", s, st->filename, st->lineno);
	}
}

void yyerror(const char *s){
	fprintf(stderr, "Parse Error: unrecognized syntax:: %s\n", s);
}

main(){

	printf("parsing..\n");

//	yyin = stdin;	
	
 
	yyparse();
	printf("EOF\n");
}

