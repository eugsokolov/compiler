%error-verbose
%debug
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
#include "sym_table.h"

#define YYDEBUG 1
int yydebug = 0;

extern int yylex();
extern int yyparse();
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
void yyerror(const char *s);
void insert_symbol(char *s);

struct sym_table *curr;

%}

%union{

	char yychar;
	char *yystring;

	struct number{
		enum number_type{
			TYPE_INT,
			TYPE_LONG,
			TYPE_LONGLONG,
			TYPE_FLOAT,
			TYPE_DOUBLE,
			TYPE_LONGDOUBLE
		} num_type;
		enum sign_type{
			TYPE_UNSIGNED,
			TYPE_SIGNED
		} num_sign;
		long long yyint;
		long double yydouble;
	}number;

	void *nil;
}

%token <yychar> CHARLIT
%token <yystring> IDENT STRING
%token <number> NUMBER 

%token <nil> INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ
%token <nil> LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ
%token <nil> SHLEQ SHREQ ANDEQ OREQ XOREQ
%token <nil> AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE
%token <nil> ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG
%token <nil> REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC
%token <nil> STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED
%token <nil> VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <number.yyint> constant_expr primary_expr postfix_expr 
%type <number.yyint> function_call expression_list cast_expr 
%type <number.yyint> unary_expr multiplicative_expr additive_expr 
%type <number.yyint> shift_expr relational_expr equality_expr
%type <number.yyint>  bit_or_expr bit_xor_expr bit_and_expr 
%type <number.yyint> logical_or_expr logical_and_expr conditional_expr 
%type <number.yyint> assignment_expr expr
%type <nil> compound_statement

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
        : '{' '}' { $$ = NULL; }
        | '{' { //midaction rule
                if (curr->scope_type == FILE_SCOPE)
                        curr = symTable_new(FUNCTION_SCOPE, lineno, filename, curr);
                else
                        curr = symTable_new(BLOCK_SCOPE, lineno, filename, curr);
        } declaration_or_statement_list '}' {
                curr = symTable_pop(curr);
        }
        ;

declaration_or_statement_list
	: declaration_or_statement
	| declaration_or_statement_list declaration_or_statement
	;

declaration_or_statement
        : declaration
	| statement
        ;

statement
        : expr ';' 
        | compound_statement
	| ';'
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

declaration
        : INT identifier_list ';'
	| declaration_specifiers initialized_declarator_list ';'
	;

declaration_specifiers
	: '+++'
	;

function_specifier
	: '+++'
	;

initialized_declarator_list
	: '+++'
	;
	
initializer
        : assignment_expr
        | '{' initializer_list '}'
        | '{' initializer_list ',' '}'
        ;

initializer_list
        : initializer
        | initializer_list ',' initializer
        | designation initializer
        | initializer_list ',' designation initializer
        ;

designation
        : designator_list '='
        ;

designator_list
        : designator
        | designator_list designator
        ;

designator
        : '[' constant_expr ']'
        | '.' IDENT
        ;

identifier_list
        : identifier_list ',' IDENT { insert_symbol($3); }
        | IDENT { insert_symbol($1); }
        ;

constant_expr
        : conditional_expr
        ;

primary_expr
        : IDENT {
		char *ident = yylval.yystring;
		ident[strlen(yylval.yystring)] = '\0';
		fprintf(stderr, "ident: %s\n", ident);
                struct symbol *s = symTable_getSymbol(curr, $1, curr->scope_type);
		//symTable_print(curr);
		//fprintf(stderr, "sym: %d\n", (long long)s);
		if (s != NULL) $$ = (long long)s;
                else {
                        $$ = 0;
                        fprintf(stderr, "Undefined identifier %s\n", $1);
                }
        }
        | NUMBER {
	
                if ($1.num_type == TYPE_INT || $1.num_type == TYPE_LONG || $1.num_type == TYPE_LONGLONG)
                        $$ = yylval.number.yyint;
                else {
                        $$ = (long long)yylval.number.yydouble;
                        fprintf(stderr,"Truncating real number %Lg to integer %lld\n",yylval.number.yydouble,$$);
                        printf("exprval=%lld\n",$$);
                }
        }
        | '(' expr ')' { $$ = (long long)$2; }
        ;

postfix_expr
	: primary_expr
	| postfix_expr '[' expr ']' {
                fprintf(stderr, "Arrays not implemented\n");
                $$ = 0;
        }
        | postfix_expr '.' IDENT {
                fprintf(stderr, "component-selection not implemented\n");
                $$ = 0;
        }
        | postfix_expr INDSEL IDENT {
                fprintf(stderr, "component-selection not implemented\n");
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
        | '(' INT ')' cast_expr {$$ = (int)$4; } 
        ;

unary_expr
        : postfix_expr
        | SIZEOF '(' INT ')' { $$ = sizeof(long long); }
        | '-' cast_expr { $$ = -$2; }
        | '+' cast_expr { $$ = $2;  printf("exprval=%lld\n",$$); }
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
		        fprintf(stderr, "Parse Error: divide by 0\n");
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
        | unary_expr '=' assignment_expr { $$ = $3;printf( "exprval=%lld\n", $$); }
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
	if(symTable_push(curr, s, st, curr->scope_type) != TRUE){
		st = symTable_getSymbol(curr,s, curr->scope_type);
		fprintf(stderr, "Error: %s previously defined around %s:%d\n", s, st->filename, st->linenumber);
	}
symTable_print(curr);
//fprintf(stderr, "sym val: %s with %lld\n", s,st->value);
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
