// Eugene Sokolov
// Compilers ECE466
// quads.h

#ifndef _QUADS_H
#define _QUADS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "def.h"
#include "parser.tab.h"
#include "ast.h"

enum quad_opcode{
	Q_MOV, Q_LOAD, Q_LEA, Q_STORE,
	Q_BR, Q_CMP, Q_BRGT, Q_BRLT, Q_BRGE, Q_BRLE, Q_BREQ, Q_BRNE,
	Q_INC, Q_DEC,
	Q_ADD, Q_SUB, Q_MUL, Q_DIV, Q_MOD,
	Q_AND, Q_XOR, Q_OR, Q_LOGAND, Q_LOGOR,
	Q_NOT, Q_LOGNOT, Q_BITNOT,
	Q_SHL, Q_SHR,
	Q_FUNC_CALL, Q_FUNC_ARG, Q_FUNC_ARG_BEGIN,
	Q_RETURN
};

enum quad_arg_type{
        QA_NONE,
        QA_INT,
        QA_TMP_IDENT,
        QA_IDENT,
        QA_STRING,
        QA_BASIC_BLOCK
};

struct quad{
	//int opcode;
	enum quad_opcode q_opcode;
	struct quad_arg *result, *source1, *source2;
	struct quad *next;
};

struct quad_arg{

	enum quad_arg_type type;
	union{
		int val;
		struct basic_block *bb;

	} data;

};

struct quad_list{
	int size;
	struct quad *head, *tail;
};

struct basic_block{
	char *id;
	struct quad_list *quads;


};

struct basic_block_list{
	int size;
	struct basic_block *head, *tail;
};

struct loop_bb{

};

struct quad *new_quad(enum quad_opcode op, struct quad_arg *result, struct quad_arg *s1, struct quad_arg *s2);
struct quad_list *quads_gen_fn(struct ast_node *ast);
struct quad_list *quads_gen_statement(struct ast_node *ast);
struct quad_list *quads_gen_assignment(struct ast_node *ast);
struct quad_list *quads_gen_rval(struct ast_node *ast, struct ast_node *target);
struct quad_list *quads_gen_lval(struct ast_node *ast, int *direct);
void quads_gen_if(struct ast_node *ast);
void quads_gen_condexpr(struct ast_node *ast, struct basic_block *true, struct basic_block *false);


struct quad_list *new_quad_list();
struct quad_list *quad_list_cat(struct quad_list *root, struct quad_list *tail);
struct quad_list *quad_list_push(struct quad_list *root, struct quad *new_quad);

struct basic_block *new_basic_block();
struct basic_block *basic_block_link(struct basic_block *bb);
struct basic_block_list *new_bb_list();
struct basic_block_list *bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb);

void quads_print(struct quad *q, struct basic_block *bb);
void quads_print_bb(struct basic_block *bb);

#endif
