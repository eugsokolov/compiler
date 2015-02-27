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
void insert_symbol(char *s);

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
%token INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ 
%token LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ 
%token SHLEQ SHREQ ANDEQ OREQ XOREQ
%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE 
%token ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG 
%token REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC 
%token STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED 
%token VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <number.yyint> primary_expr postfix_expr 
%type <number.yyint> function_call expression_list cast_expr 
%type <number.yyint> unary_expr multiplicative_expr additive_expr 
%type <number.yyint> shift_expr relational_expr equality_expr
%type <number.yyint>  bit_or_expr bit_xor_expr bit_and_expr 
%type <number.yyint> logical_or_expr logical_and_expr conditional_expr 
%type <number.yyint> assignment_expr expr

%start translation_unit

%%

translation_unit
        : top_level_declaration
        | translation_unit top_level_declaration
        ;

top_level_declaration
        : declaration
        | function_definition
        ;

function_definition
        : function_specifier compound_statement
        ;

function_specifier
        : IDENT '(' ')' {
		//no parameters currently
                insert_symbol($1);
        }
        ;

compound_statement
        : '{' '}'
        | '{' { //midaction rule
                if (curr->scope_type == FILE_SCOPE)
                        curr = symTable_new(FUNCTION_SCOPE, lineno, filename, curr);
                else
                        curr = symTable_new(BLOCK_SCOPE, lineno, filename, curr);
        } declaration_list '}' {
                curr = symTable_pop(curr);
        }
        | '{' { //midaction rule
                if (curr->scope_type == FILE_SCOPE)
                        curr = symTable_new(FUNCTION_SCOPE, lineno, filename, curr);
                else
                        curr = symTable_new(BLOCK_SCOPE, lineno, filename, curr);
        } statement_list '}' {
                curr = symTable_pop(curr);
        }
        ;

statement_list
        : statement
        | statement_list statement
        ;

statement
        : expr ';' { fprintf(stderr, "Parse statement expression value = %lld", $1); }
        | ';'
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

declaration
        : INT identifier_list ';' 
        ;






identifier_list
        : identifier_list ',' IDENT { insert_symbol($3); }
        | IDENT { insert_symbol($1); }
        ;

primary_expr
        : IDENT {
                struct symbol *s = symTable_getSymbol(curr, $1);
                if (s != NULL) $$ = s->value;
                else {
                        $$ = 0;
                        fprintf(stderr, "Undefined identifier %s", $1);
                }
        }
        | NUMBER {
                if ($1.num_type == TYPE_INT || $1.num_type == TYPE_LONG || $1.num_type == TYPE_LONGLONG)
                        $$ = $1.yyint;
                else {
                        $$ = (long long)$1.yydouble;
                        fprintf(stderr,"Truncating real number %Lg to integer %lld",$1.yydouble,$$);
                        printf("exprval=%lld",$$);
                }
        }
        | '(' expr ')' { $$ = (long long)$2; }
        ;

postfix_expr
	: primary_expr
	| postfix_expr '[' expr ']' {
                fprintf(stderr, "Arrays not implemented");
                $$ = 0;
        }
        | postfix_expr '.' IDENT {
                fprintf(stderr, "component-selection not implemented");
                $$ = 0;
        }
        | postfix_expr INDSEL IDENT {
                fprintf(stderr, "component-selection not implemented");
                $$ = 0;
        }
	| function_call	
        | postfix_expr PLUSPLUS { $$ = $1++; }
        | postfix_expr MINUSMINUS { $$ = $1--; }
        ;

function_call
	: postfix_expr '(' ')'
        | postfix_expr '(' expression_list ')'
	;

expression_list
        : assignment_expr
        | expression_list ',' assignment_expr
        ;

cast_expr
        : unary_expr
        | '(' INT ')' cast_expr 
        ;

