%error-verbose
%debug
%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: parser.y

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "esparser.tab.h"
#include "sym_table.h"
#include "ast.h"
#include "quads.h"
#include "def.h"

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
		enum number_type num_type;
		enum sign_type num_sign;
		long long yyint;
		long double yydouble;
	}number;

	struct ast_node *node;
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

%type <node> constant_expression primary_expression postfix_expression 
%type <node> function_call expression_list cast_expression 
%type <node> unary_expression multiplicative_expression additive_expression 
%type <node> shift_expression relational_expression equality_expression
%type <node> bit_or_expression bit_xor_expression bit_and_expression 
%type <node> logical_or_expression logical_and_expression conditional_expression 
%type <node> assignment_expression expression statement
%type <node> compound_statement
%type <node> conditional_statement iterative_statement switch_statement break_statement
%type <node> if_statement if_else_statement while_statement do_statement
%type <node> continue_statement return_statement goto_statement null_statement
%type <node> declaration_specifier storage_class_specifier
%type <node> typedef_definition function_declarator array_declarator
%type <node> direct_declarator simple_declarator pointer_declarator pointer
%type <node>  for_statement type_specifier declarator
%type <node> abstract_declarator enumeration_type_specifier floating_point_specifier
%type <node> type_qualifier integer_type_specifier character_type_specifier 
%type <node> for_expression bool_type_specifier structure_type_specifier
%type <node> union_type_specifier typedef_name initial_clause void_type_specifier
%type <node> direct_abstract_declarator declaration

%start translation_unit

%%

/* Declarations: Chapter 4 of H&S */

declaration
        : INT identifier_list ';' {
		int i;
                struct ast_node *head = $2;
                while ($2 != NULL){
                    struct ast_node *var_type = $1;
                    while (var_type != NULL && var_type->type == AST_STORAGE){
                        var_type = var_type->left;
                    }
                    var_type = ast_push_back(var_type, $2,LEFT);
                    $$ = ast_reverse_tree(var_type, LEFT);
                    if ($1->type == AST_STORAGE){
                        struct ast_node *tmp = $$->left;
                        struct ast_node *this = $1;
                        while (this->left != NULL && this->left->type == AST_STORAGE){
                            this = this->left;
                        }
                        this->left = tmp;
                        $$->left = $1;
                    }
                    if (print_declarations){
                        ast_print_tree($$);
                    }
                    $2 = $2->next;
                }
                $$ = head;
                $$ = NULL;
	}
	;


declaration_specifier
        : storage_class_specifier
        | storage_class_specifier declaration_specifier { $$ = ast_push_back($1, $2, LEFT); }
        | typedef_definition
        | typedef_definition declaration_specifier { $$ = ast_push_back($2, $1, LEFT); }
        | type_specifier
        | type_specifier declaration_specifier { $$ = ast_push_back($2, $1, LEFT); }
        | type_qualifier
        | type_qualifier declaration_specifier { $$ = $2; }
        ;

storage_class_specifier
        : AUTO { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_AUTO; }
        | EXTERN { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_EXTERN; }
        | STATIC { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_STATIC; }
        ;
	
typedef_definition
        : TYPEDEF { $$ = ast_newnode(AST_TYPEDEF);}
        ;

type_specifier
        : enumeration_type_specifier
        | floating_point_specifier
        | integer_type_specifier
        | structure_type_specifier
        | typedef_name
        | union_type_specifier
        | void_type_specifier
        ;

type_qualifier
        : CONST { $$ = NULL;}
        | VOLATILE { $$ = NULL; }
        | RESTRICT { $$ = NULL; }
 	;

declarator
        : pointer_declarator
        | direct_declarator
        ;

direct_declarator
        : simple_declarator
        | '(' declarator ')' {$$ = $2;} 
        | function_declarator 
        | array_declarator
        ;

simple_declarator
        : IDENT {

	}
	;

pointer_declarator
        : pointer direct_declarator {   $$ = ast_push_back($1,$2,LEFT);} 
        ;

