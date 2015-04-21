%debug
%{
//Eugene Sokolov
//ECE466: Compilers
//parser.y
#include "def.h"
#include "ast.h"
#include "hash.h"
#include "quads.h"
#include "sym_table.h"

extern int yylex();
extern int yyleng;
extern int lineno;
extern char filename[128];
extern FILE *yyin;
int yyerror(const char *p) {fprintf(stderr, "ERROR: unrecognized syntax: %s\n", p);}
void error_msg(char *s, int lineno, char* filename){fprintf(stderr, "Warning: this compiler does not support %s types @:%s: %d\n",s,filename, lineno);}

int yydebug=0;
struct sym_table *curr_scope;
%}

%union{

	char yychar;
	char *yystring;
	int yystring_size;

	struct num{
		enum number_type num_type;
		enum sign_type num_sign;
		long long yyint;
		long double yydouble;
	}number;

	struct ast_node *node;
	void *nil;
}


%token <yychar> CHARLIT
%token <yystring> IDENT
%token <yystring> STRING
%token <number.yyint> NUMBER

%token <number.yyint> INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ
%token <number.yyint> LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ
%token <number.yyint> SHLEQ SHREQ ANDEQ OREQ XOREQ
%token <number.yyint> PREINC POSTINC PREDEC POSTDEC
%token <yystring> AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE
%token <yystring> ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG
%token <yystring> REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC
%token <yystring> STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED
%token <yystring> VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <node> declaration declaration_specifiers storage_class_specifier
%type <node> initialized_declarator_list initialized_declarator type_specifier type_qualifier
%type <node> declarator direct_declarator simple_declarator
%type <node> pointer_declarator pointer array_declarator constant_expression

%type <node> integer_type_specifier character_type_specifier floating_point_specifier
%type <node> enumeration_type_specifier union_type_specifier structure_type_specifier 
%type <node> void_type_specifier bool_type_specifier
%type <node> type_name typedef_name typedef_definition

%type <node> primary_expression parenthesized_expression postfix_expression subscript_expression
%type <node> component_selection_expression indirection_expression
%type <node> expression_list postincrement_expression postdecrement_expression cast_expression 
%type <node> unary_expression sizeof_expression unary_minus_expression unary_plus_expression 
%type <node> logical_negation_expression bitwise_negation_expression 
%type <node> address_expression preincrement_expression predecrement_expression 
%type <node> multiplicative_expression additive_expression shift_expression 
%type <node> relational_expression equality_expression 
%type <node> bitwise_or_expression bitwise_xor_expression bitwise_and_expression
%type <node> logical_or_expression logical_and_expression conditional_expression
%type <node> assignment_expression expression
%type <number.yyint> assignment_operator

%type <node> statement conditional_statement iterative_statement expression_statement 
%type <node> compound_statement declaration_or_statement_list declaration_or_statement 
%type <node> if_statement if_else_statement while_statement do_statement  
%type <node> for_statement for_expression 
%type <node> initial_clause switch_statement null_statement 

%type <node> translation_unit top_level_declaration
%type <node> function_declarator function_definition function_call function_specifier

%start translation_unit

%% /* Grammar rules and actions follow */

/* Declarations: Chapter 4 of H&S */
declaration
        : declaration_specifiers initialized_declarator_list ';' {
		int i;
		struct ast_node *head = $2;
		while($2 != NULL){
			struct ast_node *var = $1;
			while((var != NULL) && (var->type == AST_STORAGE))
				var = var->left;
			var = ast_push_back(var, $2,LEFT);
               		$$ = ast_reverse_tree(var, LEFT);
			if($1->type == AST_STORAGE){
				struct ast_node *tmp = $$->left;
				struct ast_node *tmp2 = $1;
				while((tmp2->left != NULL) && (tmp2->left->type == AST_STORAGE))
					tmp2 = tmp2->left;
			
			tmp2->left = tmp;
			$$->left = $1;
		    	}
//ast_print_tree($$);
		    	$2 = $2->next;
		}
		$$ = head;
		$$ = NULL;
	}
        ;

