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
extern char filename[256];
extern FILE *yyin;
int yyerror(const char *p) {fprintf(stderr, "ERROR: unrecognized syntax: %s\n", p);}

int yydebug=0;
int debug=1;
int print_ast=0;
int print_declarations=0;
int print_quads=0;

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



%token <yystring> IDENT
%token <yychar> CHARLIT
%token <yystring> STRING
%token <number.yyint> NUMBER TIMESEQ DIVEQ MODEQ SHLEQ SHREQ ANDEQ OREQ XOREQ PLUSEQ MINUSEQ
%token <number.yyint> INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ LOGAND LOGOR
%token <number.yyint> PREINC POSTINC PREDEC POSTDEC
%token <str> AUTO BREAK CASE CHAR CONST ELLIPSIS
%token <str> CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER
%token <str> RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF TYPEDEF_NAME UNION UNSIGNED
%token <str> VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY

%type <node> declaration declaration_specifiers simple_declarator integer_type_specifier
%type <node> pointer_declarator pointer direct_declarator primary_expression array_declarator
%type <node> logical_or_expression logical_and_expression logical_negation_expression multiplicative_expression additive_expression
%type <node> bitwise_negation_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression
%type <node> shift_expression indirection_expression unary_plus_expression unary_minus_expression postdecrement_expression postincrement_expression
%type <node> preincrement_expression predecrement_expression address_expression constant_expression cast_expression function_declarator
%type <node> character_type_specifier storage_class_specifier type_specifier type_qualifier function_specifier declarator
%type <node> expression parenthesized_expression enumeration_type_specifier floating_point_specifier type_name union_type_specifier void_type_specifier
%type <node> initialized_declarator structure_type_specifier typedef_name bool_type_specifier typedef_definition
%type <node> expression_statement null_statement unary_expression assignment_expression statement postfix_expression subscript_expression
%type <node> initialized_declarator_list function_call sizeof_expression component_selection_expression compound_literal
%type <node> if_statement if_else_statement for_expressions for_statement while_statement do_statement switch_statement initial_clause
%type <node> conditional_expression declaration_or_statement_list declaration_or_statement function_definition function_def_specifier
%type <node> expression_list compound_statement iterative_statement conditional_statement
%type <number.yyint> assignment_operator

%start translation_unit

%% /* Grammar rules and actions follow */