pointer
        : '*' { $$ = ast_newnode(AST_PTR); }
        | '*' type_qualifier_list { $$ = ast_newnode(AST_PTR); }
        | '*' type_qualifier_list pointer { $$ = ast_newnode(AST_PTR); $$->left = $3; }
        | '*' pointer { $$ = ast_newnode(AST_PTR); $$->left = $2; }
        ;

type_qualifier_list
        : type_qualifier
        | type_qualifier_list type_qualifier
        ;


array_declarator
        : direct_declarator '[' ']'    {   } 
        | direct_declarator '[' constant_expression ']'     {   }
        ;

constant_expression
        : conditional_expression
        ;

function_declarator
        : direct_declarator '(' parameter_type_list ')' { fprintf(stderr, "Error: function prototypes not supported at: %s: %d\n",filename, lineno); }
        | direct_declarator '(' ')' { }
        | direct_declarator '(' identifier_list ')' { fprintf(stderr, "Error: function arguments not supported at: %s: %d\n",filename, lineno); }
        ;

parameter_type_list
        : parameter_list
        | parameter_list ',' ELLIPSIS
        ;

parameter_list
        : parameter_declaration
        | parameter_list ',' parameter_declaration
        ;

parameter_declaration
        : declaration_specifier declarator
        | declaration_specifier
        | declaration_specifier abstract_declarator
        ;

identifier_list
        : IDENT { insert_symbol($1); }
        | identifier_list ',' IDENT { insert_symbol($3); }
        ;

initializer
        : assignment_expression
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
        : '[' constant_expression ']'
        | '.' IDENT
        ;

/* Types: Chapter 5 of H&S */

integer_type_specifier
	: signed_type_specifier { $$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = SIZE_SIGNED;
		$$->attributes.scalar_type = SCALAR_INT; }
	| unsigned_type_specifier { $$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = SIZE_UNSIGNED;
		$$->attributes.scalar_type = SCALAR_INT; }
	| character_type_specifier
	| bool_type_specifier { $$ = ast_newnode(AST_SCALAR);
	$$->attributes.num_signed = SIZE_SIGNED;
	$$->attributes.scalar_type = SCALAR_INT; }
;

unsigned_type_specifier
	: UNSIGNED SHORT
	| UNSIGNED SHORT INT
	| UNSIGNED
	| UNSIGNED INT
	| UNSIGNED LONG
	| UNSIGNED LONG INT
	| UNSIGNED LONG LONG
	| UNSIGNED LONG LONG INT
	;

signed_type_specifier
	: SHORT
	| SHORT INT
	| SIGNED SHORT
	| SIGNED SHORT INT
	| INT
	| SIGNED INT
	| SIGNED
	| LONG
	| LONG INT
	| SIGNED LONG
	| SIGNED LONG INT
	| LONG LONG
	| LONG LONG INT
	| SIGNED LONG LONG
	| SIGNED LONG LONG INT
	;

character_type_specifier
	: CHAR { $$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = SIZE_SIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; }
	| SIGNED CHAR { $$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = SIZE_SIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; }
	| UNSIGNED CHAR { $$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = SIZE_UNSIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; }
	;

