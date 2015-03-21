// Eugene Sokolov
// Compilers ECE466
// ast.c

#include "ast.h"

struct ast_node *ast_new(int type){

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
	node->other=NULL;

	fprintf(stderr, "NEW NODE: %d\n", type);
	return node;
}

struct ast_node *ast_reservetree(struct ast_node *root, int par){

	struct ast_node * new_root = NULL;
	while(root != NULL){
		struct ast_node * next;
		if (par == NEXT){
			next = root->next;
			root->next = new_root;
		}
		else if (par == LEFT){
			next = root->left;
			root->left = new_root;
		}
		else{
			fprintf(stderr, "AST reverse error\n");
			exit(1);
		}

		new_root = root;
		root = next;
	}

	return new_root;
}

struct ast_node *ast_pushback(struct ast_node *root, struct ast_node *newnode, int par){

	if(root == NULL)
		return newnode;

	if(par == NEXT){
		struct ast_node *next = root->next;
		struct ast_node *tmp = root;
		while (root->next != NULL)
			root = root->next;
	
		root->next = new_node;
		return tmp;
	}
	else if(par == LEFT){
		struct ast_node *next = root->left;
		struct ast_node *tmp = root;
		while (root->left != NULL)
			root = root->left;
	
		root->left = new_node;
		return tmp;
	}
	
	fprintf(stderr, "Error: ast pushback\n");
	return NULL;
}

void ast_print(struct ast_node *root){

}
