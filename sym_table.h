// Eugene Sokolov
// Compilers ECE466
// symboltable.h

#ifndef _SYM_TABLE_H
#define _SYM_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "def.h"
#include "hash.h"

struct symbol{
	long long value;
	char filename[MAX_STRING_LENGTH];
	int linenumber;

};

struct sym_table{
	struct hashTable *symbols[4];
	int scope_type;	
	int line_begin;
	char *filename;
//	char filename[MAX_STRING_LENGTH];
	struct sym_table *prev;
};

struct sym_table * symTable_new(int st, int line_begin, char *filename, struct sym_table *prev);

struct symbol * sym_new(char *filename, int linenumber);

struct sym_table * symTable_pop(struct sym_table *table);

int push(struct sym_table * symTable_table, char *symbol, void *ptr, int scope);

void * symTable_getSymbol(struct sym_table *table, char *symbol, int scope);

void symTable_print(struct sym_table *table);

#endif
