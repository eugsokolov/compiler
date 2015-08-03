// Eugene Sokolov
// Compilers ECE466
// quads.c

#include "quads.h"
#include "parser.tab.h"

extern int qdebug;

struct basic_block *current_bb;
struct basic_block_list *fn_bb_list;
int q_fn_count = 1;
int q_bb_count = 1;
int q_tmp_count = 1;
struct loop *current_l;

struct quad *quad_emit(enum quad_opcode op, struct ast_node *s1, struct ast_node *s2, struct ast_node *result){

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

	q_tmp_count++;
	struct ast_node *tmp = ast_newnode(AST_TMP);
	tmp->type = AST_TMP;
	tmp->attributes.num = q_tmp_count;

	if(qdebug) printf("Generating TMP T:%d\n", tmp->attributes.num);

	return tmp;
}

struct quad_list *quads_gen_fn(struct ast_node *ast_fn, struct ast_node *ast){

	if(ast_fn->type != AST_VAR || ast_fn->left->type != AST_FN){
		fprintf(stderr, "Error: quads_gen_fn\n");
		return NULL;
	}
		
	fn_bb_list = quad_new_bb_list();
	struct basic_block *bb = quad_new_basic_block();
	current_bb = bb;
	
	printf("%s:\n", ast_fn->attributes.identifier);
	bb->func = strdup(ast_fn->attributes.identifier);
//	printf("%s:\n", bb->func);

	while(ast != NULL){
		quads_gen_statement(ast);
		ast=ast->next;
	}
	
	quads_print_bb(bb);
	q_fn_count++;
}

struct quad_list *quads_gen_fncall(struct ast_node *ast){

	struct ast_node *arg = ast->right;
	if(arg != NULL){
		while(arg != NULL){
			quad_emit(Q_FNCALL, arg, NULL, NULL);
			arg = arg->next;
		}
	}
// ADDDED HERE
	return NULL;
}

struct quad_list *quads_gen_statement(struct ast_node *ast){

	if(qdebug) printf("generate statement type: %d\n", ast->type);

	struct quad_list *new = quad_new_quad_list();
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
	case AST_FN:
		if(qdebug) printf("FN  quad\n");
		quads_gen_fn(ast, ast->right);
	break;
	case AST_FNCALL:
		if(qdebug) printf("FNCALL  quad\n");
		quads_gen_fncall(ast);
	break;
	case AST_BINOP:
		if(qdebug) printf("BINOP quad\n");
		quad_emit(ast->attributes.op,ast->right,ast->left,NULL);
	break;
	case AST_UNOP:
		if(qdebug) printf("UNOP  quad\n");
		quad_emit(Q_INC,ast,NULL,NULL);
	break;

	case AST_VAR: break;
	case AST_RET:
	//ADDED HERE
	printf("RETURN \n");
	break;
	default:
		fprintf(stderr, "Invalid statement type: quad_gen_statement\n");
		break;
	}
	
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
		if(ast->right->type == AST_BINOP){
		tmp = quads_gen_rval(ast->right, dest);
		}
		else{
		tmp = quads_gen_rval(ast->right, dest);
		quad_emit(Q_MOV, tmp, NULL, dest);
		}
	}
	else{
		tmp = quads_gen_rval(ast->right, NULL);
		quad_emit(Q_STORE, tmp, NULL, dest);
	}
	return dest;
}

struct ast_node *quads_gen_rval(struct ast_node *ast, struct ast_node *target){

	struct ast_node *tmp, *left, *right;
	struct ast_node *n1, *n2;
	int ptr_left, ptr_right;
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

		if(qdebug) printf("Found binary op\n");
            
		ptr_left = quad_get_pointer(ast->left, 0);
		ptr_right = quad_get_pointer(ast->right, 0);
                
		if(ptr_left){
		        if (ast->attributes.op != '-' && ast->attributes.op != '+')
			fprintf(stderr, "Invalid operation on pointer arithmetic\n");
		        
		        left = quads_gen_rval(ast->left, NULL);
		        tmp = quads_gen_rval(ast->right, NULL);
		        n1 = ast_newnode(AST_BINOP);
		        n1->attributes.op = '*';
		        n1->left = tmp;
		        n2 = ast_newnode(AST_NUM);
		        n2->attributes.num = ptr_left;
		        n1->right = n2;
		        right = quads_gen_rval(n1, NULL);
		}
		else if(ptr_right){
		        if (ast->attributes.op != '-' && ast->attributes.op != '+')
			fprintf(stderr, "Invalid operation on pointer arithmetic\n");
		        
		        right = quads_gen_rval(ast->right, NULL);
		        tmp = quads_gen_rval(ast->left, NULL);
		        n1 = ast_newnode(AST_BINOP);
		        n1->attributes.op = '*';
		        n1->right = tmp;
		        n2 = ast_newnode(AST_NUM);
		        n2->attributes.num = ptr_right;
		        n1->left = n2;
		        left = quads_gen_rval(n1, NULL);
		}
		else{
		        left = quads_gen_rval(ast->left, NULL);
		        right = quads_gen_rval(ast->right, NULL);
		}

