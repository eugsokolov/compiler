// Eugene Sokolov
// Compilers ECE466
// ast.c

#include "ast.h"
#include "sym_table.h"
#include "parser.tab.h"

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
        node->other=NULL;

        fprintf(stderr, "NEW NODE: %d\n", type);
        return node;
}

struct ast_node * ast_reverse_tree(struct ast_node *root, int which){
    struct ast_node * new_root = NULL;
    while (root != NULL){
        struct ast_node *next;
        if (which == NEXT){
            next = root->next;
            root->next = new_root;
        } else if (which == LEFT){
            next = root->left;
            root->left = new_root;
        }
        new_root = root;
        root = next;
    }
    return new_root;
}

struct ast_node * ast_push_back(struct ast_node *root, struct ast_node *new_node, int which){
    if  (root == NULL){
        return new_node;
    }
    if (which == NEXT){
        struct ast_node *next = root->next;
        struct ast_node *tmp = root;
        while (root->next != NULL){
            root = root->next;
        }
        root->next = new_node;
        return tmp;
    } else if (which == LEFT){
        struct ast_node *next = root->left;
        struct ast_node *tmp = root;
        while (root->left != NULL){
            root = root->left;
        }
        root->left = new_node;
        return tmp;
    }
    return NULL;
}

int ast_list_size(struct ast_node *root, int which){
    int size=0;
    while (root != NULL){
        if (which == NEXT){
            root = root->next;
        } else if (which == LEFT){
            root = root->left;
        }
        size++;
    }
    return size;
}

void ast_print_syntax_error(char *file_name, int line_number){
    fprintf(stderr, "The syntax in %s: %d is not supported\n", file_name, line_number);
}

void ast_dump(struct ast_node *root, char *fn_name){
    if (fn_name != NULL){
        printf("\nAST DUMP for function %s\n", fn_name);
    } else {
        printf("\nAST DUMP for function (NIL)\n");
    }
    printf("\tLIST {\n");
    while (root != NULL){
        ast_print_node(root, 2);
        root = root->next;
    }
    printf("}\n");
}

void ast_print_node(struct ast_node *root, int tabs){
    int i, size;
    char tab_string[100];
    struct ast_node *tmp;
    for (i=0; i<tabs; i++){
        /*printf("\t");*/
        tab_string[i] = '\t';
    }
    tab_string[i] = '\0';
    switch (root->type){
        case AST_ASSGN:
            printf("%sASSIGNMENT\n", tab_string);
            ast_print_node(root->left, tabs+1);
            ast_print_node(root->right, tabs+1);
            break;
        case AST_VAR:
            printf("%svariable name=%s def @%s:%d\n", tab_string, root->attributes.identifier, root->attributes.file_name, root->attributes.ln_effective);
            break;
        case AST_FNCALL:
            size = ast_list_size(root->right, NEXT);
            printf("%sFNCALL, %d arguments\n", tab_string, size);
            ast_print_node(root->left, tabs+1);
            tmp = root->right;
            for (i=0; i<size; i++){
                printf("%sarg #%d=\n", tab_string, i+1);
                ast_print_node(tmp, tabs+1);
                tmp = tmp->next;
            }
            break;
        case AST_NUM:
            printf("%sCONSTANT: (type=int):%d\n", tab_string, root->attributes.num);
            break;
        case AST_CHAR:
            printf("%sCONSTANT: (type=char):%c\n", tab_string, (char)root->attributes.num);
            break;
        case AST_STR:
            printf("%sCONSTANT: (type=char *):%s\n", tab_string, root->attributes.str);
            for (i=0; i<strlen(root->attributes.str); i++){
                switch (root->attributes.str[i]){
                    case '\"':
                        printf("\\\"");
                        break;
                    case '\'':
                        printf("\\\'");
                        break;
                    case '\\':
                        printf("\\\\");
                        break;
                    case '\a':
                        printf("\\a");
                        break;
                    case '\b':
                        printf("\\b");
                        break;
                    case '\n':
                        printf("\\n");
                        break;
                    case '\t':
                        printf("\\t");
                        break;
                    default:
                        printf("%c", root->attributes.str[i]);
                        break;
                }
            }
            printf("\"\n");
            break;
        case AST_SCALAR:
            printf("%sSCALAR: (type=%d\n", tab_string, root->attributes.num_signed);
            switch (root->attributes.scalar_type){
                case SCALAR_INT:
                    printf("int)\n");
                    break;
                case SCALAR_CHAR:
                    printf("char)\n");
                    break;
                case SCALAR_DOUBLE:
                    printf("double)\n");
                    break;
            }
            break;
        case AST_ARRAY:
            printf("%sArray, (size=%d)\n", tab_string, root->attributes.size);
            break;
        case AST_BINOP:
            printf("%sBINARY OP ", tab_string);
            switch (root->attributes.op){
                case '*':
                    printf("*\n");
                    break;
                case '/':
                    printf("/\n");
                    break;
                case '%':
                    printf("%%\n");
                    break;
                case '+':
                    printf("+\n");
                    break;
                case '-':
                    printf("-\n");
                    break;
                case SHL:
                    printf("<<\n");
                    break;
                case SHR:
                    printf(">>\n");
                    break;
                case '<':
                    printf("<\n");
                    break;
                case '>':
                    printf(">\n");
                    break;
                case LTEQ:
                    printf("<=\n");
                    break;
                case GTEQ:
                    printf(">=\n");
                    break;
                case EQEQ:
                    printf("==\n");
                    break;
                case NOTEQ:
                    printf("!=\n");
                    break;
                case '&':
                    printf("&\n");
                    break;
                case '|':
                    printf("|\n");
                    break;
                case '^':
                    printf("^\n");
                    break;
                case LOGAND:
                    printf("&&\n");
                    break;
                case LOGOR:
                    printf("||\n");
                    break;
            }
            ast_print_node(root->left, tabs+1);
            ast_print_node(root->right, tabs+1);
            break;
        case AST_UNOP:
            printf("%sUNARY OP ", tab_string);
            switch (root->attributes.op){
                case SIZEOF:
                    printf("SIZEOF\n");
                    break;
                case POSTINC:
                    printf("POSTINC\n");
                    break;
                case PREINC:
                    printf("PREINC\n");
                    break;
                case POSTDEC:
                    printf("POSTDEC\n");
                    break;
                case PREDEC:
                    printf("PREDEC\n");
                    break;
                default:
                    printf("%c\n", root->attributes.op);
                    break;
            }
            ast_print_node(root->left, tabs+1);
            break;
        case AST_IF:
            printf("%sIF\n", tab_string);
            printf("%sCOND:\n", tab_string);
            ast_print_node(root->cond, tabs+1);
            printf("%sTHEN:\n", tab_string);
            ast_print_node(root->body, tabs+1);
            if (root->other != NULL){
                printf("%sELSE:\n", tab_string);
                ast_print_node(root->other, tabs+1);
            }
            break;
        case AST_WHILE:
            printf("%sWHILE\n", tab_string);
            printf("%sCOND:\n", tab_string);
            ast_print_node(root->cond, tabs+1);
            printf("%sBODY:\n", tab_string);
            ast_print_node(root->body, tabs+1);
            break;
        case AST_FOR:
            printf("%sFOR\n", tab_string);
            printf("%sINIT:\n", tab_string);
            ast_print_node(root->left, tabs+1);
            printf("%sCOND:\n", tab_string);
            ast_print_node(root->cond, tabs+1);
            printf("%sBODY:\n", tab_string);
            ast_print_node(root->body, tabs+1);
            printf("%sINCR:\n", tab_string);
            ast_print_node(root->right, tabs+1);
            break;
    }
}

