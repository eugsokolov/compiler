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

struct quad *emit(enum quad_opcode op, struct ast_node *s1, struct ast_node *s2, struct ast_node *result){

	struct quad *q = malloc(sizeof(struct quad));
	if(q == NULL){
		fprintf(stderr, "Error allocating memory: quad_new\n");
		return NULL;
	}
	q->q_opcode = op;
	q->result = result;
	q->source1 = s1;
	q->source2 = s2;

	quad_list_push(current_bb->quads, q);
	return q;

}

struct ast_node * quads_new_tmp(){

	tmp_count++;
	struct ast_node *tmp = ast_newnode(AST_TMP);
	tmp->attributes.num = tmp_count;
	return tmp;
}

struct quad_list *quads_gen_fn(struct ast_node *ast_fn, struct ast_node *ast){

	if(ast_fn->type != AST_VAR || ast_fn->left->type != AST_FN)
		fprintf(stderr, "Error: quads_gen_fn\n");
	
	fn_bb_list = new_bb_list();
	struct basic_block *bb = new_basic_block();
	current_bb = bb;
	
	printf("%s:\n", ast_fn->attributes.identifier);

	while(ast != NULL){
		quads_gen_statement(ast);
		ast=ast->next;
	}
	
	quads_print_bb(current_bb);
	fn_count++;
}


struct quad_list *quads_gen_statement(struct ast_node *ast){

printf("ast type:%d\n", ast->type);
	struct quad_list *new = new_quad_list();
	switch(ast->type){
	case AST_ASSGN:
		if(qdebug) printf("ASSIGN quad\n");
		quads_gen_assignment(ast);
	break;
	case AST_IF:
		if(qdebug) printf("IF quad\n");
		quads_gen_if(ast);	
	break;
	case AST_FOR:
		if(qdebug) printf("FOR quad\n");
		quads_gen_for(ast);
	break;
	case AST_DO:
		if(qdebug) printf("DO quad\n");
		
	break;
	case AST_WHILE:
		if(qdebug) printf("WHILE  quad\n");
		
	break;
	case AST_BINOP:
		if(qdebug) printf("BINOP  quad\n");
	break;
/*	default:
		fprintf(stderr, "Invalid statement type: quad_gen_statement\n");
		exit(1);
		break;
*/	}
	
	return new;
}



struct ast_node *quads_gen_assignment(struct ast_node *ast){

	struct ast_node *tmp, *dest;
	int dstmode;
	dest = quads_gen_lval(ast->left, &dstmode);

	if(dest == NULL){
		fprintf(stderr, "Error: quads_gen_assigment: LHS invalid");
	}	
	if(dstmode == DIRECT){
		tmp = quads_gen_rval(ast->right, dest);
		emit(Q_MOV, tmp, NULL, dest);
	}
	else{
		tmp = quads_gen_rval(ast->right, NULL);
		emit(Q_STORE, tmp, NULL, dest);
	}
	return dest;
}

struct ast_node *quads_gen_rval(struct ast_node *ast, struct ast_node *target){

	struct ast_node *tmp;
	int left, right;
	switch(ast->type){
	case AST_VAR:
		return ast;
	break;
	case AST_NUM:
	case AST_CHAR:
	case AST_STR:
		return ast;
	break;
	case AST_BINOP:
/*
		left = quads_gen_lval(ast->left, NULL);
		right = quads_gen_rval(ast->right, NULL);
		if(!target)
			target = quads_new_tmp();
		emit(ast->attributes.op, left, right, target);
		return target;	
*/
	break;
	}
}

struct ast_node *quads_gen_lval(struct ast_node *ast, int *dstmode){

	switch(ast->type){
	case AST_VAR:
		if(ast->left != NULL && ast->left->type == AST_SCALAR)
		*dstmode = DIRECT;
		return ast;
	break;
	case AST_NUM:
	case AST_CHAR:
	case AST_STR:
		return NULL;
	case AST_UNOP:
        if(ast->attributes.op != '*') 
	break;
	}
}

