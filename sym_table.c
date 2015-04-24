// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "def.h"
#include "sym_table.h"

extern int stdebug;

struct sym_table * symTable_new(int st, int line_begin, char *filename, struct sym_table *prev){

	struct sym_table *symtable;
	if((symtable = malloc(sizeof(struct sym_table))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
		return NULL;
	}

	symtable->scope_type = st;
	symtable->line_begin = line_begin;
	symtable->filename = strdup(filename);
	symtable->prev = prev;
	int i=0;
	for(i=0; i<4;i++)
		symtable->symbols[i] = hashTable_new(50);
	return symtable;
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

int symTable_push(struct sym_table *table, char *ident, void *ptr, int namespace){

	if(stdebug)
	fprintf(stderr, "inserting ident:%s into table: %p namespace: %d\n", ident, table, namespace);

	struct sym_table *st = table;
	while(st != NULL){
		if(hashTable_contains(st->symbols[namespace], ident) == TRUE)
			return FALSE;
		st = st->prev;
	}

	if(hashTable_insert(table->symbols[namespace], ident, ptr) == TRUE)
		return TRUE;

	return FALSE;
}

void * symTable_getSymbol(struct sym_table *table, char *symbol, int namespace){

	struct sym_table *st = table;
	void *ptr = NULL;
	int b = FALSE;
	
	while(st != NULL){
		
		if(stdebug){
		fprintf(stderr, "getting sym:%s from table: %p namespace: %d\n", symbol, st, namespace);
		symTable_print(st);		
		}

		if(hashTable_contains(st->symbols[namespace], symbol) == TRUE){
			ptr = hashTable_getPointer(st->symbols[namespace], symbol, b);
		
			if(stdebug)
			fprintf(stderr, "GOT: %p\n", ptr);
			
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
		printf("namespace: %d\n", i);
		hashTable_print(table->symbols[i]);
	}

	printf(" --- SYM TABLE END --- \n");
}
