// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "sym_table.h"


struct sym_table *new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev){

	struct sym_table *table;
	if((table = malloc(sizeof(struct sym_table))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", sterror(errno));
		return NULL;
	}

	table->scope_type = st;
	table->line_begin = line_begin;
	table->filename = strdup(filename);
	table->prev = prev;
	table->symbols = hashTable_new();
	return table;
}

struct sym_table *pop(struct sym_table *table){

	struct sym_table *prev = table->prev;
	return prev;

}

int push(struct sym_table *table, char *symbol, void *ptr){

	struct sym_table st = table;
	while(st != NULL){
		if(st->symbols->hashTable_contains(st->symbols, symbol))
			return FALSE;

	}
	st->symbols->push(st-symbols, symbol, ptr);
	return TRUE;

}

void *get_symbol(struct sym_table *table, char *symbol){

	struct sym_table st = table;
	void *ptr = NULL;
	int b = FALSE;
	
	while(st != NULL){
		ptr = st->symbols->hashTable_getPointer(table, symbol, &b);
		if(b == TRUE) return ptr;
		else st = st->prev;
	}
	return ptr;
}

void print(struct sym_table *table){

	printf("\n --- SYM TABLE START ---");
	printf("file: %s\t scope: %d\t linebeg: %d\t \n", table->filename, table->scope_type, table->line_begin);
	printf("");
	

	printf(" --- SYM TABLE END --- \n");
}