void quads_gen_if(struct ast_node *ast){

	struct basic_block *bt, *bf, *bn;
	bt = new_basic_block();
	bf = new_basic_block();
	if(ast->next != NULL)
		bn = new_basic_block();
	else
		bn = bf;
	
	quads_gen_condexpr(ast->cond, bt, bf);
	current_bb=bt;
	quads_gen_statement(ast->body);
	basic_block_link(current_bb, ALWAYS, bn, NULL);
	if(ast->next != NULL){
		current_bb=bf;
		quads_gen_statement(ast->next);
		basic_block_link(current_bb, ALWAYS, bn, NULL);
	}
	current_bb=bn;

}

void quads_gen_for(struct ast_node *ast){
        




}

void quads_gen_condexpr(struct ast_node *ast, struct basic_block *true, struct basic_block *false){

	switch(ast->type){






	}
}


struct quad_list *new_quad_list(){

	struct quad_list *ql = malloc(sizeof(struct quad_list));
	if(ql == NULL){
		fprintf(stderr, "Error allocating memory: quad_list_new\n");
		return NULL;
	}
	
	ql->size = 0;
	ql->head = ql->tail = NULL;	

	return ql;
}

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

	struct basic_block *bb = malloc(sizeof(struct basic_block));
	if(bb == NULL){
		fprintf(stderr, "Error allocating memory: basic_block_new\n");
		return NULL;
	}

	char id[MAX_STRING_LENGTH] = {0};
	sprintf(id, "BB:%d@%d",fn_count, bb_count++);
	bb->id = strdup(id);
	bb->quads = new_quad_list();

	bb_list_push(fn_bb_list, bb);
	return bb;
}

struct basic_block *basic_block_link(struct basic_block *bb, int branch, struct basic_block *left, struct basic_block *right){

	bb->branch = branch;
	bb->left = left;
	bb->right = right;
}

struct basic_block_list *new_bb_list(){

	struct basic_block_list *bbl;
	
	if((bbl=malloc(sizeof(struct basic_block_list))) == NULL){
		fprintf(stderr, "Error allocating memory: basic_block_list_new: %s\n", strerror(errno));
		return NULL;
	}
	bbl->size = 0;
	bbl->head = bbl->tail = NULL;

	return bbl;
}

struct basic_block_list *bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb){

	if(bb_list->size == 0)
		bb_list->head = bb_list->tail = bb;
	else{
		bb_list->tail->next = bb;
		bb_list->tail = bb;
	}
	bb_list->size++;
	return bb_list;
}

void quad_print(struct quad *q){


}

void quads_print_bb(struct basic_block *bb){
printf("addr %p\n", bb);
	if(!bb){
		fprintf(stderr, "Error: BB:%s empty in quads_print_bb\n", bb->id);	
		return;
	}	
	else{
	
	struct basic_block *tmp_bb = bb;
	struct quad *tmp_q = bb->quads->head;
	printf("%s #\n", bb->id);

	while(tmp_q != NULL){
printf("q: %p\n", tmp_q);
		quads_print_inst(tmp_q);
		tmp_q = tmp_q->next;
	}
	
	quads_print_bb(bb->next);
	}
}

void quads_print_inst(struct quad *q){

printf("q: %p\n", q);

	if(q){
	if(q->result){
		if(q->result->type == AST_TMP)
		printf("\t \%%T%05d\t=\t", q->result->attributes.num);
		
		else if(q->result->type == AST_VAR)
		printf("\t %s\t=\t", q->result->attributes.identifier);
	}
	else
		printf("\t\t");

	switch(q->q_opcode){
	case Q_LEA:
		printf("LEA \t%s\n",q->source1->attributes.identifier );
		break;
	case Q_STORE:
		printf("STORE \t%s , %s\n", q->source1->attributes.identifier, q->source2->attributes.identifier);
		break;
	case Q_MOV:
		printf("MOV \t%d\n",q->source1->attributes.num );
		break;
	case Q_CMP:
		printf("CMP \n" );
		break;

	case Q_LOAD:
		printf("LOAD \n" );
		break;


	}
	}
	else
	printf("Error: quad null\n");
}
