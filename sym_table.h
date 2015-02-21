// Eugene Sokolov
// Compilers ECE466
// symboltable.h

#ifndef _SYM_TABLE_H
#define _SYM_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "hash.h"

struct sym_table{
	struct hashTable *symbols[4];
	int scope;	
	int line_begin;
	char filename[256];
	struct sym_table *prev;
};

struct sym_table *new(int scope, int line_begin, char *filename, struct sym_table *prev);

struct sym_table *pop(struct sym_table *cur);

int push(struct sym_table *cur, char *ident, void *ptr, int namesp);

void *get_ident(struct sym_table *cur, char *ident, int namesp);

#endif
