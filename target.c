// Eugene Sokolov
// Compilers ECE466
// target.c

#include "target.h"
#include "parser.tab.h"

struct basic_block *current_bb;
struct basic_block_list *fn_bb_list;
int fn_count = 1;
int bb_count = 1;
int tmp_count = 1;
struct loop *current_l;

char buffer1[MAX_STRING_LENGTH];
char buffer2[MAX_STRING_LENGTH];
char buffer3[MAX_STRING_LENGTH];
const int alignment = 4;
const int variable_size = 4;
int strvar = 0;
int arg = 0;

void target_print(){

	int i = target_print_globl();
	if(i == 0){
		printf("\t.text\n");
		printf("\t.globl %s\n", fn_bb_list->func);
		printf("\t.type %s, @function\n", fn_bb_list->func);
	}
	printf("\n%s:\n", fn_bb_list->func);
	printf("\tpushl %%ebp\n");
	printf("\tmovl %%esp, %%ebp\n");
	printf("\tsubl $-%d, %%esp\n", variable_size * 4);

	int j = 0;
	while(fn_bb_list->head != NULL){
		target_print_bb(fn_bb_list->head);
		fn_bb_list->head = fn_bb_list->head->next;
		j++;	
		if(fn_bb_list->bbend == j) exit(0);
	}
}

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

	target_list_push(current_bb->quads, q);
	return q;

}

struct ast_node * target_new_tmp(){

	tmp_count++;
	struct ast_node *tmp = ast_newnode(AST_TMP);
	tmp->type = AST_TMP;
	tmp->attributes.num = tmp_count;

	return tmp;
}

int target_print_globl(){

	int i=0;
	struct ast_node *tmp = current_bb->next->quads->head->result;
	while(tmp != NULL){
		if(tmp->type == 16){
		//Should actually traverse and find AST_FNCALL
		tmp=tmp->body;
			if(tmp->right->type == 5){
				printf(".LC%d:\n", strvar++);
				printf("\t.string \"%s\"\n", tmp->right->attributes.str);
				printf("\t.text\n");
				printf("\t.globl %s\n", fn_bb_list->func);
				printf("\t.type %s, @function\n", fn_bb_list->func);
				i++;
			}	
		}
			
		tmp=tmp->next;

	}

	return i;
}

void target_globl(struct ast_node *ast){

	printf("\t.comm %s,%d,%d\n", ast->attributes.identifier, variable_size, variable_size);
}

struct quad_list *target_gen_fn(struct ast_node *ast_fn, struct ast_node *ast){

	if(ast_fn->type != AST_VAR || ast_fn->left->type != AST_FN)
		return NULL;
	
	fn_bb_list = new_bb_list();
	struct basic_block *bb = new_basic_block();
	current_bb = bb;
	
	arg=1;	
//	printf("%s:\n", ast_fn->attributes.identifier);
	fn_bb_list->func = strdup(ast_fn->attributes.identifier);

	while(ast != NULL){
		target_gen_statement(ast);
		ast=ast->next;
	}

	bb_list_push(fn_bb_list,bb);	
//	target_print_bb(bb);
	fn_count++;
}

struct quad_list *target_gen_fncall(struct ast_node *ast){

	struct ast_node *arg = ast->right;
	struct ast_node *list = ast_newnode(AST_FNCALL_ARG);
	strcpy(list->attributes.identifier,"function arg list");
	while(arg != NULL && (arg->type == 0 || arg->type == 5)){
		if(arg->type == 5){
			sprintf(arg->attributes.identifier,".LC%d",strvar);
			//strcpy(arg->attributes.identifier, ".LC0");
		}
		else if(arg->type == 4){
			arg->attributes.num = 0;
			if(arg->attributes.scalar_type == 0) arg->attributes.num = 4;	
			else if(arg->attributes.scalar_type == 1) arg->attributes.num = 1;	
			else if(arg->attributes.scalar_type == 2) arg->attributes.num = 16;
		}
		else if(arg->type == 0){
			arg->attributes.num = 0;
			if(arg->left->attributes.scalar_type == 0) arg->attributes.num = 4;	
			else if(arg->left->attributes.scalar_type == 1) arg->attributes.num = 1;	
			else if(arg->left->attributes.scalar_type == 2) arg->attributes.num = 16;
		}

		emit(Q_FNCALL_ARG, arg, NULL, NULL);
//		if(arg->next != NULL) ast_push_back(list,arg,NEXT);
		arg = arg->next;
	}
/*
	while(list != NULL){
printf("name: %s\n", list->attributes.identifier);
printf("type: %d\n", list->type);
		emit(Q_FNCALL_ARG, list, NULL, NULL);
		list = list->next;
	}
*/	
	emit(Q_FNCALL, NULL, NULL, ast);	
	return NULL;
}