declaration_specifiers
        : storage_class_specifier
        | storage_class_specifier declaration_specifiers { $$ = ast_push_back($1, $2, LEFT); }
        | type_specifier
        | type_specifier declaration_specifiers { $$ = ast_push_back($2, $1, LEFT); }
        | type_qualifier
        | type_qualifier declaration_specifiers { $$ = $2; }
        ;

storage_class_specifier
        : AUTO { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_AUTO; }
        | EXTERN { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_EXTERN; }
        | STATIC { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_STATIC; }
        ;
	
initialized_declarator_list
        : initialized_declarator { $$ = $1; }
        | initialized_declarator_list ',' initialized_declarator { $$ = ast_push_back($1,$3,NEXT); }
        ;

initialized_declarator
        : declarator
        | declarator '=' initializer { $$ = $1; }
        ;

type_specifier
        : enumeration_type_specifier
        | floating_point_specifier
        | integer_type_specifier
        | structure_type_specifier
        | typedef_name
	| typedef_definition
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
		int ret;
		$$ = ast_newnode(AST_VAR);
		$$->scope_type = curr_scope->scope_type;
		strcpy($$->attributes.identifier, yylval.yystring);
		$$->attributes.linestart = lineno;
		strcpy($$->attributes.filename, filename);
		
		ret = symTable_push(curr_scope, yylval.yystring, $$, NAMESPACE_OTHER);
		if(!ret)
			fprintf(stderr, "Error: redeclaration of identifer: %s @ %s:%d\n", yylval.yystring, filename, lineno);
		
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
        : direct_declarator '[' ']'  {
		$$ = ast_newnode(AST_ARY);
               	$$->left = $1;
		$$->attributes.size = -1;  
	} 
        | direct_declarator '[' constant_expression ']'  { 
		if($3->type != AST_NUM) {
			error_msg("non integer array declaration",lineno,filename);
			$$ = NULL;
		}
		else {
			$$ = ast_newnode(AST_ARY);
			$$->left = $1;
			$$->attributes.size = $3->attributes.num; 
		}
	}
        ;

constant_expression
        : conditional_expression
        ;

function_declarator
        : direct_declarator '(' parameter_type_list ')' { error_msg("function prototype",lineno,filename); }
        | direct_declarator '(' ')' { 
		$$ = ast_newnode(AST_FN); 
		ast_push_back($$,$1,LEFT); 
	}
        | direct_declarator '(' identifier_list ')' { error_msg("function argument",lineno,filename);}
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
        : declaration_specifiers declarator
        | declaration_specifiers
        | declaration_specifiers abstract_declarator
        ;

identifier_list
        : IDENT
        | identifier_list ',' IDENT
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
        : signed_type_specifier { 
		$$ = ast_newnode(AST_SCALAR); 
		$$->attributes.num_signed = TYPE_SIGNED;
		$$->attributes.scalar_type = SCALAR_INT; 
	}
        | unsigned_type_specifier { 
		$$ = ast_newnode(AST_SCALAR); 
		$$->attributes.num_signed = TYPE_UNSIGNED;
		$$->attributes.scalar_type = SCALAR_INT; 
	}
        | character_type_specifier 
        | bool_type_specifier { 
		$$ = ast_newnode(AST_SCALAR);
		$$->attributes.num_signed = TYPE_SIGNED;
		$$->attributes.scalar_type = SCALAR_INT; 
	}
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
        ;

unsigned_type_specifier
        : UNSIGNED SHORT
        | UNSIGNED SHORT INT
        | UNSIGNED
        | UNSIGNED INT
        | UNSIGNED LONG
        | UNSIGNED LONG INT
        ;

