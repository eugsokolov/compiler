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

struct quad{
	//int opcode;
	enum quad_opcode q_opcode;
	struct quad_arg *target, *left, *right;
	struct quad *next;
};

struct quad_list{
	int size;
	struct quad *head, *tail;
};

struct basic_block{

	char *id;
	struct quad_list *quads;
	struct basic_block *left, *right, *next;
	int fn_count, bb_count;
};

struct basic_block_list{


};




#endif