		if (target == NULL) 
			target = quads_new_tmp();

		quad_emit(ast->attributes.op, left, right, target);
		return target;
        break;
	default:
		return NULL;
	}
}

int quad_get_pointer(struct ast_node *node, int deref){

	struct ast_node *size_node = node;
	int r=0,l=0,i=0;
	
	if(node->type == AST_UNOP)
		return quad_get_pointer(node->left, deref+1);
	else if(node->type == AST_BINOP){
		l = quad_get_pointer(node->left, deref);
		r = quad_get_pointer(node->right, deref);
		if(l) return l;
		else if(r) return r;
		else if (node->type == AST_VAR && node->left && (node->left->type == AST_PTR || node->left->type == AST_ARY)){
 			while (i++ < deref){
			if(qdebug) printf("pointer deref\n");
			size_node = node->left;
			}
			return quad_get_sizeof(size_node->left->left);
		}	
	}
	else 
		return 0;
}

int quad_get_sizeof(struct ast_node *node){

	if(node->type == AST_SCALAR){
		if(node->attributes.scalar_type == SCALAR_CHAR)
			return 1;
		else
			return 4;
        }
	else if(node->type == AST_PTR)
		return 8;
	else if(node->type == AST_UNOP){
		if(node->attributes.op = '&')
			return 8;
	}
	else if(node->type == AST_VAR)
		return quad_get_sizeof(node->left);
	
	return 0;
}

struct ast_node *quads_gen_lval(struct ast_node *ast, int *dstmode){

	switch(ast->type){
	case AST_VAR:
	        if(ast->left != NULL && ast->left->type == AST_SCALAR)
                *dstmode = DIRECT;
                if(qdebug) printf("lval pointer: direct access\n");
                
                return ast;
            break;
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
	bt = quad_new_basic_block();
	bf = quad_new_basic_block();
	if(ast->next != NULL)
		bn = quad_new_basic_block();
	else
		bn = bf;
	
	quads_gen_condexpr(ast->cond, bt, bf);
	current_bb=bt;
	quads_gen_statement(ast->body);
	quad_basic_block_link(current_bb, ALWAYS, bn, NULL);
	if(ast->next != NULL){
		current_bb=bf;
		quads_gen_statement(ast->next);
		quad_basic_block_link(current_bb, ALWAYS, bn, NULL);
	}
	current_bb=bn;
printf("GEN IF\n");
}

void quads_gen_for(struct ast_node *ast){
        
	struct basic_block *b_cond = quad_new_basic_block();
	struct basic_block *b_body = quad_new_basic_block();
	struct basic_block *b_inc = quad_new_basic_block();
	struct basic_block *b_next = quad_new_basic_block();

	quads_gen_assignment(ast->left);
	quad_loop_new(b_inc, b_next);
	quad_basic_block_link(current_bb, ALWAYS, b_cond, NULL);
	current_bb = b_cond;
	quads_gen_condexpr(ast->cond, b_body, b_next);
	current_bb = b_body;
	quads_gen_statement(ast->body);
	quad_basic_block_link(current_bb, ALWAYS, b_inc, NULL);
	current_bb = b_inc;
	quads_gen_statement(ast->right);
	quad_basic_block_link(current_bb, ALWAYS, b_cond, NULL);
	current_bb = b_next;	
	quad_loop_end();

}

void quads_gen_condexpr(struct ast_node *ast, struct basic_block *true_b, struct basic_block *false_b){

	struct ast_node *left, *right, *tmp1, *tmp2;
	switch(ast->type){
		case AST_VAR:
		tmp1 = quads_gen_rval(ast, NULL);
		tmp2 = ast_newnode(AST_NUM);
		tmp2->attributes.num = 0;
		quad_emit(Q_CMP, tmp1, tmp2, NULL);
		quad_basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_NUM:
		case AST_CHAR:
		tmp2 = ast_newnode(AST_NUM);
		tmp2->attributes.num = 0;
		quad_emit(Q_CMP, ast, tmp2, NULL);
		quad_basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_STR:
		quad_basic_block_link(current_bb, ALWAYS, true_b, false_b);
		break;
		case AST_BINOP:
		switch (ast->attributes.op){
			case '<':
			case '>':
			case EQEQ:
			case NOTEQ:
				left = quads_gen_rval(ast->left, NULL);
				right = quads_gen_rval(ast->right, NULL);
				quad_emit(Q_CMP, left, right, NULL);
				quad_basic_block_link(current_bb, COND_LT, true_b, false_b);
				break;
			default:
				left = quads_gen_rval(ast, NULL);
				right = ast_newnode(AST_NUM);
				right->attributes.num=0;
				quad_emit(Q_CMP, left, right, NULL);
				quad_basic_block_link(current_bb, COND_NE, true_b, false_b);
		}
		break;
		case AST_UNOP:
		left = quads_gen_rval(ast, NULL);
		right = ast_newnode(AST_NUM);
		right->attributes.num = 0;
		quad_emit(Q_CMP, left, right, NULL);
		quad_basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_ASSGN:
		left = quads_gen_assignment(ast);
		right = ast_newnode(AST_NUM);
		right->attributes.num = 0;
		quad_emit(Q_CMP, left, right, NULL);
		quad_basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
	}
		
}

struct loop *quad_loop_new(struct basic_block *b_continue, struct basic_block *b_break){

