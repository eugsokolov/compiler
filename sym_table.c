// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "sym_table.h"

struct sym_table * symTable_new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev){

	struct sym_table *table;
	if((table = malloc(sizeof(struct sym_table))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
		return NULL;
	}

	table->scope_type = st;
	table->line_begin = line_begin;
	table->filename = strdup(filename);
	table->prev = prev;
	table->symbols = hashTable_new(20);
	return table;
}

struct symbol * sym_new(char *filename, int linenumber){

	struct symbol *s;
	if((s = malloc(sizeof(struct symbol))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
		return NULL;
	}
	strcpy(s->filename, filename);
	s->linenumber = linenumber;
	return s;
}

struct sym_table * symTable_pop(struct sym_table *table){

	struct sym_table *prev = table->prev;
	return table->prev;

}

int symTable_push(struct sym_table *table, char *symbol, void *ptr){

	struct sym_table *st = table;
	while(st != NULL){
		if(hashTable_contains(st->symbols, symbol) == TRUE)
			return FALSE;
		st = st->prev;
	}
	hashTable_insert(table->symbols, symbol, ptr);
	return TRUE;

}

struct symbol * symTable_getSymbol(struct sym_table *table, char *symbol){

	struct sym_table *st = table;
	void *ptr = NULL;
	int b = FALSE;
	
	while(st != NULL){
		ptr = hashTable_getPointer(st->symbols, symbol, b);
		if(b == TRUE) return ptr;
		else st = st->prev;
	}
	return ptr;
}

void symTable_print(struct sym_table *table){

	printf("\n --- SYM TABLE START ---");
	printf("file: %s\t scope: %d\t linebeg: %d\t \n", table->filename, table->scope_type, table->line_begin);
	
	hashTable_print(table->symbols);
	printf("");
	

	printf(" --- SYM TABLE END --- \n");
}
