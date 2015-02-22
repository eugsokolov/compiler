// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "sym_table.h"


struct sym_table *new(enum scope_type st, int line_begin, char *filename, struct sym_table *prev){



}

struct sym_table *pop(struct sym_table *table){


}

int push(struct sym_table *table, char *symbol, void *ptr){



}

void *get_symbol(struct sym_table *table, char *symbol){

	void *ptr = NULL;


	return ptr;
}


void print(struct sym_table *table){

	printf("\n --- SYM TABLE START ---");
	printf("file: %s\t scope: %d\t linebeg: %d\t \n", table->filename, table->scope_type, table->line_begin);
	printf("");
	

	printf(" --- SYM TABLE END --- \n");
}