	struct loop *l = malloc(sizeof(struct loop));
	if(l == NULL)
		fprintf(stderr, "Error creating loop struct\n");

	l->b_continue = b_continue;
	l->b_break = b_break;
	l->previous = current_l;
	current_l = l;
	return l;

}

struct loop *quad_loop_end(){
	struct loop *l = current_l;
	current_l = current_l->previous;
	free(l);
}

struct quad_list *quad_new_quad_list(){

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

struct basic_block *quad_new_basic_block(){

	struct basic_block *bb = malloc(sizeof(struct basic_block));
	if(bb == NULL){
		fprintf(stderr, "Error allocating memory: basic_block_new\n");
		return NULL;
	}

	char id[MAX_STRING_LENGTH] = {0};
	sprintf(id, "BB:%d@%d",q_fn_count, q_bb_count++);
	bb->id = strdup(id);
	bb->quads = quad_new_quad_list();

	quad_bb_list_push(fn_bb_list, bb);
	return bb;
}

struct basic_block *quad_basic_block_link(struct basic_block *bb, int branch, struct basic_block *left, struct basic_block *right){

	bb->branch = branch;
	bb->left = left;
	bb->right = right;

	if(qdebug){
		printf("BB Linked .BB%s to ",bb->id);
		if(left)
			printf("(L) BB%s", bb->left->id);
		if(right)
			printf(" (R) BB%s", bb->right->id);
		printf(" as: %d\n", bb->branch);
	}
}

struct basic_block_list *quad_new_bb_list(){

	struct basic_block_list *bbl;
	
	if((bbl=malloc(sizeof(struct basic_block_list))) == NULL){
		fprintf(stderr, "Error allocating memory: basic_block_list_new: %s\n", strerror(errno));
		return NULL;
	}
	bbl->size = 0;
	bbl->head = bbl->tail = NULL;

	return bbl;
}

struct basic_block_list *quad_bb_list_push(struct basic_block_list *bb_list, struct basic_block *bb){

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
/*
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
*/