character_type_specifier
        : CHAR { 
		$$ = ast_newnode(AST_SCALAR); 
		$$->attributes.num_signed = TYPE_SIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; 
	}
        | SIGNED CHAR { 
		$$ = ast_newnode(AST_SCALAR); 
		$$->attributes.num_signed = TYPE_SIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; 
	}
        | UNSIGNED CHAR { 
		$$ = ast_newnode(AST_SCALAR); 
		$$->attributes.num_signed = TYPE_UNSIGNED;
		$$->attributes.scalar_type = SCALAR_CHAR; 
	}
        ;

floating_point_specifier
        : FLOAT {  error_msg("floating point",lineno,filename);$$ = NULL; }
        | DOUBLE {  error_msg("floating point",lineno,filename);;$$ = NULL; }
        | LONG DOUBLE {  error_msg("floating point",lineno,filename);$$ = NULL; }
        | complex_type_specifier {  error_msg("floating point",lineno,filename);$$ = NULL; }
        ;

complex_type_specifier
        : FLOAT _COMPLEX
        | DOUBLE _COMPLEX
        | LONG DOUBLE _COMPLEX
        ;

bool_type_specifier
        : _BOOL { $$=NULL; }
        ;

void_type_specifier
        : VOID { $$=NULL; }
        ;

typedef_definition
        : TYPEDEF {  error_msg("typedef",lineno,filename);$$ = NULL; }
        ;

enumeration_type_specifier
        : enumeration_type_definition {  error_msg("enum",lineno,filename);$$ = NULL; }
        | enumeration_type_reference { error_msg("enum",lineno,filename);$$ = NULL; }
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
        : structure_type_definition {  error_msg("struct",lineno,filename);$$ = NULL; }
        | structure_type_reference {  error_msg("struct",lineno,filename);$$ = NULL; }
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
        : union_type_definition {  error_msg("union",lineno,filename);$$ = NULL; }
        | union_type_reference {  error_msg("union",lineno,filename);$$ = NULL; }
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
        : TYPEDEF_NAME {  error_msg("typedef name",lineno,filename);$$ = NULL; }
        ;

type_name
        : declaration_specifiers
        | declaration_specifiers abstract_declarator
        ;

abstract_declarator
        : pointer
        | direct_abstract_declarator
        | pointer direct_abstract_declarator
        ;

/* Duplicate pointer definition */
/* Duplicate type-qualifier-list definition */

direct_abstract_declarator
        : '(' abstract_declarator ')'
        | '[' ']'
        | direct_abstract_declarator '[' ']'
        | direct_abstract_declarator '[' constant_expression ']'
        | '[' constant_expression ']'
        | '[' expression ']'
        |  direct_abstract_declarator '[' expression ']'
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
		//ident[yylval.yystring_size] = '\0';
		struct ast_node *var = symTable_getSymbol(curr_scope, ident, NAMESPACE_OTHER);
		$$ = var;
	}
        | NUMBER { 
		$$ = ast_newnode(AST_NUM); 
		$$->attributes.num = yylval.number.yyint; 
		$$->attributes.linestart = lineno;
	}
        | CHARLIT { 
		$$ = ast_newnode(AST_CHAR); 
		$$->attributes.num =(int)(yylval.yychar); 
		$$->attributes.linestart = lineno;
	}
        | STRING { 
		$$ = ast_newnode(AST_STR); 
		strcpy($$->attributes.str, yylval.yystring); 
		$$->attributes.linestart = lineno;
	}
        | parenthesized_expression
        ;

parenthesized_expression
        : '(' expression ')' { $$ = $2; }
        ;

postfix_expression
        : primary_expression
        | subscript_expression
        | component_selection_expression
        | function_call
        | postincrement_expression
        | postdecrement_expression
        | '(' type_name ')' '{' initializer_list '}' { $$ = NULL; }
        | '(' type_name ')' '{' initializer_list ',' '}' { $$ = NULL; }
        ;

