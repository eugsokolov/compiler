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

enum ast_type{
	AST_VAR=0,	
	AST_FN,		//1
	AST_STORAGE,	//2
	AST_SCALAR,	//3
	AST_NUM,	//4
	AST_STR,	//5
	AST_CHAR,	//6
	AST_PTR,	//7
	AST_ARY,	//8
	AST_BINOP,	//9
	AST_UNOP,	//10
	AST_ASSGN,	//11
	AST_FNCALL,	//12
	AST_IF,		//13
	AST_DO,		//14
	AST_WHILE,	//15
	AST_FOR,	//16
	AST_SWITCH,	//17
	AST_TMP,	//18
	AST_IF_E	//19
};

struct ast_node {
	enum ast_type type;
	struct ast_node *left;
	struct ast_node *right;
	struct ast_node *next;
	struct ast_node *cond;
	struct ast_node *body;
	struct attributes {
	        char filename[128];
	        int linestart;
	        char identifier[128];
	        char str[MAX_STRING_LENGTH];
	        
		int num;
	        enum sign_type num_signed;
	        enum scalar_type scalar_type;
	        enum storage_class storage_class;
	        
		int ary;
		int op;
	} attributes;
};

struct ast_node * ast_newnode(int type);

struct ast_node * ast_reverse_tree(struct ast_node *root, int dir);

struct ast_node * ast_push_back(struct ast_node *root, struct ast_node *new_node, int dir);

int ast_list_size(struct ast_node *root, int dir);

void ast_dump(struct ast_node *root, char *fn_name);

void ast_print_node(struct ast_node *root);

void ast_print_tree(struct ast_node *root);

#endif
