

#ifndef _YYLVAL_H
#define _YYLVAL_H

enum number_type{
  SIZE_INT=0,
  SIZE_LONG,
  SIZE_LONGLONG,
  SIZE_FLOAT,
  SIZE_DOUBLE,
  SIZE_LONGDOUBLE,
  SIZE_UNSIGNED,
  SIZE_SIGNED
};

typedef union{
  char yychar;
  char *yystring;
  //int yyint;
  unsigned long long int yyint;
  long double yydouble;
  enum number_type num_type;
  enum number_type num_sign;
} YYSTYPE;

extern YYSTYPE yylval;

#endif