struct quad_list *target_gen_statement(struct ast_node *ast){

	struct quad_list *new = new_quad_list();
	switch(ast->type){
	case AST_ASSGN:
		target_gen_assignment(ast);
	break;
	case AST_IF:
		target_gen_if(ast);	
	break;
	case AST_FOR:
		target_gen_for(ast);
	break;
	case AST_DO:
		
	break;
	case AST_WHILE:
	break;	
	case AST_FN:
		target_gen_fn(ast, ast->right);
	break;
	case AST_FNCALL:
		target_gen_fncall(ast);
	break;
	case AST_BINOP:
		emit(ast->attributes.op,ast->right,ast->left,NULL);
	break;
	case AST_UNOP:
		emit(Q_INC,ast,NULL,NULL);
	break;

	case AST_VAR: break;
	case AST_RET:
		target_gen_return(ast);
	break;
	default:
		fprintf(stderr, "Invalid statement type: quad_gen_statement %d\n",ast->type);
		break;
	}
	
	return new;
}

struct ast_node *target_gen_assignment(struct ast_node *ast){

	struct ast_node *tmp, *dest;
	int dstmode;
	dest = target_gen_lval(ast->left, &dstmode);
	if(dest == NULL){
		fprintf(stderr, "Error: target_gen_assigment: LHS invalid");
	}	
	if(dstmode == DIRECT){
		if(ast->right->type == AST_BINOP){
		tmp = target_gen_rval(ast->right, dest);
		}
		else{
		tmp = target_gen_rval(ast->right, dest);
		emit(Q_MOV, tmp, NULL, dest);
		}
	}
	else{
		tmp = target_gen_rval(ast->right, NULL);
		emit(Q_STORE, tmp, NULL, dest);
	}
	return dest;
}

struct ast_node *target_gen_rval(struct ast_node *ast, struct ast_node *target){

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

		ptr_left = get_pointer(ast->left, 0);
		ptr_right = get_pointer(ast->right, 0);
                
		if(ptr_left){
		        if (ast->attributes.op != '-' && ast->attributes.op != '+')
			fprintf(stderr, "Invalid operation on pointer arithmetic\n");
		        
		        left = target_gen_rval(ast->left, NULL);
		        tmp = target_gen_rval(ast->right, NULL);
		        n1 = ast_newnode(AST_BINOP);
		        n1->attributes.op = '*';
		        n1->left = tmp;
		        n2 = ast_newnode(AST_NUM);
		        n2->attributes.num = ptr_left;
		        n1->right = n2;
		        right = target_gen_rval(n1, NULL);
		}
		else if(ptr_right){
		        if (ast->attributes.op != '-' && ast->attributes.op != '+')
			fprintf(stderr, "Invalid operation on pointer arithmetic\n");
		        
		        right = target_gen_rval(ast->right, NULL);
		        tmp = target_gen_rval(ast->left, NULL);
		        n1 = ast_newnode(AST_BINOP);
		        n1->attributes.op = '*';
		        n1->right = tmp;
		        n2 = ast_newnode(AST_NUM);
		        n2->attributes.num = ptr_right;
		        n1->left = n2;
		        left = target_gen_rval(n1, NULL);
		}
		else{
		        left = target_gen_rval(ast->left, NULL);
		        right = target_gen_rval(ast->right, NULL);
		}

		if (target == NULL) 
			target = target_new_tmp();

		emit(ast->attributes.op, left, right, target);
		return target;
        break;
	default:
		return NULL;
	}
}

int get_pointer(struct ast_node *node, int deref){

	struct ast_node *size_node = node;
	int r=0,l=0,i=0;
	
	if(node->type == AST_UNOP)
		return get_pointer(node->left, deref+1);
	else if(node->type == AST_BINOP){
		l = get_pointer(node->left, deref);
		r = get_pointer(node->right, deref);
		if(l) return l;
		else if(r) return r;
		else if (node->type == AST_VAR && node->left && (node->left->type == AST_PTR || node->left->type == AST_ARY)){
 			while (i++ < deref){
			size_node = node->left;
			}
			return get_sizeof(size_node->left->left);
		}	
	}
	else 
		return 0;
}

int get_sizeof(struct ast_node *node){

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
		return get_sizeof(node->left);
	
	return 0;
}

struct ast_node *target_gen_lval(struct ast_node *ast, int *dstmode){