subscript_expression
        : postfix_expression '[' expression ']' {
		$$ = ast_newnode(AST_UNOP);
		$$->attributes.op = '*';
		struct ast_node *new = ast_newnode(AST_BINOP);
		new->attributes.op = '+';
		new->left = $1;
		new->right = $3;
		$$->left = new;
	}
        ;

component_selection_expression
        : direct_component_selection { $$ = NULL; }
        | indirect_component_selection { $$ = NULL; }
        ;

direct_component_selection
        : postfix_expression '.' IDENT
        ;

indirect_component_selection
        : postfix_expression INDSEL IDENT
        ;

function_call
        : postfix_expression '(' ')' { $$ = ast_newnode(AST_FNCALL); $$->left = $1; }
        | postfix_expression '(' expression_list ')' {
		$$ = ast_newnode(AST_FNCALL);
		$$->left = $1;
		$$->right = $3;
	}
        ;

expression_list
        : assignment_expression
        | expression_list ',' assignment_expression { $$ = ast_push_back($1, $3, NEXT); }
        ;

postincrement_expression
        : postfix_expression PLUSPLUS { $$ = ast_newnode(AST_UNOP); $$->attributes.op = POSTINC; $$->left = $1; }
        ;

postdecrement_expression
        : postfix_expression MINUSMINUS { $$ = ast_newnode(AST_UNOP); $$->attributes.op = POSTDEC; $$->left = $1; }
        ;

cast_expression
        : unary_expression
        | '(' type_name ')' cast_expression { error_msg("cast expression",lineno,filename);$$ = NULL; }
        ;

unary_expression
        : postfix_expression
        | sizeof_expression
        | unary_minus_expression
        | unary_plus_expression
        | logical_negation_expression
        | bitwise_negation_expression
        | address_expression
        | indirection_expression
        | preincrement_expression
        | predecrement_expression
        ;

sizeof_expression
        : SIZEOF '(' type_name ')' { $$ = ast_newnode(AST_UNOP); $$->attributes.op = SIZEOF; $$->left=$3; }
        | SIZEOF unary_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = SIZEOF; $$->left=$2; }
        ;

unary_minus_expression
        : '-' cast_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '-'; $$->left=$2; }
        ;

unary_plus_expression
        : '+' cast_expression  { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '+'; $$->left=$2; }
        ;

logical_negation_expression
        : '!' cast_expression  { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '!'; $$->left=$2; }
        ;

bitwise_negation_expression
        : '~' cast_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '~'; $$->left=$2; } 
        ;

address_expression
        : '&' cast_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '&'; $$->left=$2; }
        ;

indirection_expression
        : '*' cast_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = '*'; $$->left=$2; }
        ;

preincrement_expression
        : PLUSPLUS unary_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = PREINC; $$->left=$2; }
        ;

predecrement_expression
        : MINUSMINUS unary_expression { $$ = ast_newnode(AST_UNOP); $$->attributes.op = PREINC; $$->left=$2; }
        ;

multiplicative_expression
        : cast_expression
        | multiplicative_expression '*' cast_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '*'; 
						            $$->left=$1; $$->right=$3; }
        | multiplicative_expression '/' cast_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '/'; 
						            $$->left=$1; $$->right=$3; } 
        | multiplicative_expression '%' cast_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '%'; 
						            $$->left=$1; $$->right=$3; } 
        ;

additive_expression
        : multiplicative_expression
        | additive_expression '+' multiplicative_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '+'; 
						            $$->left=$1; $$->right=$3; } 
        | additive_expression '-' multiplicative_expression  { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '-'; 
						            $$->left=$1; $$->right=$3; }
        ;

shift_expression
        : additive_expression
        | shift_expression SHL additive_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = SHL; 
						            $$->left=$1; $$->right=$3; }
        | shift_expression SHR additive_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = SHR; 
						            $$->left=$1; $$->right=$3; }
        ;

