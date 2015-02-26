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
%token <number> NUMBER 
%token INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ ANDEQ OREQ XOREQ
%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <number.yyint> logical assignment
%type <number.yyint> val exp

%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation        */

%start translation_unit

%%

translation_unit:
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



logical
	: exp '|' exp {$$ = $1 | $3; }
	| exp '&' exp {$$ = $1 & $3; }
	| exp '^' exp {$$ = $1 ^ $3; }
	| exp LOGOR exp {$$ = $1 || $3; }
	| exp LOGAND exp {$$ = $1 && $3; }
	| exp '?' exp ':' exp {$$ = $1 ? $3 : $5; }

assignment
	: val '=' exp {$$ = $3; printf("exprval=%lld\n", $$); }
	| val TIMESEQ exp {$$ = $1->value * $3; $1->value = $$; }
	| val DIVEQ exp {$$ = $1->value / $3; $1->value = $$; }
	| val PLUSEQ exp {$$ = $1-> value + $3; $1->value = $$; }
	| val MINUSEQ exp {$$ = $1-> value - $3; $1->value = $$; }
	| val SHLEQ exp {$$ = $1-> value << $3; $1->value = $$; }
	| val SHREQ exp {$$ = $1-> value >> $3; $1->value = $$; }
	| val ANDEQ exp {$$ = $1-> value & $3; $1->value = $$; }
	| val OREQ exp {$$ = $1-> value | $3; $1->value = $$; }
	| val XOREQ exp {$$ = $1-> value ^ $3; $1->value = $$; }
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
        | '-' exp		 { $$ = -$2;        }
        | exp '^' exp        { $$ = pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }
;

%%

void insert_symbol(char *s){

	struct symbol *st = sym_new(filename, lineno);
	if(symTable_push(curr, s, st) != FALSE){
		st = symTable_getSymbol(curr,s);
		fprintf(stderr, "Error: %s previously defined in %s:%d\n", s, st->filename, st->linenumber);
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

