// Eugene Sokolov
// Compilers ECE466
// target.h

#ifndef _TARGET_H
#define _TARGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "def.h"
#include "ast.h"

#define DIRECT 0
#define INDIRECT 1

enum quad_opcode{
	Q_MOV, Q_LOAD, Q_LEA, Q_STORE,
	Q_BR, Q_CMP, Q_BRGT, Q_BRLT, Q_BRGE, Q_BRLE, Q_BREQ, Q_BRNE,
	Q_INC, Q_DEC,
	Q_ADD, Q_SUB, Q_MUL, Q_DIV, Q_MOD,
	Q_AND, Q_XOR, Q_OR, Q_LOGAND, Q_LOGOR,
	Q_NOT, Q_LOGNOT, Q_BITNOT,
	Q_SHL, Q_SHR,
	Q_FNCALL, Q_FNCALL_ARG,
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

enum branching {
	NEVER,
	ALWAYS,
	COND_LT,
	COND_GT,
	COND_LE,
	COND_GE,
	COND_EQ,
	COND_NE,
	COND_OR,
	COND_AND
};

enum quad_symbol_type {
	QST_SCALAR,
	QST_ARRAY,
	QST_POINTER,
	QST_FUNCTION
};


struct quad{
	//int opcode;
	enum quad_opcode q_opcode;
	struct ast_node *result, *source1, *source2;
	struct quad *next;
};

struct tmp_symbol{
	enum quad_symbol_type qst;
	char *id;
};

struct quad_list{
	int size;
	struct quad *head, *tail;
};

struct basic_block{
	char *id;
	int i;
	char *func;
	struct quad_list *quads;
	struct basic_block *left, *right, *next;
	int branch;

};

struct basic_block_list{
	int size;
	int bbend;
	char *func;
	struct basic_block *head, *tail;
};

struct loop{

	struct loop *previous;
	struct basic_block *b_continue;
	struct basic_block *b_break;
};

//struct quad *emit(enum quad_opcode op, struct quad_arg *result, struct quad_arg *s1, struct quad_arg *s2);
struct quad *emit(enum quad_opcode op, struct ast_node *s1, struct ast_node *s2, struct ast_node *result);
struct ast_node *target_new_tmp();
struct quad_list *target_gen_globl(struct ast_node *ast_fn, struct ast_node *ast);
struct quad_list *target_gen_fn(struct ast_node *ast_fn, struct ast_node *ast);
struct quad_list *target_gen_statement(struct ast_node *ast);
struct ast_node *target_gen_assignment(struct ast_node *ast);
struct ast_node *target_gen_lval(struct ast_node *ast, int *dstmode);
struct ast_node *target_gen_rval(struct ast_node *ast, struct ast_node *target);
int get_pointer(struct ast_node *ast, int deref);
int get_sizeof(struct ast_node *node);
void target_gen_if(struct ast_node *ast);
void target_gen_for(struct ast_node *ast);
void target_gen_condexpr(struct ast_node *ast, struct basic_block *true_b, struct basic_block *false_b);
void target_gen_return(struct ast_node *ast);

struct quad_list *new_quad_list();
struct quad_list *quad_list_cat(struct quad_list *root, struct quad_list *tail);
struct quad_list *target_list_push(struct quad_list *list, struct quad *new_quad);

struct basic_block *new_basic_block();
struct basic_block *basic_block_link(struct basic_block *bb, int branch, struct basic_block *left, struct basic_block *right);
struct basic_block_list *new_bb_list();
struct basic_block_list *bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb);
struct loop *loop_new(struct basic_block *b_continue, struct basic_block *b_break);
struct loop *loop_end();

void target_print_bb(struct basic_block *bb);
void target_print_inst(struct quad *q);
void target_print_vt(struct ast_node *cur);

char *target_id(struct ast_node *ast, char *buffer);
void target_globl(struct ast_node *ast_fn);
void target_print();
int target_print_globl();

#endif
