// Eugene Sokolov
// Compilers ECE466
// symboltable.c

#include "sym_table.h"


struct sym_table *new(int scope, int line_begin, char *filename, struct sym_table *prev){



}

struct sym_table *pop(struct sym_table *cur){


}

int push(struct sym_table *cur, char *ident, void *ptr, int namesp){



}

void *get_ident(struct sym_table *cur, char *ident, int namesp){


}