	if (bb != NULL){
		struct basic_block *cur_bb = bb;
		struct quad *cur = bb->quads->head;
		printf("$%s\n", bb->id);
		while (cur != NULL){
		quads_print_inst(cur);
		cur = cur->next;
		}

		switch (bb->branch){
		case NEVER:
			break;
		case ALWAYS:
			printf("\t\t\tBR\t %s\n", bb->left->id);
			break;
		case COND_LT:
			printf("\t\t\tBRLT\t %s %s\n",bb->left->id, bb->right->id); 
			break;
		case COND_GT:
			printf("\t\t\tBRGT\t %s %s\n",bb->left->id, bb->right->id); 
			break;
		case COND_LE:
			printf("\t\t\tBRLE\t %s %s\n",bb->left->id , bb->right->id); 
			break;
		case COND_GE:
			printf("\t\t\tBRGE\t %s %s\n",bb->left->id , bb->right->id); 
			break;
		case COND_EQ:
			printf("\t\t\tBREQ\t %s %s\n",bb->left->id , bb->right->id); 
			break;
		case COND_NE:
			printf("\t\t\tBRNE\t %s %s\n",bb->left->id , bb->right->id); 
			break;
		}
		quads_print_bb(bb->next);
	}
}

void quads_print_inst(struct quad *q){

	if(q){
	if(q->result){
		if(q->result->type == AST_TMP)
		printf("\t \%%T%05d\t=\t", q->result->attributes.num);
		
		else if(q->result->type == AST_VAR)
		printf("\t %s\t=\t", q->result->attributes.identifier);
	}
	else
		printf("\t");

	switch(q->q_opcode){
	case Q_RETURN:
		printf("RET\n");
	case Q_LEA:
		printf("LEA \t%s\n",q->source1->attributes.identifier );
		break;
	case Q_STORE:
		printf("STORE \t%s , %s\n", q->source1->attributes.identifier, q->source2->attributes.identifier);
		break;
	case Q_MOV:
		if(q->source1->type == AST_TMP)
		printf("MOV \t@T%d\n",q->source1->attributes.num );
		else	
		printf("MOV \t%d\n",q->source1->attributes.num );
		break;
	case Q_CMP:
		printf("\tCMP \t");
		if (q->source1->type == AST_NUM || q->source1->type == AST_CHAR)
			printf("%d", q->source1->attributes.num);
		else 
			quads_print_vt(q->source1);
		
		printf(",");
		if(q->source2->type == AST_NUM || q->source2->type == AST_CHAR)
			printf("%d", q->source2->attributes.num);
		else
			quads_print_vt(q->source2);
		
		printf("\n");
		break;

	case Q_LOAD:
		printf("LOAD \n" );
		if(q->source1->type == AST_TMP)
			printf("LOAD\t[%%T%05d]\n", q->source1->attributes.num);
		else 
			printf("LOAD\t%s\n", q->source1->attributes.identifier);
		break;

	case Q_FNCALL:
		printf("FNCALL QUAD\n");
		break;
	case Q_INC:
		printf("%s\t = \t ADD %s,1\n",q->source1->left->attributes.identifier,
						q->source1->left->attributes.identifier);
		break;

	case '-':
		printf("SUB ");
		if(q->source1->attributes.identifier) printf("%s",q->source1->attributes.identifier);
		if(q->source1->attributes.num) printf("%d",q->source1->attributes.num);
		printf(",");
		if(q->source2->attributes.identifier) printf("%s",q->source2->attributes.identifier);
		if(q->source2->attributes.num) printf("%d",q->source2->attributes.num);
		printf("\n");
		break;			
	case '+':
		printf("ADD ");
		if(q->source1->attributes.identifier) printf("%s",q->source1->attributes.identifier);
		if(q->source1->attributes.num) printf("%d",q->source1->attributes.num);
		printf(",");
		if(q->source2->attributes.identifier) printf("%s",q->source2->attributes.identifier);
		if(q->source2->attributes.num) printf("%d",q->source2->attributes.num);
		printf("\n");
		break;			
	case '*':
		printf("MUL ");
		if(q->source1->attributes.identifier) printf("%s",q->source1->attributes.identifier);
		if(q->source1->attributes.num) printf("%d",q->source1->attributes.num);
		printf(",");
		if(q->source2->attributes.identifier) printf("%s",q->source2->attributes.identifier);
		if(q->source2->attributes.num) printf("%d",q->source2->attributes.num);
		printf("\n");
		break;			
	case '/':
		printf("DIV ");
		if(q->source1->attributes.identifier) printf("%s",q->source1->attributes.identifier);
		if(q->source1->attributes.num) printf("%d",q->source1->attributes.num);
		printf(",");
		if(q->source2->attributes.identifier) printf("%s",q->source2->attributes.identifier);
		if(q->source2->attributes.num) printf("%d",q->source2->attributes.num);
		printf("\n");
		break;			
	
	
	default:
		printf("Invalid quad opcode: %d\n",q->q_opcode);
	}

	}
	else
	printf("Error: quad null\n");
}

void quads_print_vt(struct ast_node *cur){
	if (cur->type == AST_VAR)
		printf("%s", cur->attributes.identifier);
	else if (cur->type == AST_TMP)
		printf("%%T%05d", cur->attributes.num);

}