unary_expr
        : postfix_expr
        | SIZEOF '(' INT ')' { $$ = sizeof(long long); }
        | '-' cast_expr { $$ = -$2; }
        | '+' cast_expr { $$ = $2;  printf("exprval=%lld",$$); }
        | '!' cast_expr { $$ = !$2; }
        | '~' cast_expr { $$ = ~$2; }
        | '&' cast_expr { $$ = (long long) &$2; }
        | '*' cast_expr { $$ = $2; }
        | PLUSPLUS unary_expr { $$ = ++$2; }
        | MINUSMINUS unary_expr { $$ = --$2; }
        ;

multiplicative_expr
        : cast_expr
        | multiplicative_expr '*' cast_expr { $$ = $1 * $3; }
        | multiplicative_expr '/' cast_expr {
		if ($3 != 0) $$ = $1 / $3;
		else {
		        fprintf(stderr, "Parse Error: divide by 0");
		        $$ = 0;
		}
        }
        | multiplicative_expr '%' cast_expr { $$ = $1 % $3; }
        ;

additive_expr
        : multiplicative_expr
        | additive_expr '+' multiplicative_expr { $$ = $1 + $3; }
        | additive_expr '-' multiplicative_expr { $$ = $1 - $3; }
        ;

shift_expr
        : additive_expr
        | shift_expr SHL additive_expr { $$ = $1 << $3; }
        | shift_expr SHR additive_expr { $$ = $1 >> $3; }
        ;

relational_expr
        : shift_expr
        | relational_expr '<' shift_expr { $$ = $1 < $3; }
        | relational_expr LTEQ shift_expr { $$ = $1 <= $3; }
        | relational_expr '>' shift_expr { $$ = $1 > $3; }
        | relational_expr GTEQ shift_expr { $$ = $1 >= $3; }
        ;

equality_expr
        : relational_expr
        | equality_expr EQEQ relational_expr { $$ = $1 == $3; }
        | equality_expr NOTEQ relational_expr { $$ = $1 != $3; }
        ;

bit_or_expr
        : bit_xor_expr
        | bit_or_expr '|' bit_xor_expr { $$ = $1 | $3; }
        ;

bit_xor_expr
        : bit_and_expr
        | bit_xor_expr '^' bit_and_expr { $$ = $1 ^ $3; }
        ;

bit_and_expr
        : equality_expr
        | bit_and_expr '&' equality_expr { $$ = $1 & $3; }
        ;

logical_or_expr
        : logical_and_expr
        | logical_or_expr LOGOR logical_and_expr { $$ = $1 || $3; }
        ;

logical_and_expr
        : bit_or_expr
        | logical_and_expr LOGAND bit_or_expr { $$ = $1 && $3; }
        ;

conditional_expr
        : logical_or_expr
        | logical_or_expr '?' expr ':' conditional_expr { $$ = $1 ? $3 : $5; }
        ;

assignment_expr
        : conditional_expr
        | unary_expr '=' assignment_expr { $$ = $3;printf( "exprval=%lld", $$); }
        | unary_expr PLUSEQ assignment_expr {$$ = $1 + $3;$1 = $$; }
        | unary_expr MINUSEQ assignment_expr { $$ = $1 - $3;$1 = $$;}
	| unary_expr TIMESEQ assignment_expr { $$ = $1 * $3;$1 = $$; }
        | unary_expr DIVEQ assignment_expr { $$ = $1 / $3;$1 = $$; }
        | unary_expr MODEQ assignment_expr { $$ = $1 % $3;$1 = $$; }
        | unary_expr SHLEQ assignment_expr { $$ = $1 << $3;$1 = $$; }
        | unary_expr SHREQ assignment_expr { $$ = $1 >> $3;$1 = $$; }
        | unary_expr ANDEQ assignment_expr { $$ = $1 & $3;$1 = $$; }
        | unary_expr OREQ assignment_expr { $$ = $1 | $3;$1 = $$; }
        | unary_expr XOREQ assignment_expr { $$ = $1 ^ $3;$1 = $$; }
        ;

expr
	: assignment_expr
	| expr ',' assignment_expr { $$ = $3; }
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

	strcpy(filename, "<stdin>");	
	curr= symTable_new(FILE_SCOPE, lineno, filename, NULL);
	yyparse();

	printf("EOF\n");
}

