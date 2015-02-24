http://www.csc.villanova.edu/~tway/courses/csc4181/s2012/handouts/Tiny%20Symbol%20Table%20Info.pdf
http://research.microsoft.com/en-us/um/people/rgal/ar_language/external/compiler.pdf
http://www.mactech.com/articles/mactech/Vol.16/16.07/UsingFlexandBison/index.html





%{
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

        struct word{
                unsigned int yystring_size;
                char yychar;
                char *yystring;
        }word;

        struct number{
                enum number_type num_type;
                enum number_type num_sign;
                unsigned long long int yyint;
                long double yydouble;
        }number;
}


%token <word.yystring> IDENT CHARLIT STRING
%token <number.yyint> NUMBER TIMESEQ DIVEQ MODEQ SHLEQ SHREQ ANDEQ OREQ XOREQ PLUSEQ MINUSEQ
%token <number.yyint> INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR
%token <inumber.yyint> AUTO BREAK CASE CHAR CONST ELLIPSIS CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <number.yyint> declaration ident_list


%left '-' '+'
%left '*' '/'
%left NEG     /* negation--unary minus */
%right '^'    /* exponentiation        */

%type <number.yyint> exp


%start declaration

%%

declaration: 
	decltype ident_list ';'	{

	}
	;

	ident_list : IDENT	{push(curr, $1, ptr);}
	| ident_list ',' IDENT
	;



decltype
	: NUMBER {$$ = TYPE_INT; }
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

void yyerror(const char *s){
	fprintf(stderr, "Parse Error: unrecognized syntax:: %s\n", s);
}

main(){

	printf("parsing..\n");

//	yyin = stdin;	
	
 
	yyparse();
	printf("EOF\n");
}
