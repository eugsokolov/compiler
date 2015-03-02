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

#define MAX_STRING_LENGTH 4096 

/*
enum number_type{
        TYPE_INT,
        TYPE_LONG,
        TYPE_LONGLONG,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_LONGDOUBLE,
        TYPE_UNSIGNED,
        TYPE_SIGNED
};
*/

enum scope_type{
	FILE_SCOPE,
	FUNCTION_SCOPE,
	BLOCK_SCOPE,
	PROTOTYPE_SCOPE,
};

struct symbol{
	long long value;
	char filename[MAX_STRING_LENGTH];
	int linenumber;

};

struct sym_table{
	struct hashTable *symbols;
	//int scope;	
	int line_begin;
	char *filename;
	struct sym_table *prev;
	enum scope_type scope_type;
};

struct sym_table * symTable_new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev);

struct symbol * sym_new(char *filename, int linenumber);

struct sym_table * symTable_pop(struct sym_table *table);

int push(struct sym_table * symTable_table, char *symbol, void *ptr);

struct symbol * symTable_getSymbol(struct sym_table *table, char *symbol);

void symTable_print(struct sym_table *table);

#endif