void ast_print_tree(struct ast_node *root){
    int num=0, i;
    while (root != NULL){
        for (i=0; i<num; i++){
            printf("\t");
        }
        switch (root->type){
            case AST_VAR:
                printf("Variable %s, FILE: %s - %d, SCOPE: %d, SCOPE START: %s - %d ", 
			root->attributes.identifier,
                        curr_scope->filename, 
			root->attributes.ln_effective, 
			root->scope_type,
			curr_scope->filename,
			curr_scope->line_begin);
                if (root->left && root->left->type == AST_STORAGE){
                    printf("Storage class: ");
                }
                while (root->left && root->left->type == AST_STORAGE){
                    root = root->left;
                    switch (root->attributes.storage_class){
                        case STORE_AUTO:
                            printf("AUTO, ");
                            break;
                        case STORE_EXTERN:
                            printf("EXTERN, ");
                            break;
                        case STORE_REGISTER:
                            printf("REGISTER, ");
                            break;
                        case STORE_STATIC:
                            printf("STATIC, ");
                            break;
                    }
                }
                printf("TYPE: \n");
                break;
            case AST_SCALAR:
                printf("Scalar, %d\n", root->attributes.num_signed);
                switch (root->attributes.scalar_type){
                    case SCALAR_INT:
                        printf("INT");
                        break;
                    case SCALAR_CHAR:
                        printf("CHAR");
                        break;
                    case SCALAR_DOUBLE:
                        printf("DOUBLE");
                        break;
                }
                if (root->attributes.num_signed == TYPE_UNSIGNED)
                    printf(", UNSIGNED");
                printf("\n");
                break;
            case AST_ARRAY:
                printf("Array, Size: %d\n", root->attributes.size);
                break;
            case AST_FN:
                printf("Function Returns: \n");
                break;
            case AST_PTR:
                printf("Pointer to\n");
                break;
            case AST_TYPEDEF:
                printf("Typedef to\n");
                break;
            case AST_STORAGE:
                printf("Storage class: ");
                switch (root->attributes.storage_class){
                    case STORE_AUTO:
                        printf("AUTO\n");
                        break;
                    case STORE_EXTERN:
                        printf("EXTERN\n");
                        break;
                    case STORE_REGISTER:
                        printf("REGISTER\n");
                        break;
                    case STORE_STATIC:
                        printf("STATIC\n");
                        break;
                }
                break;
        }
        root = root->left;
        num++;
    }
}