relational_expression
        : shift_expression
        | relational_expression '<' shift_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '<'; 
						            $$->left=$1; $$->right=$3; }
        | relational_expression '>' shift_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '>'; 
						            $$->left=$1; $$->right=$3; }
        | relational_expression LTEQ shift_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = LTEQ; 
						            $$->left=$1; $$->right=$3; }
        | relational_expression GTEQ shift_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = GTEQ; 
						            $$->left=$1; $$->right=$3; }
        ;

equality_expression
        : relational_expression
        | equality_expression EQEQ relational_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = EQEQ; 
						            $$->left=$1; $$->right=$3; }
        | equality_expression NOTEQ relational_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = NOTEQ; 
						            $$->left=$1; $$->right=$3; }
        ;

bitwise_or_expression
        : bitwise_xor_expression
        | bitwise_or_expression '|' bitwise_xor_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '|'; 
						            $$->left=$1; $$->right=$3; }
        ;

bitwise_xor_expression
        : bitwise_and_expression
        | bitwise_xor_expression '^' bitwise_and_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '^'; 
						            $$->left=$1; $$->right=$3; }
        ;

bitwise_and_expression
        : equality_expression
        | bitwise_and_expression '&' equality_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = '&'; 
						            $$->left=$1; $$->right=$3; }
        ;

logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGOR logical_and_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = LOGOR; 
						            $$->left=$1; $$->right=$3; }
        ;

logical_and_expression
        : bitwise_or_expression
        | logical_and_expression LOGAND bitwise_or_expression { $$ = ast_newnode(AST_BINOP); 
						            $$->attributes.op = LOGAND; 
						            $$->left=$1; $$->right=$3; }
        ;


conditional_expression
        : logical_or_expression
        | logical_or_expression '?' expression ':' conditional_expression {  error_msg("conditional expression",lineno,filename);$$ = NULL; }
        ;


assignment_expression
        : constant_expression
        | unary_expression assignment_operator assignment_expression {
		$$ = ast_newnode(AST_ASSGN);
		$$->left = $1;
		if($2 == '=')
			$$->right = $3;
		else {
			struct ast_node *right;
			right = ast_newnode(AST_BINOP);
			right->left = $1;
			right->right = $3;
			switch($2){
			case TIMESEQ:
				right->attributes.op = '*';
				break;
			case DIVEQ:
				right->attributes.op = '/';
				break;
			case MODEQ:
				right->attributes.op = '%';
				break;
			case PLUSEQ:
				right->attributes.op = '+';
				break;
			case MINUSEQ:
				right->attributes.op = '-';
				break;
			case SHLEQ:
				right->attributes.op = SHL;
				break;
			case SHREQ:
				right->attributes.op = SHR;
				break;
			case ANDEQ:
				right->attributes.op = '&';
				break;
			case OREQ:
				right->attributes.op = '|';
				break;
			case XOREQ:
				right->attributes.op = '^';
				break;

			}
		$$->right = right;
		}
	}
        ;

assignment_operator
        : '=' { $$ = '='; }
        | TIMESEQ { $$ = TIMESEQ; }
        | DIVEQ { $$ = DIVEQ; }
        | MODEQ { $$ = MODEQ; }
        | PLUSEQ { $$ = PLUSEQ; }
        | MINUSEQ { $$ = MINUSEQ; }
        | SHLEQ { $$ = SHLEQ; }
        | SHREQ { $$ = SHREQ; }
        | ANDEQ { $$ = ANDEQ; }
        | OREQ { $$ = OREQ; }
        | XOREQ { $$ = XOREQ; }
        ;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

/* Statements: Chapter 8 of H&S */
statement
        : expression_statement 
        | labeled_statement { error_msg("labeled statement",lineno,filename);$$ = NULL; }
        | compound_statement
        | conditional_statement 
        | iterative_statement 
        | switch_statement 
        | break_statement { error_msg("break statement",lineno,filename);$$ = NULL; }
        | continue_statement { error_msg("continue statement",lineno,filename);$$ = NULL; }
        | return_statement { error_msg("return statement",lineno,filename);$$ = NULL; }
        | goto_statement { error_msg("go to statement",lineno,filename);$$ = NULL; }
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

