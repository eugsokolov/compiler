/*
EUGENE SOKOLOV
ECE466: Compilers
LEXICAL ANALYSIS: YYLVAL definition
*/

#ifndef _YYLVAL_H
#define _YYLVAL_H

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
endif
