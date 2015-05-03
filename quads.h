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

struct quad{
	int opcode;
	struct ast_node *target, *left, *right;
	struct quad *next;
};

struct quad_list{
	int size;
	struct quad *head, *tail;
};






#endif
