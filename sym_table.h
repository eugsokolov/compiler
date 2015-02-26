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
#include "esparser.tab.h"

enum scope_type{
	FILE_SCOPE,
	FUNCTION_SCOPE,
	BLOCK_SCOPE,
	PROTO_SCOPE,
};

struct symbol{
	int value;
	char filename[MAX_STRING_LENGTH];
	int linenumber;

} symbol;

struct sym_table{
	struct hashTable *symbols;
	//int scope;	
	int line_begin;
	char *filename;
	struct sym_table *prev;
	enum scope_type scope_type;
} sym_table;

struct sym_table * symTable_new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev);

struct symbol * sym_new(char *filename, int linenumber);

struct sym_table * symTable_pop(struct sym_table *table);

int push(struct sym_table * symTable_table, char *symbol, void *ptr);

struct symbol * symTable_getSymbol(struct sym_table *table, char *symbol);

void symTable_print(struct sym_table *table);

#endif
