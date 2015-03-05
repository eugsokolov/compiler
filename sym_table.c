// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "sym_table.h"

struct sym_table * symTable_new(int st, int line_begin, char *filename, struct sym_table *prev){

	struct sym_table *table;
	if((table = malloc(sizeof(struct sym_table))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
		return NULL;
	}

	table->scope_type = st;
	table->line_begin = line_begin;
	table->filename = strdup(filename);
	table->prev = prev;
	int i=0;
	for(i=0; i<4;i++)
		table->symbols[i] = hashTable_new(50);
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

int symTable_push(struct sym_table *table, char *ident, void *ptr, int scope){

	struct sym_table *st = table;
	while(st != NULL){
		if(hashTable_contains(st->symbols[scope], ident) == TRUE)
			return FALSE;
		st = st->prev;
	}

	if(hashTable_insert(table->symbols[scope], ident, ptr) == TRUE)
		return TRUE;

	return FALSE;
}

struct symbol * symTable_getSymbol(struct sym_table *table, char *symbol, int scope){

	struct sym_table *st = table;
	void *ptr = NULL;
	int b = FALSE;
	while(st->prev != NULL){
		if(hashTable_contains(st->symbols[scope], symbol) == TRUE){
			ptr = hashTable_getPointer(st->symbols[scope], symbol, b);
			return ptr;
		}
		st = st->prev;
	}
	return ptr;
}

void symTable_print(struct sym_table *table){

	printf("\n --- SYM TABLE START ---\n");
	printf("file: %s\t scope: %d\t linebeg: %d\t \n", table->filename, table->scope_type, table->line_begin);
	
	int i=0;
	for(i=0; i<4;i++){
		printf("HASH TABLE NUMBER: %d\n", i);
		hashTable_print(table->symbols[i]);
	}

	printf(" --- SYM TABLE END --- \n");
}
