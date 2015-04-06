/*
EUGENE SOKOLOV
ECE466: Compilers
LEXICAL ANALYSIS: YYLVAL definition
*/

#ifndef _YYLVAL_H
#define _YYLVAL_H

/*
enum number_type{
	TYPE_INT,
	TYPE_LONG,
	TYPE_LONGLONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_LONGDOUBLE,
	TYPE_UNSIGNED,
	TYPE_SIGNED
};

typedef union{

	struct word{
		unsigned int yystring_size;
		char yychar;
		char *yystring;
	}word;	

	struct number{
		enum number_type num_type;
		enum number_type num_sign;
		unsigned long long int yyint;
		long double yydouble;
	}number;

} YYSTYPE;
#define MAX_STRING_LENGTH 4096
extern YYSTYPE yylval;

*/

typedef struct{
        char yychar;
        char *yystring;
        int yystring_size;

        struct number{
                enum number_type{
                        TYPE_INT,
                        TYPE_LONG,
                        TYPE_LONGLONG,
                        TYPE_FLOAT,
                        TYPE_DOUBLE,
                        TYPE_LONGDOUBLE,
                } num_type;
                enum sign_type{
                        TYPE_UNSIGNED,
                        TYPE_SIGNED
                } num_sign;
                long long yyint;
                long double yydouble;
        }number;

        struct ast_node *node;
        struct ast_node_list *node_list;
        void *nil;

} YYSTYPE;
extern YYSTYPE yylval;

#endif
