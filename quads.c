// Eugene Sokolov
// Compilers ECE466
// quads.c

#include "quads.h"

extern int qdebug;

struct basic_block *current_bb;
struct basic_block_list *fn_bb_list;


void new_quads(){

}

struct quad_list *quads_gen_fn(struct ast_node *ast){


}


struct quad_list *quads_gen_statement(struct ast_node *ast){


}



struct quad_list *quads_gen_assignment(struct ast_node *ast){}
struct quad_list *quads_gen_rval(struct ast_node *ast, struct ast_node *target){}
struct quad_list *quads_gen_lval(struct ast_node *ast, int *direct){}
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
void quads_gen_condexpr(struct ast_node *ast, struct basic_block *true, struct basic_block *false){}


struct quad_list *new_quad_list(){}
struct quad_list *quad_list_cat(struct quad_list *root, struct quad_list *tail){}
struct quad_list *quad_list_push(struct quad_list *root, struct quad *new_quad){}

struct basic_block *new_basic_block(){}
struct basic_block *basic_block_link(struct basic_block *bb){}
struct basic_block_list *new_bb_list(){}
struct basic_block_list *bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb){}

void quads_print(struct quad *q, struct basic_block *bb){}
void quads_print_bb(struct basic_block *bb){}

