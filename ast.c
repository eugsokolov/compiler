// Eugene Sokolov
// Compilers ECE466
// ast.c

#include "ast.h"
#include "sym_table.h"
#include "parser.tab.h"

extern int astdebug;
extern struct sym_table *curr_scope;
	
struct ast_node *ast_newnode(int type){
	struct ast_node *node;
	if((node=malloc(sizeof(struct ast_node))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
		return NULL;
	}
	node->type=type;
	node->left=NULL;
	node->right=NULL;
	node->next=NULL;
	node->cond=NULL;
	node->body=NULL;

//fprintf(stderr, "NEW NODE: %d\n", type);
	
	return node;
}

struct ast_node * ast_reverse_tree(struct ast_node *root, int dir){
	struct ast_node * new_root = NULL;
	while(root != NULL){
		struct ast_node *next;
		if(dir == NEXT){
			next = root->next;
			root->next = new_root;
		} 
		else if(dir == LEFT){
			next = root->left;
			root->left = new_root;
		}
		new_root = root;
		root = next;
	}
	return new_root;
}

struct ast_node * ast_push_back(struct ast_node *root, struct ast_node *new_node, int dir){
	if(root == NULL)
		return new_node;

	if(dir == NEXT){
		struct ast_node *next = root->next;
		struct ast_node *tmp = root;
		while(root->next != NULL)
			root = root->next;
	
		root->next = new_node;
		return tmp;
	} 
	else if(dir == LEFT){
		struct ast_node *next = root->left;
		struct ast_node *tmp = root;
		while(root->left != NULL)
			root = root->left;
	
	root->left = new_node;
	return tmp;
	}
	return NULL;
}

int ast_list_size(struct ast_node *root, int dir){
	int size=0;
	while(root != NULL){
		if(dir == NEXT)
			root = root->next;
		else if(dir == LEFT)
			root = root->left;
	size++;
	}
	return size;
}

void ast_dump(struct ast_node *root, char *fn_name){
	if(fn_name != NULL)
		printf("\nAST DUMP for function %s\n", fn_name);
	else
		printf("\nAST DUMP for function NULL\n");

	printf("\n---------------------AST-----------------------\n");
	
	while(root != NULL){
		ast_print_node(root);
		root = root->next;
		printf("\n");
	}
	
	printf("\n-----------------------------------------------\n");
	exit(0);
}

void ast_print_node(struct ast_node *root){
	int i=0,size=0;
	struct ast_node *tmp;
	
//printf("node type:%d\n", root->type);

	switch(root->type){
	case AST_VAR:
		printf("\tVAR=%s defined@%s:%d\n", root->attributes.identifier, root->attributes.filename, root->attributes.linestart);
		break;
	case AST_NUM:
		printf("\tCONST type:int=%d\n", root->attributes.yynum);
		break;
	case AST_STR:
		printf("\tCONST type:char * :%s\n", root->attributes.str);
		for(i=0; i<strlen(root->attributes.str); i++)
			printf("%c", root->attributes.str[i]);
		printf("\n");
		break;
	case AST_CHAR:
		printf("\tCONST type=char :%c\n", (char)root->attributes.yynum);
		break;
	case AST_ASSGN:
		printf("\tASSIGNMENT\n");
		ast_print_node(root->left);
		printf("EQUALS\n");
		ast_print_node(root->right);
		break;
	case AST_SCALAR:
		printf("\tSCALAR type=%d ",root->attributes.num_signed);
		switch(root->attributes.scalar_type){
		case SCALAR_INT:
			printf("int\n");
			break;
		case SCALAR_CHAR:
			printf("char\n");
			break;
		case SCALAR_DOUBLE:
			printf("double\n");
			break;
		}
		break;
	case AST_BINOP:
        	printf("BINOP ");
        	switch (root->attributes.op){
                case '<':
                	printf("<\n");
                	break;
                case '>':
                	printf(">\n");
                	break;
		default:
			printf("lazy binop\n");
		}
		break;
	case AST_UNOP:
        	printf("UNOP ");
        	switch (root->attributes.op){
                case PREINC:
        		printf("SIZEOF\n");
                	break;
		case POSTINC:
			printf("POSTINC\n");
			break;
		default:
			printf("%c\n", root->attributes.op);
		}
		break;
	case AST_ARY:
		printf("\tArray size=%d\n", root->attributes.ary);
		break;
        case AST_FNCALL:
	        size = ast_list_size(root->right, NEXT);
	        printf("\tFNCALL, %d arguments\n\t\t",size);
        	ast_print_node(root->left);
        	tmp = root->right;
        	for(i=0; i<size; i++){
        	        printf("arg#%d= ",i+1);
        	        ast_print_node(tmp);
			printf("\n");
                	tmp = tmp->next;
           	}
        	break;
	case AST_IF:
		printf("\tIF\n");
		printf("\tCOND:\n\t\t");
			ast_print_node(root->cond);
		printf("\tTHEN:\n\t\t");
			ast_print_node(root->body);
		if(root->next != NULL){
			printf("\tELSE:\n\t");
			ast_print_node(root->next);
		}
		break;
	case AST_WHILE:
		printf("\tWHILE\n");
		printf("\tCOND:\n\t\t");
			ast_print_node(root->cond);
		printf("\tBODY:\n\t\t");
			ast_print_node(root->body);
		break;
	case AST_FOR:
		printf("\tFOR\n");
		printf("\tINIT:\n\t");
			ast_print_node(root->left);
		printf("\tCOND:\n\t\t");
			ast_print_node(root->cond);
		printf("\tINCR:\n\t\t");
			ast_print_node(root->right);
		printf("\tBODY:\n\t\t");
			ast_print_node(root->body);
		break;
	default:
		fprintf(stderr, "ERROR printing ast node");
	}
}
