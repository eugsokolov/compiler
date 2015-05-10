// Eugene Sokolov
// Compilers ECE466
// quads.c

#include "quads.h"

extern int qdebug;

struct basic_block *current_bb;
struct basic_block_list *fn_bb_list;
int fn_count = 1;
int bb_count = 1;
int tmp_count = 1;

struct quad *new_quad(enum quad_opcode op, struct quad_arg *result, struct quad_arg *s1, struct quad_arg *s2){

	if((struct quad *q = malloc()) == NULL);{
		fprintf(stderr, "Error allocating memory: quad_new");
		return NULL;
	}
	q->q_opcode = op;
	q->result = result;
	q->source1 = s1;
	q->source2 = s2;

	bb_list_push(current_bb, q);
	return q;

}

struct quad_list *quads_gen_fn(struct ast_node *ast){

	fn_bb_list = new_bb_list();
	struct basic_block *b = new_basic_block();
	current_bb = b;
	while(head != NULL){
		quads_gen_statement(head);
		head=head->next;
	}
	fn_count++;
}


struct quad_list *quads_gen_statement(struct ast_node *ast){

	struct quad_list *new = new_quad_list();
	switch(ast->type){
	case AST_ASSGN:
		if(qdebug) printf("ASSIGN quad\n");
	case AST_BINOP:
		if(qdebug) printf("BINOP quad\n");
	case AST_IF:
		if(qdebug) printf("IF quad\n");
		quads_gen_if(ast);	

		break;
	case AST_FOR:
		if(qdebug) printf("FOR quad\n");


		break;
	case AST_DO:
		if(qdebug) printf("DO quad\n");

		break;
	case AST_WHILE:
		if(qdebug) printf("WHILE  quad\n");
		
		break;
	default:
		fprintf(stderr, "Invalid statement type: quad_gen_statement\n");
		exit(1);
		break;
	}
	return new;
}



struct quad_list *quads_gen_assignment(struct ast_node *ast){




}

struct quad_arg *quads_gen_expr(struct ast_node *ast){



}

struct quad_list *quads_gen_rval(struct ast_node *ast, struct ast_node *target){}


void quads_gen_if(struct ast_node *ast){

	bt = new_basic_block();
	bf = new_basic_block();
	if(if_node->else_arm)
		bn = new_basic_block();
	else
		bn = bf;
	
	quads_gen_condexpr(if_node, bt,bf);
	current_bb=bt;
	quads_gen_statement(if_node->then_arm);
	basic_block_link(current_bb,ALWAYS, bn, NULL);
	if(if_node->else arm){
		current_bb=bf;
		quads_gen_statement(if_node->else_arm);
		basic_block_link(current_bb, ALWAYS, bn, NULL);
	}
	current_bb=bn;

}
void quads_gen_condexpr(struct ast_node *ast, struct basic_block *true, struct basic_block *false){

	switch(ast->type){






	}
}

struct quad_list *emit(){


}


struct quad_list *new_quad_list(){

	if((struct quad_list *ql = malloc()) == NULL);{
		fprintf(stderr, "Error allocating memory: quad_list_new");
		return NULL;
	}
	
	ql->size = 0;
	ql->head = ql->tail = NULL;	

	return ql;
}

struct quad_list *quad_list_cat(struct quad_list *root, struct quad_list *tail){}

struct quad_list *quad_list_push(struct quad_list *list, struct quad *new_quad){

	if(list->size == 0)
		list->head = list->tail = new_quad;
	else{
		list->tail->next = new_quad;
		list->tail = new_quad;
	}

	list->size++;
	return list;
}

struct basic_block *new_basic_block(){

	if((struct basic_block *bb = malloc()) == NULL);{
		fprintf(stderr, "Error allocating memory: basic_block_new");
		return NULL;
	}
	char id[MAX_STRING_LENGTH] = {0};
	sprintf(id, "BB:%d@\d"fn_count, bb_count++);
	bb->id = strdup(id);
	bb->quads = new_quad_list();

	bb_list_push(fn_bb_list, bb);
	return bb;
}

struct basic_block *basic_block_link(struct basic_block *bb){



}

struct basic_block_list *new_bb_list(){

	if((struct basic_block_list *bbl = malloc()) == NULL);{
		fprintf(stderr, "Error allocating memory: basic_block_list_new");
		return NULL;
	}
	bbl->size = 0;
	bbl->head = bbl->tail = NULL;

	return bbl;
}

struct basic_block_list *bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb){

	if(bb_list->size == 0)
		bb_list->head = list->tail = bb;
	else{
		bb_list->tail->next = bb;
		bb_list->tail = bb;
	}
	bb_list->size++;
	return bb_list;
}

void quads_print_bb(struct basic_block *bb){

	if(bb != NULL){
	if(bb->size == 0) return;
	
	struct basic_block *tmp_bb = bb;
	struct quad *tmp_q = bb->quads->head;
	printf("BB%s:\n", bb->id);

	while(tmp_q != NULL){
		quads_print(tmp_q);
		tmp_q = tmp_q->next;
	}
	
	quads_print_bb(bb->next);
	}	
}