	switch(ast->type){
	case AST_VAR:
	        if(ast->left != NULL && ast->left->type == AST_SCALAR)
                *dstmode = DIRECT;
                
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
	
void target_gen_return(struct ast_node *ast){

	if(ast->left == NULL) emit(Q_RETURN, NULL, NULL, NULL);
	else emit(Q_RETURN, NULL, NULL, ast->left);
	fn_bb_list->bbend = current_bb->i;
}

void target_gen_if(struct ast_node *ast){
	
	struct basic_block *bt, *bf, *bn;
	bt = new_basic_block();
	bf = new_basic_block();
	if(ast->next != NULL)
		bn = new_basic_block();
	else
		bn = bf;
	
	target_gen_condexpr(ast->cond, bt, bf);
	current_bb=bt;
	target_gen_statement(ast->body);
	basic_block_link(current_bb, ALWAYS, bn, NULL);
	if(ast->next != NULL){
		current_bb=bf;
		target_gen_statement(ast->next);
		basic_block_link(current_bb, ALWAYS, bn, NULL);
	}
	current_bb=bn;

}

void target_gen_for(struct ast_node *ast){
        
	struct basic_block *b_cond = new_basic_block();
	struct basic_block *b_body = new_basic_block();
	struct basic_block *b_inc = new_basic_block();
	struct basic_block *b_next = new_basic_block();

	target_gen_assignment(ast->left);
	loop_new(b_inc, b_next);
	basic_block_link(current_bb, ALWAYS, b_cond, NULL);
	current_bb = b_cond;
	target_gen_condexpr(ast->cond, b_body, b_next);
	current_bb = b_body;
	target_gen_statement(ast->body);
	basic_block_link(current_bb, ALWAYS, b_inc, NULL);
	current_bb = b_inc;
	target_gen_statement(ast->right);
	basic_block_link(current_bb, ALWAYS, b_cond, NULL);
	current_bb = b_next;	
	loop_end();

}

void target_gen_condexpr(struct ast_node *ast, struct basic_block *true_b, struct basic_block *false_b){

	struct ast_node *left, *right, *tmp1, *tmp2;
	switch(ast->type){
		case AST_VAR:
		tmp1 = target_gen_rval(ast, NULL);
		tmp2 = ast_newnode(AST_NUM);
		tmp2->attributes.num = 0;
		emit(Q_CMP, tmp1, tmp2, NULL);
		basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_NUM:
		case AST_CHAR:
		tmp2 = ast_newnode(AST_NUM);
		tmp2->attributes.num = 0;
		emit(Q_CMP, ast, tmp2, NULL);
		basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_STR:
		basic_block_link(current_bb, ALWAYS, true_b, false_b);
		break;
		case AST_BINOP:
		switch (ast->attributes.op){
			case '<':
			case '>':
			case EQEQ:
			case NOTEQ:
				left = target_gen_rval(ast->left, NULL);
				right = target_gen_rval(ast->right, NULL);
				emit(Q_CMP, left, right, NULL);
				basic_block_link(current_bb, COND_LT, true_b, false_b);
				break;
			default:
				left = target_gen_rval(ast, NULL);
				right = ast_newnode(AST_NUM);
				right->attributes.num=0;
				emit(Q_CMP, left, right, NULL);
				basic_block_link(current_bb, COND_NE, true_b, false_b);
		}
		break;
		case AST_UNOP:
		left = target_gen_rval(ast, NULL);
		right = ast_newnode(AST_NUM);
		right->attributes.num = 0;
		emit(Q_CMP, left, right, NULL);
		basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
		case AST_ASSGN:
		left = target_gen_assignment(ast);
		right = ast_newnode(AST_NUM);
		right->attributes.num = 0;
		emit(Q_CMP, left, right, NULL);
		basic_block_link(current_bb, COND_NE, true_b, false_b);
		break;
	}
		
}

struct loop *loop_new(struct basic_block *b_continue, struct basic_block *b_break){

	struct loop *l = malloc(sizeof(struct loop));
	if(l == NULL)
		fprintf(stderr, "Error creating loop struct\n");

	l->b_continue = b_continue;
	l->b_break = b_break;
	l->previous = current_l;
	current_l = l;
	return l;

}

struct loop *loop_end(){
	struct loop *l = current_l;
	current_l = current_l->previous;
	free(l);
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

struct quad_list *target_list_push(struct quad_list *list, struct quad *new_quad){

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
	//sprintf(id, "BB:%d@%d",fn_count, bb_count++);
	sprintf(id, ".L%d", bb_count++);
	bb->i = bb_count - 1;
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
	bbl->bbend = 0;
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

char *target_id(struct ast_node *ast, char *buffer){
	
	int offset;

	switch(ast->type){
	case AST_VAR:
		offset = 4;
                sprintf(buffer, "-%d(%%ebp)", offset * variable_size);
		break;
	case AST_NUM:
		sprintf(buffer, "$%d", ast->attributes.num);
		break;
	case AST_STR:
		sprintf(buffer, "$%s", ast->attributes.identifier);
		break;
	default:
		//printf("error %d\n", ast->type);
		break;
	}

	return buffer;
}

void target_print_bb(struct basic_block *bb){
	
	char *r, *s1, *s2;

	if (bb != NULL){
		struct basic_block *cur_bb = bb;
		struct quad *cur = bb->quads->head;
		
		printf("%s:\n", bb->id);
		while (cur != NULL){
		
		target_print_inst(cur);
		cur = cur->next;
		}
		
		if(bb->left != NULL) s1 = bb->left->id;
		else s1 = NULL;
		if(bb->right != NULL) s2 = bb->right->id;
		else s2 = NULL;
		
		switch (bb->branch){
		case NEVER:
			break;
		case ALWAYS:
	                printf("\tjmp %s\n",s1);
			break;
		case COND_LT:
        		printf("\tjl %s\n", s1);
	        	printf("\tjmp %s\n", s2);
			break;
	        case COND_GT:
        		printf("\tjg %s\n", s1);
	        	printf("\tjmp %s\n", s2);
        		break;
        	case COND_LE:
        		printf("\tjle %s\n", s1);
	        	printf("\tjmp %s\n", s2);
        		break;
        	case COND_GE:
        		printf("\tjge %s\n", s1);
	        	printf("\tjmp %s\n", s2);
       			break;
        	case COND_EQ:
        		printf("\tje %s\n", s1);
	        	printf("\tjmp %s\n", s2);
        		break;
        	case COND_NE:
        		printf("\tjne %s\n", s1);
	        	printf("\tjmp %s\n", s2);
        		break;
		}
	// target_print_bb(bb->next);
	}
}

void target_print_inst(struct quad *q){
	
	char *r, *s1, *s2;
		
	if(q->result != NULL) r = target_id(q->result, buffer1);
	else r = NULL;
	if(q->source1 != NULL) s1 = target_id(q->source1, buffer2);
	else s1 = NULL;
	if(q->source2 != NULL) s2 = target_id(q->source2, buffer3);
	else s2 = NULL;

	if(q){
	switch(q->q_opcode){
	case Q_LEA:
		printf("LEA \t%s\n",q->source1->attributes.identifier );
		break;
	case Q_STORE:
                printf("\tmovl %s, %%eax\n", s2);
                printf("\tmovl %s, %%edx\n", s1);
                printf("\tmovl %%edx, (%%eax)\n");
		break;
	case Q_MOV:
                printf("\tmovl %s, %%eax\n", s1);
                printf("\tmovl %%eax, %s\n", r);
		break;
	case Q_CMP:
                printf("\tmovl %s, %%eax\n",s1);
                printf("\tcmpl %s, %%eax\n",s2);
		break;
	case Q_LOAD:
                printf("\tmovl %s, %%eax\n", s1);
                printf("\tmovl (%%eax), %%edx\n");
                printf("\tmovl %%edx, %s\n", r);
		break;
	case Q_FNCALL_ARG:
		if(q->source1->type == 5)
			printf("\tmovl $%s, (%%esp)\n", q->source1->attributes.identifier);
		else if(q->source1->type == 0){
			printf("\tmovl %s, %%eax\n", q->source1->attributes.identifier);
			printf("\tmovl %%eax, %d(%%esp)\n", arg * variable_size);
		}
		arg++;
		break;	
	case Q_FNCALL:
		printf("\tcall %s\n",q->result->left->attributes.identifier);		
		break;
	case Q_RETURN:
		if(r) printf("\tmovl %s, %%eax\n", r);
		//printf("\tmovl %%ebp, %%esp\n");
                //printf("\tpopl %%ebp\n");
                printf("\tleave\n");
                printf("\tret\n");
		break;
	case Q_INC:
                printf("\tmovl %s, %%eax\n", s1);
                printf("\taddl %%eax, 1\n");
                printf("\tmovl %%eax, %s\n", s1);
		break;
        case '+':
                printf("\tmovl %s, %%eax\n", s2);
                printf("\tmovl %s, %%edx\n", s1);
                printf("\taddl %%eax, %%edx\n");
                printf("\tmovl %%edx, %s\n", r);
	        break;
        case '-':
                printf("\tmovl %s, %%eax\n", s2);
                printf("\tmovl %s, %%edx\n", s1);
                printf("\tsubl %%eax, %%edx\n");
                printf("\tmovl %%edx, %s\n", r);
		break;
        case '*':
                printf("\tmovl %s, %%eax\n", s2);
                printf("\tmovl %s, %%edx\n", s1);
                printf("\timull %%edx\n");
                printf("\tmovl %%edx, %s\n", r);
	        break;
	default:
		printf("Invalid quad opcode: %d\n",q->q_opcode);
	}

	}
	else
	printf("Error: quad null\n");
}

void target_print_vt(struct ast_node *cur){
	if (cur->type == AST_VAR)
		printf("%s", cur->attributes.identifier);
	else if (cur->type == AST_TMP)
		printf("%%T%05d", cur->attributes.num);

}
