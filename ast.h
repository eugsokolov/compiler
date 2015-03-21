// Eugene Sokolov
// Compilers ECE466
// ast.h

#ifndef _AST_H
#define _AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "hash.h"
#include "esparser.tab.h"

#define LEFT 1
#define RIGHT 2
#define NEXT 3

enum ast_type{
	
	AST_VAR=0,
	AST_PTR,
	AST_ARRAY,
	AST_FN,
	AST_TYPEDEF,
	AST_STORAGE,
	AST_SCALAR,
	AST_STRUCT,
	AST_UNION,
	AST_NUM,
	AST_STR,
	AST_CHAR,
	AST_BINOP,
	AST_UNOP,
	AST_ASSGN,
	AST_FNCALL,
	AST_FOR,
	AST_IF,
	AST_WHILE,
	AST_DO,
	AST_SWITCH,
	AST_TMP
};

enum storage_class {
	STORE_AUTO,
	STORE_EXTERN,
	STORE_REGISTER,
	STORE_STATIC
};

enum scalar_type{
	
	SCALAR_INT,
	SCALAR_CHAR,
	SCALAR_DOUBLE
};

struct ast_node{

	enum ast_type type;
	int scope;
	struct ast_node *left;
	struct ast_node *right;
	struct ast_node *next;
	struct ast_node *cond;
	struct ast_node *body;
	struct ast_node *other;
	
	char filename[256];
	char ident[256];
	int op;
	int num_signed;	
	enum storage_class storage_class;
	enum scalar_type scalar_type;

};

struct ast_node * ast_new(int type);

struct ast_node * ast_reversetree(struct ast_node *root, int par);

struct ast_node * ast_pushback(struct ast_node *root, struct ast_node *newnode, int par);

void ast_print(struct ast_node *root);

#endif