declaration
        : declaration_specifiers initialized_declarator_list ';' 
            {
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

declaration_specifiers
        : storage_class_specifier
        | storage_class_specifier declaration_specifiers { $$ = ast_push_back($1, $2, LEFT); }
        | typedef_definition
        | typedef_definition declaration_specifiers { $$ = ast_push_back($2, $1, LEFT); }
        | type_specifier
        | type_specifier declaration_specifiers { $$ = ast_push_back($2, $1, LEFT); }
        | type_qualifier
        | type_qualifier declaration_specifiers { $$ = $2; }
        | function_specifier
        | function_specifier declaration_specifiers { $$ = $2; }
        ;

function_specifier
        : INLINE { $$ = NULL; }
        ;

initialized_declarator_list
        : initialized_declarator { $$ = $1; }
        | initialized_declarator_list ',' initialized_declarator { $$ = ast_push_back($1,$3,NEXT); }
        ;

initialized_declarator
        : declarator
        | declarator '=' initializer { $$ = $1; }
        ;

storage_class_specifier
        : AUTO { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_AUTO; }
        | EXTERN { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_EXTERN; }
        | REGISTER { $$ = ast_newnode(AST_STORAGE); $$->attributes.storage_class = STORE_REGISTER; }
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
        : IDENT 
            {
                int ret;
                $$ = ast_newnode(AST_VAR);
                $$->scope_type = curr_scope->scope_type;
                strcpy($$->attributes.identifier, yylval.yystring);
                $$->attributes.ln_effective = lineno;
                strcpy($$->attributes.file_name, filename);
                ret = symTable_push(curr_scope, yylval.yystring, $$, NAMESPACE_OTHER);
                if (!ret){
                    fprintf(stderr, "Error: Previous Declaration of Identifier %s - %s: %d\n", yylval.yystring, filename, lineno);
                }
            }
        ;

pointer_declarator
        : pointer direct_declarator {   $$ = ast_push_back($1,$2,LEFT);} 
        ;

type_qualifier_list
        : type_qualifier
        | type_qualifier_list type_qualifier
        ;

array_declarator
        : direct_declarator '[' ']'    {   $$ = ast_newnode(AST_ARRAY);
                                                $$->left = $1;
                                                $$->attributes.size = -1;  } 
        | direct_declarator '[' constant_expression ']'     {   if ($3->type != AST_NUM){
                                                                    ast_print_syntax_error(filename, lineno);
                                                                } else {
                                                                    $$ = ast_newnode(AST_ARRAY);
                                                                    $$->left = $1;
                                                                    $$->attributes.size = $3->attributes.num; } }
        | direct_declarator '[' array_qualifier_list ']'     /*{   $$ = ast_newnode(AST_ARRAY);
                                                                    $$->prev = $1;  }*/
        | direct_declarator '[' array_size_expression ']'     /*{   $$ = ast_newnode(AST_ARRAY);
                                                                    $$->prev = $1;
                                                                    $$->attributes.size = $3;  }*/
        | direct_declarator '[' array_qualifier_list array_size_expression ']'  /*{   $$ = ast_newnode(AST_ARRAY);
                                                                                        $$->prev = $1;
                                                                                        $$->attributes.size = $4;  }*/
        | direct_declarator '[' array_qualifier_list '*' ']'    /*{   $$ = ast_newnode(AST_ARRAY);
                                                                        $$->prev = $1;
                                                                        $$->attributes.size = -1;  }*/
        ;

array_qualifier_list
        : array_qualifier
        | array_qualifier_list array_qualifier
        ;

array_qualifier
        : STATIC
        | RESTRICT
        | CONST
        | VOLATILE
        ;

array_size_expression
        : assignment_expression
        | '*'
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

integer_type_specifier
        : signed_type_specifier { $$ = ast_newnode(AST_SCALAR); 
                                    $$->attributes.num_signed = TYPE_SIGNED;
                                    $$->attributes.scalar_type = SCALAR_INT; }
        | unsigned_type_specifier { $$ = ast_newnode(AST_SCALAR); 
                                        $$->attributes.num_signed = TYPE_UNSIGNED;
                                        $$->attributes.scalar_type = SCALAR_INT; }
        | character_type_specifier 
        | bool_type_specifier { $$ = ast_newnode(AST_SCALAR); 
                                        $$->attributes.num_signed = TYPE_SIGNED;
                                        $$->attributes.scalar_type = SCALAR_INT; }
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

character_type_specifier
        : CHAR { $$ = ast_newnode(AST_SCALAR); 
                                        $$->attributes.num_signed = TYPE_SIGNED;
                                        $$->attributes.scalar_type = SCALAR_CHAR; }
        | SIGNED CHAR { $$ = ast_newnode(AST_SCALAR); 
                                        $$->attributes.num_signed = TYPE_SIGNED;
                                        $$->attributes.scalar_type = SCALAR_CHAR; }
        | UNSIGNED CHAR { $$ = ast_newnode(AST_SCALAR); 
                                        $$->attributes.num_signed = TYPE_UNSIGNED;
                                        $$->attributes.scalar_type = SCALAR_CHAR; }
        ;

floating_point_specifier
        : FLOAT { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
        | DOUBLE { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
        | LONG DOUBLE { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
        | complex_type_specifier { fprintf(stderr, "Warning: This compiler doesn't support floating point types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
        ;

complex_type_specifier
        : FLOAT _COMPLEX
        | DOUBLE _COMPLEX
        | LONG DOUBLE _COMPLEX
        ;

bool_type_specifier
        : _BOOL { $$=NULL; }
        ;

enumeration_type_specifier
        : enumeration_type_definition { fprintf(stderr, "Warning: This compiler doesn't support enum types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
        | enumeration_type_reference { fprintf(stderr, "Warning: This compiler doesn't support enum types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
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
                                                                 filename, lineno);$$ = NULL; }
        | structure_type_reference { fprintf(stderr, "Warning: This compiler doesn't support struct types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
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
                                                                 filename, lineno);$$ = NULL; }
        | union_type_reference { fprintf(stderr, "Warning: This compiler doesn't support union types - %s: %d\n",
                                                                 filename, lineno);$$ = NULL; }
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

void_type_specifier
        : VOID { $$=NULL; }
        ;

typedef_name
        : TYPEDEF_NAME 
            {
                struct ast_node *t;
                t = symTable_getSymbol(curr_scope, yylval.yystring, NAMESPACE_OTHER);
                if (t->left != NULL && t->left->type == AST_TYPEDEF && t->left->left != NULL){
                    $$ = t->left->left;
                } else {
                    fprintf(stderr, "Error: Problem with typedef - %s: %d\n", filename, lineno);
                    $$ = NULL;
                }
            }
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
        |  direct_abstract_declarator '[' expression ']'
        | '[' '*' ']'
        | direct_abstract_declarator '[' '*' ']'
        | '(' ')'
        | direct_abstract_declarator '(' ')'
        | direct_abstract_declarator '(' parameter_type_list ')'
        | '(' parameter_type_list ')'
        ;

primary_expression
        : IDENT
            {
                char *ident = yylval.yystring;
                //ident[yylval.yystring_size] = '\0';
                struct ast_node *var = symTable_getSymbol(curr_scope, ident, NAMESPACE_OTHER);
                $$ = var;
            }
        | NUMBER { $$ = ast_newnode(AST_NUM); $$->attributes.num = yylval.number.yyint; $$->attributes.ln_effective = lineno;}
        | CHARLIT { $$ = ast_newnode(AST_CHAR); $$->attributes.num = (int)(yylval.yychar); $$->attributes.ln_effective = lineno;}
        | STRING { $$ = ast_newnode(AST_STR); strcpy($$->attributes.str, yylval.yystring); $$->attributes.ln_effective = lineno;}
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
        | compound_literal
        ;

subscript_expression
        : postfix_expression '[' expression ']' 
            {
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
        | postfix_expression '(' expression_list ')' 
            {
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

compound_literal
        : '(' type_name ')' '{' initializer_list '}' { $$ = NULL; }
        | '(' type_name ')' '{' initializer_list ',' '}' { $$ = NULL; }
        ;

cast_expression
        : unary_expression
        | '(' type_name ')' cast_expression { ast_print_syntax_error(filename, lineno); $$=NULL; }
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

and_expression
        : equality_expression
        | and_expression '&' equality_expression { $$ = ast_newnode(AST_BINOP); 
                                                            $$->attributes.op = '&'; 
                                                            $$->left=$1; $$->right=$3; }
        ;

exclusive_or_expression
        : and_expression
        | exclusive_or_expression '^' and_expression { $$ = ast_newnode(AST_BINOP); 
                                                            $$->attributes.op = '^'; 
                                                            $$->left=$1; $$->right=$3; }
        ;

inclusive_or_expression
        : exclusive_or_expression
        | inclusive_or_expression '|' exclusive_or_expression { $$ = ast_newnode(AST_BINOP); 
                                                            $$->attributes.op = '|'; 
                                                            $$->left=$1; $$->right=$3; }
        ;

logical_and_expression
        : inclusive_or_expression
        | logical_and_expression LOGAND inclusive_or_expression { $$ = ast_newnode(AST_BINOP); 
                                                            $$->attributes.op = LOGAND; 
                                                            $$->left=$1; $$->right=$3; }
        ;

logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGOR logical_and_expression { $$ = ast_newnode(AST_BINOP); 
                                                            $$->attributes.op = LOGOR; 
                                                            $$->left=$1; $$->right=$3; }
        ;

conditional_expression
        : logical_or_expression
        | logical_or_expression '?' expression ':' conditional_expression { ast_print_syntax_error(filename, lineno); }
        ;

constant_expression
        : conditional_expression
        ;

assignment_expression
        : constant_expression
        | unary_expression assignment_operator assignment_expression
            {
                $$ = ast_newnode(AST_ASSGN);
                $$->left = $1;
                if ($2 == '='){
                    $$->right = $3;
                } else {
                    struct ast_node *right;
                    right = ast_newnode(AST_BINOP);
                    right->left = $1;
                    right->right = $3;
                    switch ($2){
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

statement
        : expression_statement 
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

conditional_statement
        : if_statement
        | if_else_statement
        ;

if_statement
        : IF '(' expression ')' statement
            {
                $$ = ast_newnode(AST_IF);
                $$->cond = $3;
                $$->body = $5;
            }
        ;

if_else_statement
        : IF '(' expression ')' statement ELSE statement
            {
                $$ = ast_newnode(AST_IF);
                $$->cond = $3;
                $$->body = $5;
                $$->other = $7;
            }
        ;

iterative_statement
        : do_statement
        | while_statement
        | for_statement
        ;

do_statement
        : DO statement WHILE '(' expression ')' ';'
            {
                $$ = ast_newnode(AST_DO);
                $$->cond = $5;
                $$->body = $2;
            }
        ;

while_statement
        : WHILE '(' expression ')' statement
            {
                $$ = ast_newnode(AST_WHILE);
                $$->cond = $3;
                $$->body = $5;
            }
        ;

for_statement
        : FOR for_expressions statement { $$ = $2; $$->body = $3; }
        ;

for_expressions
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
        : SWITCH '(' expression ')' statement
            {
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

translation_unit
        : top_level_declaration
        | translation_unit top_level_declaration
        ;

top_level_declaration
        : declaration
        | function_definition
        ;

function_definition
        : function_def_specifier '{' { curr_scope = symTable_new(FUNCTION_SCOPE, lineno, filename, curr_scope); } 
            declaration_or_statement_list '}' 
                { 
                    curr_scope = symTable_pop(curr_scope);
                    if (print_ast) ast_dump($4, $1->attributes.identifier);
                    //quads_generate_function($1, $4);
                }
        ;

function_def_specifier
        : declarator { $$ = ast_reverse_tree($1, LEFT); }
        | declaration_specifiers declarator 
            { 
                struct ast_node *var_type = $1;
                while (var_type->type == AST_STORAGE){
                    var_type = var_type->left;
                }
                ast_push_back(var_type, $2,LEFT);
                $$ = ast_reverse_tree(var_type, LEFT);
                if ($1->type == AST_STORAGE){
                    struct ast_node *tmp = $$->left;
                    struct ast_node *this = $1;
                    while (this->left->type == AST_STORAGE){
                        this = this->left;
                    }
                    this->left = tmp;
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

function_declarator
        : direct_declarator '(' parameter_type_list ')' { fprintf(stderr, "Warning: This compiler doesn't support function prototypes - %s: %d\n",
                                                                 filename, lineno);$$ = ast_newnode(AST_FN); ast_push_back($$,$1,LEFT); }
        | direct_declarator '(' ')' { $$ = ast_newnode(AST_FN); ast_push_back($$,$1,LEFT); }
        | direct_declarator '(' identifier_list ')' { fprintf(stderr, "Warning: This compiler doesn't support function arguments - %s: %d\n",
                                                                filename, lineno);$$ = ast_newnode(AST_FN); ast_push_back($$,$1,LEFT); }
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

%%

int main(int argc, char** argv){
    char *infile;
    int c;
    
    while ((c=getopt(argc, argv, "dazq")) != -1){
        switch(c){
            case 'z':
                debug = 1;
                break;
            case 'a':
                print_ast = 1;
                break;
            case 'd':
                print_declarations = 1;
                break;
            case 'q':
                print_quads = 1;
                break;
            default:
                fprintf(stderr, "invalid argument: %c\n", c);
                break;
        }

    }
    if (optind != argc){
        infile = argv[optind];
        yyin = fopen(argv[optind], "r");
    } else {
        strcpy(filename, "<stdin>");
        lineno=1;
        infile = "<stdin>";
        yyin = stdin;
    }
    curr_scope = symTable_new(FILE_SCOPE, 1, filename, NULL);
    yyparse();
    return 0;
}