floating_point_specifier
	: FLOAT { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| DOUBLE { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| LONG DOUBLE { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| complex_type_specifier { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	;

complex_type_specifier
	: FLOAT _COMPLEX
	| DOUBLE _COMPLEX
	| LONG DOUBLE _COMPLEX
	;

void_type_specifier
	: VOID { $$=NULL; }
	;

bool_type_specifier
	: _BOOL { $$=NULL; }
	;

enumeration_type_specifier
	: enumeration_type_definition { fprintf(stderr, "Warning: This compiler doesn't support enum types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| enumeration_type_reference { fprintf(stderr, "Warning: This compiler doesn't support enum types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	;

enumeration_type_definition
	: ENUM '{' enumeration_definition_list '}'
	| ENUM enumeration_tag '{' enumeration_definition_list '}'
	| ENUM '{' enumeration_definition_list ',' '}'
	| ENUM enumeration_tag '{' enumeration_definition_list ',' '}'
	;
enumeration_type_reference
	: ENUM enumeration_tag
	;

enumeration_tag
	: IDENT
;

enumeration_definition_list
	: enumeration_constant_definition
	| enumeration_definition_list ',' enumeration_constant_definition
	;

enumeration_constant_definition
	: enumeration_constant
	| enumeration_constant '=' expression
	;

enumeration_constant
	: IDENT
	;

structure_type_specifier
	: structure_type_definition { fprintf(stderr, "Warning: This compiler doesn't support struct types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| structure_type_reference { fprintf(stderr, "Warning: This compiler doesn't support struct types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	;

structure_type_definition
	: STRUCT '{' field_list '}'
	| STRUCT structure_tag '{' field_list '}'
	;

structure_type_reference
	: STRUCT structure_tag
	;

structure_tag
	: IDENT
	;

field_list
	: component_declaration
	| field_list component_declaration
	;
	
component_declaration
	: type_specifier component_declaration_list ';'
	;

component_declaration_list
	: component_declarator
	| component_declaration_list ',' component_declarator
	;

component_declarator
	: simple_component
	| bit_field
	;

simple_component
	: declarator
	;
	
bit_field
	: ':' width
	| declarator ':' width
	;

width
	: constant_expression
	;

union_type_specifier
	: union_type_definition { fprintf(stderr, "Warning: This compiler doesn't support union types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	| union_type_reference { fprintf(stderr, "Warning: This compiler doesn't support union types - %s: %d\n",
		filename, line_number);$$ = NULL; }
	;

union_type_definition
	: UNION '{' field_list '}'
	| UNION union_tag '{' field_list '}'
	;

union_type_reference
	: UNION union_tag
	;

union_tag
	: IDENT
	;

typedef_name
	: TYPEDEF_NAME {
		struct ast_node *t;
		t = get_ident(current_scope, yylval.yystring, NAMESPACE_OTHER);
		if (t->left != NULL && t->left->type == AST_TYPEDEF && t->left->left != NULL){
		$$ = t->left->left;
		} else {
		fprintf(stderr, "Error: Problem with typedef - %s: %d\n", filename, line_number);
		$$ = NULL;
		}
	}
	;

type_name
	: declaration_specifier
	| declaration_specifier abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

pointer
	: '*' { $$ = ast_newnode(AST_PTR); }
	| '*' type_qualifier_list { $$ = ast_newnode(AST_PTR); }
	| '*' type_qualifier_list pointer { $$ = ast_newnode(AST_PTR); $$->left = $3; }
	| '*' pointer { $$ = ast_newnode(AST_PTR); $$->left = $2; }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '[' constant_expression ']'
	| '[' expression ']'
	| direct_abstract_declarator '[' expression ']'
	| '[' '*' ']'
	| direct_abstract_declarator '[' '*' ']'
	| '(' ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	| '(' parameter_type_list ')'
	;

/* Expressions: Chapter 7 of H&S */
primary_expression
        : IDENT {
		char *ident = yylval.yystring;
		ident[strlen(yylval.yystring)] = '\0';
                struct symbol *s = symTable_getSymbol(curr, $1, curr->scope_type);
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
        | '(' expression ')' { $$ = (long long)$2; }
        ;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']' {
                fprintf(stderr, "Error: arrays not supported at: %s: %d\n",filename, lineno); 
                $$ = 0;
        }
        | postfix_expression '.' IDENT {
		fprintf(stderr, "Error: direct component-selection not supported at: %s: %d\n",filename, lineno); 
                $$ = 0;
        }
        | postfix_expression INDSEL IDENT {
f		printf(stderr, "Error: indirect component-selection not supported at: %s: %d\n",filename, lineno); 
                $$ = 0;
        }
	| function_call	
        | postfix_expression PLUSPLUS { $$ = $1++; }
        | postfix_expression MINUSMINUS { $$ = $1--; }
        ;

function_call
	: postfix_expression '(' ')'
        | postfix_expression '(' expression_list ')'
	;

expression_list
        : assignment_expression
        | expression_list ',' assignment_expression
        ;

cast_expression
        : unary_expression
        | '(' INT ')' cast_expression {$$ = (int)$4; } 
        ;

unary_expression
        : postfix_expression
        | SIZEOF '(' type_name ')' { $$ = sizeof(long long); }
	| SIZEOF '(' unary_expression ')' {  }
        | '-' cast_expression { $$ = -$2; }
        | '+' cast_expression { $$ = $2;  printf("exprval=%lld\n",$$); }
        | '!' cast_expression { $$ = !$2; }
        | '~' cast_expression { $$ = ~$2; }
        | '&' cast_expression { $$ = (long long) &$2; }
        | '*' cast_expression { $$ = $2; }
        | PLUSPLUS unary_expression { $$ = ++$2; }
        | MINUSMINUS unary_expression { $$ = --$2; }
        ;

multiplicative_expression
        : cast_expression
        | multiplicative_expression '*' cast_expression { $$ = $1 * $3; }
        | multiplicative_expression '/' cast_expression {
		if ($3 != 0) $$ = $1 / $3;
		else {
		        fprintf(stderr, "Parse Error: divide by 0\n");
		        $$ = 0;
		}
        }
        | multiplicative_expression '%' cast_expression { $$ = $1 % $3; }
        ;

additive_expression
        : multiplicative_expression
        | additive_expression '+' multiplicative_expression { $$ = $1 + $3; }
        | additive_expression '-' multiplicative_expression { $$ = $1 - $3; }
        ;

shift_expression
        : additive_expression
        | shift_expression SHL additive_expression { $$ = $1 << $3; }
        | shift_expression SHR additive_expression { $$ = $1 >> $3; }
        ;

relational_expression
        : shift_expression
        | relational_expression '<' shift_expression { $$ = $1 < $3; }
        | relational_expression LTEQ shift_expression { $$ = $1 <= $3; }
        | relational_expression '>' shift_expression { $$ = $1 > $3; }
        | relational_expression GTEQ shift_expression { $$ = $1 >= $3; }
        ;

equality_expression
        : relational_expression
        | equality_expression EQEQ relational_expression { $$ = $1 == $3; }
        | equality_expression NOTEQ relational_expression { $$ = $1 != $3; }
        ;

bit_or_expression
        : bit_xor_expression
        | bit_or_expression '|' bit_xor_expression { $$ = $1 | $3; }
        ;

bit_xor_expression
        : bit_and_expression
        | bit_xor_expression '^' bit_and_expression { $$ = $1 ^ $3; }
        ;

bit_and_expression
        : equality_expression
        | bit_and_expression '&' equality_expression { $$ = $1 & $3; }
        ;

logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGOR logical_and_expression { $$ = $1 || $3; }
        ;

logical_and_expression
        : bit_or_expression
        | logical_and_expression LOGAND bit_or_expression { $$ = $1 && $3; }
        ;

conditional_expression
        : logical_or_expression
        | logical_or_expression '?' expression ':' conditional_expression { $$ = $1 ? $3 : $5; }
        ;

assignment_expression
        : conditional_expression
        | unary_expression '=' assignment_expression { $$ = $3;printf( "exprval=%lld\n", $$); }
        | unary_expression PLUSEQ assignment_expression {$$ = $1 + $3;$1 = $$; }
        | unary_expression MINUSEQ assignment_expression { $$ = $1 - $3;$1 = $$;}
	| unary_expression TIMESEQ assignment_expression { $$ = $1 * $3;$1 = $$; }
        | unary_expression DIVEQ assignment_expression { $$ = $1 / $3;$1 = $$; }
        | unary_expression MODEQ assignment_expression { $$ = $1 % $3;$1 = $$; }
        | unary_expression SHLEQ assignment_expression { $$ = $1 << $3;$1 = $$; }
        | unary_expression SHREQ assignment_expression { $$ = $1 >> $3;$1 = $$; }
        | unary_expression ANDEQ assignment_expression { $$ = $1 & $3;$1 = $$; }
        | unary_expression OREQ assignment_expression { $$ = $1 | $3;$1 = $$; }
        | unary_expression XOREQ assignment_expression { $$ = $1 ^ $3;$1 = $$; }
        ;

expression
	: assignment_expression
	| expression ',' assignment_expression { $$ = $3; }
        ;

/* Statements: Chapter 8 of H&S */
statement
        : expression ';' 
        | labeled_statement { $$ = NULL; }
        | compound_statement
        | conditional_statement 
        | iterative_statement 
        | switch_statement 
        | break_statement { $$ = NULL; }
        | continue_statement { $$ = NULL; }
        | return_statement { $$ = NULL; } 
        | goto_statement { $$ = NULL; }
        | null_statement
	;

conditional_statement
        : if_statement
        | if_else_statement
        ;

iterative_statement
        : do_statement
        | while_statement
        | for_statement
        ;

labeled_statement
        : label ':' statement
        ;

label
        : named_label
        | case_label
        | default_label
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

conditional_statement
        : if_statement
        | if_else_statement
        ;

if_statement
        : IF '(' expression ')' statement {

	}
        ;

if_else_statement
        : IF '(' expression ')' statement ELSE statement {

	}
        ;

iterative_statement
        : do_statement
        | while_statement
        | for_statement
        ;

do_statement
        : DO statement WHILE '(' expression ')' ';' {
	
	}
        ;

while_statement
        : WHILE '(' expression ')' statement {

	}
        ;

for_statement
        : FOR for_expression statement { $$ = $2; $$->body = $3; }
        ;

for_expression
	: '(' ';' ';' ')' { $$ = ast_newnode(AST_FOR); }
	| '(' initial_clause ';' ';' ')' { $$ = ast_newnode(AST_FOR); $$->left = $2; }
	| '(' ';' expression ';' ')' { $$ = ast_newnode(AST_FOR); $$->cond = $3; }
	| '(' ';' ';' expression ')' { $$ = ast_newnode(AST_FOR); $$->right = $4; }
	| '(' initial_clause ';' expression ';' ')' { $$ = ast_newnode(AST_FOR); $$->left = $2; $$->cond = $4; }
	| '(' ';' expression ';' expression ')' { $$ = ast_newnode(AST_FOR); $$->cond = $3; $$->right = $5; }
	| '(' initial_clause ';' expression ';' expression ')' { $$ = ast_newnode(AST_FOR); $$->left = $2; $$->cond = $4; $$->right = $6; }
;

initial_clause
	: expression
	| declaration
	;

switch_statement
        : SWITCH '(' expression ')' statement {
	
	}
        ;

case_label
        : CASE constant_expression
        ;

default_label
        : DEFAULT
        ;

break_statement
        : BREAK ';'
        ;
    
continue_statement
        : CONTINUE ';'
        ;

return_statement
        : RETURN ';'
        | RETURN expression ';'
        ;

goto_statement
        : GOTO named_label ';'
        ;

named_label
        : IDENT 
        ;

null_statement
        : ';' { $$ = NULL; }
        ;

/* Functions: Chapter 9 of H&S */
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
	| declaration_specifier declarator declaration_list
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

%%

void insert_symbol(char *s){

printf("*********%s***********\n",s);
	struct symbol *st = sym_new(filename, lineno);
	if(symTable_push(curr, s, st, curr->scope_type) != TRUE){
		st = symTable_getSymbol(curr,s, curr->scope_type);
		fprintf(stderr, "Error: %s previously defined around %s:%d\n", s, st->filename, st->linenumber);
	}
//symTable_print(curr);
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
