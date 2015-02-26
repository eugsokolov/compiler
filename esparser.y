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
	
struct symbol *lval;
}



%token <yychar> CHARLIT
%token <yystring> IDENT STRING
%token <number> NUMBER 
%token INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ ANDEQ OREQ XOREQ
%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <number.yyint> primary_e unary_e cast_e multiplicative_e additive_e
%type <number.yyint> shift_e relational_e equality_e and_e xor_e or_e
%type <number.yyint> logical_and_e logical_or_e conditional_e assignment_e
%type <number.yyint> postfix_e generic_e
%type <lval> lval

%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation        */

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
        : function_definition_specifier compound_statement
        ;

function_definition_specifier
        : IDENT '(' ')' {
                //currently no declarations supported
                insert_symbol($1);
        }
        ;

compound_statement
        : '{' '}'
        | '{' {
                enum scope_type scope;
                if (curr->scope_type == FILE_SCOPE) {
                        //compound statement is attached to a function
                        scope = FUNCTION_SCOPE;
                } else {
                        //compound statement is a block
                        scope = BLOCK_SCOPE;
                }
                curr = symTable_new(scope, lineno, filename, curr);
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

declaration
        : INT identifier_list ';'
        ;

identifier_list
        : identifier_list ',' IDENT {
                insert_symbol($3);
        }
        | IDENT {
                insert_symbol($1);
        }
        ;

statement
        : compound_statement
        | generic_e ';' {
                //fprintf(stderr, "Parse error expression value = %lld", $1);
        }
        | ';'
        ;

initializer
        : assignment_e
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
        : '[' constant_e ']'
        | '.' IDENT
        ;

constant_e
        : conditional_e
        ;

primary_e
        : IDENT {
                struct symbol *s = symTable_getSymbol(curr, $1);
                if (s) {
                        $$ = s->value;
                } else {
                        $$ = 0;
                        fprintf(stderr, "Undefined identifier %s", $1);
                }
        }
        | NUMBER {
                if ($1.num_type == TYPE_INT ||
                    $1.num_type == TYPE_LONG ||
                    $1.num_type == TYPE_LONGLONG) {
                        $$ = $1.yyint;
                } else {
                        $$ = (long long)$1.yydouble;
                        fprintf(stderr,
                                "Truncating real number %Lg to integer %lld",
                                $1.yydouble,
                                $$);
                        printf("exprval=%lld",$$);
                }
        }
        | CHARLIT {
                //TODO: handle other types
                $$ = (long long)$1;
        }
        | STRING {
                $$ = (long long)$1;
        }
        | '(' generic_e ')' {
                $$ = (long long)$2;
        }
        ;

expression_list
        : assignment_e
        | expression_list ',' assignment_e
        ;

postfix_e
        : postfix_e '[' generic_e ']' {
                //TODO: add support
                fprintf(stderr, "Arrays not implemented");
                $$ = 0;
        }
        | postfix_e '.' IDENT {
                fprintf(stderr, "Struct/union not implemented");
                $$ = 0;
        }
        | postfix_e INDSEL IDENT {
                fprintf(stderr, "Struct/union not implemented");
                $$ = 0;
        }
        | postfix_e '(' ')'
        | postfix_e '(' expression_list ')'
        | lval PLUSPLUS {
                if ($1) {
                        $$ = $1->value++;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
        | lval MINUSMINUS {
                if ($1) {
                        $$ = $1->value--;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
        | '(' INT ')' '{' initializer_list ',' '}' {
                //TODO: change later for more types
                $$ = 1;
        }
        | '(' INT ')' '{' initializer_list '}' {
                $$ = 1;
        }
        | primary_e
        ;

cast_e
        : unary_e
        | '(' INT ')' cast_e {
                //TODO: add other types later
                $$ = (long long)$4;
        }
        ;

unary_e
        : postfix_e
        | SIZEOF '(' INT ')' {
                //TODO: add other types later
                $$ = sizeof(long long);
        }
        | '-' cast_e {
                $$ = -$2;
        }
        | '+' cast_e {
                $$ = $2;
                printf("exprval=%lld",$$);
        }
        | '!' cast_e {
                $$ = !$2;
        }
        | '~' cast_e {
                $$ = ~$2;
        }
        | '&' cast_e {
                //TODO: change later since address
                $$ = (long long) &$2;
        }
        | '*' cast_e {
                //TODO: no pointers yet
                $$ = $2;
        }
        | PLUSPLUS lval {
                if ($2) {
                        $$ = ++$2->value;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
        | MINUSMINUS lval {
                if ($2) {
                        $$ = --$2->value;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
        ;

multiplicative_e
        : cast_e
        | multiplicative_e '*' cast_e {
                $$ = $1 * $3;
        }
        | multiplicative_e '/' cast_e {
                if ($3) {
                        $$ = $1 / $3;
                } else {
                        fprintf(stderr, "divide by 0");
                        $$ = 0;
                }
        }
        | multiplicative_e '%' cast_e {
                $$ = $1 % $3;
        }
        ;

additive_e
        : multiplicative_e
        | additive_e '+' multiplicative_e {
                $$ = $1 + $3;
        }
        | additive_e '-' multiplicative_e {
                $$ = $1 - $3;
        }
        ;

shift_e
        : additive_e
        | shift_e SHL additive_e {
                $$ = $1 << $3;
        }
        | shift_e SHR additive_e {
                $$ = $1 >> $3;
                printf("exprval=%lld",$$);
        }
        ;

relational_e
        : shift_e
        | relational_e '<' shift_e {
                $$ = $1 < $3;
        }
        | relational_e LTEQ shift_e {
                $$ = $1 <= $3;
        }
        | relational_e '>' shift_e {
                $$ = $1 > $3;
        }
        | relational_e GTEQ shift_e {
                $$ = $1 >= $3;
        }
        ;

equality_e
        : relational_e
        | equality_e EQEQ relational_e {
                $$ = $1 == $3;
        }
        | equality_e NOTEQ relational_e {
                $$ = $1 != $3;
        }
        ;

or_e
        : xor_e
        | or_e '|' xor_e {
                $$ = $1 | $3;
        }
        ;

xor_e
        : and_e
        | xor_e '^' and_e {
                $$ = $1 ^ $3;
        }
        ;

and_e
        : equality_e
        | and_e '&' equality_e {
                $$ = $1 & $3;
        }
        ;

logical_and_e
        : or_e
        | logical_and_e LOGAND or_e {
                $$ = $1 && $3;
        }
        ;

logical_or_e
        : logical_and_e
        | logical_or_e LOGOR logical_and_e {
                $$ = $1 || $3;
        }
        ;

conditional_e
        : logical_or_e
        | logical_or_e '?' generic_e ':' conditional_e {
                $$ = $1 ? $3 : $5;
        }
        ;

assignment_e
        : conditional_e
        | lval '=' assignment_e {
                $$ = $3;
                printf( "exprval=%lld", $$);
        }
        | lval TIMESEQ assignment_e {
                $$ = $1->value * $3;
                $1->value = $$;
        }
        | lval DIVEQ assignment_e {
                $$ = $1->value / $3;
                $1->value = $$;
        }
        | lval MODEQ assignment_e {
                $$ = $1->value % $3;
                $1->value = $$;
        }
        | lval PLUSEQ assignment_e {
                $$ = $1->value + $3;
                $1->value = $$;
        }
        | lval MINUSEQ assignment_e {
                $$ = $1->value - $3;
                $1->value = $$;
        }
        | lval SHLEQ assignment_e {
                $$ = $1->value << $3;
                $1->value = $$;
        }
        | lval SHREQ assignment_e {
                $$ = $1->value >> $3;
                $1->value = $$;
        }
        | lval ANDEQ assignment_e {
                $$ = $1->value & $3;
                $1->value = $$;
        }
        | lval OREQ assignment_e {
                $$ = $1->value | $3;
                $1->value = $$;
        }
        | lval XOREQ assignment_e {
                $$ = $1->value ^ $3;
                $1->value = $$;
        }
        ;

generic_e
        : generic_e ',' assignment_e {
                $$ = $3;
        }
        | assignment_e
        ;

lval
        : IDENT {
                struct symbol *s = symTable_getSymbol(curr, $1);
                if (s) {
                        $$ = s;
                } else {
                        fprintf(stderr, "Unidentified identifier %s", $1);
                        $$ = 0;
                }
        }
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
	curr= symTable_new(FILE_SCOPE, lineno, filename, NULL);
	yyparse();
	printf("EOF\n");
}

