// Eugene Sokolov
// Compilers ECE466
// ast.h

#ifndef _AST_H
#define _AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "def.h"
#include "parser.tab.h"

enum ast_type{
	AST_VAR=0,
	AST_FN,
	AST_STORAGE,
	AST_SCALAR,
	AST_NUM,
	AST_STR,
	AST_CHAR,
	AST_PTR,
	AST_ARY,
	AST_BINOP,
	AST_UNOP,
	AST_ASSGN,
	AST_FNCALL,
	AST_IF,
	AST_DO,
	AST_WHILE,
	AST_FOR,
	AST_SWITCH
};

struct ast_node {
	enum ast_type type;
	struct ast_node *left;
	struct ast_node *right;
	struct ast_node *next;
	struct ast_node *cond;
	struct ast_node *body;
	struct ast_node *other;
	int scope_type;
	struct attributes {
	        int num;
	        int op;
	        char identifier[36];
	        char str[MAX_STRING_LENGTH];
	        struct ast_node *params;
	        int size;
	        enum sign_type num_signed;
	        enum scalar_type scalar_type;
	        enum storage_class storage_class;
	        int ln_effective;
	        char file_name[256];
	} attributes;
};

struct ast_node * ast_newnode(int type);

struct ast_node * ast_reverse_tree(struct ast_node *root, int which);

struct ast_node * ast_pushback(struct ast_node *root, struct ast_node *new_node, int which);

int ast_list_size(struct ast_node *root, int which);

void ast_dump(struct ast_node *root, char *fn_name);

void ast_print_node(struct ast_node *root, int tabs);

void ast_print_tree(struct ast_node *root);

#endif
