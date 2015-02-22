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

enum scope_type{
	FILE_SCOPE,
	FUNCTION_SCOPE,
	BLOCK_SCOPE,
	PROTO_SCOPE,
};

struct sym_table{
	struct hashTable *symbols[4];
	//int scope;	
	int line_begin;
	char filename[256];
	struct sym_table *prev;
	enum scope_type scope_type;
} sym_table;

struct sym_table *new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev);

struct sym_table *pop(struct sym_table *table);

int push(struct sym_table *table, char *symbol, void *ptr);

void *get_symbol(struct sym_table *table, char *symbol);

void print(struct sym_table *table);

#endif
