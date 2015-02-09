/*
EUGENE SOKOLOV
ECE466: Compilers
LEXICAL ANALYSIS: YYLVAL definition
*/

#ifndef _YYLVAL_H
#define _YYLVAL_H

enum number_type{
	TYPE_INT=0,
	TYPE_LONG,
	TYPE_LONGLONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_LONGDOUBLE,
	TYPE_UNSIGNED,
	TYPE_SIGNED
};

typedef union{
	char yychar;
	char *yystring;
	unsigned int yystring_size;
	//int yyint;
	unsigned long long int yyint;
	long double yydouble;
	enum number_type num_type;
	enum number_type num_sign;
} YYSTYPE;

#define MAX_STRING_LENGTH 4096
extern YYSTYPE yylval;

#endif