expression_statement
        : expression ';' { $$ = $1; }
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
        | '{' { curr_scope = symTable_new(BLOCK_SCOPE, lineno, filename, curr_scope); } 
            declaration_or_statement_list '}' { $$ = $3; curr_scope = symTable_pop(curr_scope); }
        ;

declaration_or_statement_list
        : declaration_or_statement { $$ = $1; }
        | declaration_or_statement_list declaration_or_statement { $$ = ast_push_back($1, $2, NEXT); }
        ;

declaration_or_statement
        : declaration
        | statement
        ;

if_statement
        : IF '(' expression ')' statement {
		$$ = ast_newnode(AST_IF);
		$$->cond = $3;
		$$->body = $5;
		$$->body = NULL;
	}
        ;

if_else_statement
        : IF '(' expression ')' statement ELSE statement {
		$$ = ast_newnode(AST_IF);
		$$->cond = $3;
		$$->body = $5;
		$$->other = $7;
        }
        ;

while_statement
        : WHILE '(' expression ')' statement {
		$$ = ast_newnode(AST_WHILE);
		$$->cond = $3;
		$$->body = $5;
	}
        ;

do_statement
        : DO statement WHILE '(' expression ')' ';' {
		$$ = ast_newnode(AST_DO);
		$$->cond = $5;
		$$->body = $2;
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
		$$ = ast_newnode(AST_SWITCH);
		$$->cond = $3;
		$$->body = $5;
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
        : function_specifier '{' { curr_scope = symTable_new(FUNCTION_SCOPE, lineno, filename, curr_scope); } 
        	declaration_or_statement_list '}'  { 
		curr_scope = symTable_pop(curr_scope);
ast_dump($4, $1->attributes.identifier);
//quads();
	}
        ;

function_specifier
	: declarator { $$ = ast_reverse_tree($1, LEFT); }
        | declaration_specifiers declarator  { 
		struct ast_node *var = $1;
		while(var->type == AST_STORAGE){
			var = var->left;
		}
		ast_push_back(var, $2,LEFT);
		$$ = ast_reverse_tree(var, LEFT);
		if($1->type == AST_STORAGE){
			struct ast_node *tmp = $$->left;
			struct ast_node *tmp2 = $1;
			while(tmp2->left->type == AST_STORAGE)
				tmp2 = tmp2->left;
			tmp2->left = tmp;
			$$->left = $1;
		}
}
        | declarator declaration_list
        | declaration_specifiers declarator declaration_specifiers
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

/* Duplicate function-declarator definition */
/* Duplicate parameter-type-list definition */
/* Duplicate parameter-list definition */
/* Duplicate parameter-declaration definition */
/* Duplicate identifier-list definition */

%%

void insert_symbol(char *s){

	struct symbol *st = sym_new(filename, lineno);
	if(symTable_push(curr_scope, s, st, curr_scope->scope_type) != TRUE){
		st = symTable_getSymbol(curr_scope,s, curr_scope->scope_type);
		fprintf(stderr, "Error: %s previously defined around %s:%d\n", s, st->filename, st->linenumber);
	}
//symTable_print(curr);
//fprintf(stderr, "sym val: %s with %lld\n", s,st->value);
}

int main(int argc, char** argv){
	char *infile;

	if(argc == 2){
        	infile = argv[1];
        	yyin = fopen(infile, "r");
	} 
	else{
        	strcpy(filename,"<stdin>");
        	lineno=1;
        	infile = "<stdin>";
        	yyin = stdin;
	}
	
	curr_scope = symTable_new(FILE_SCOPE, 1, filename, NULL);
	yyparse();
	return 0;
}
