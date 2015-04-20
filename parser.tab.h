/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHARLIT = 258,
    IDENT = 259,
    STRING = 260,
    NUMBER = 261,
    INDSEL = 262,
    PLUSPLUS = 263,
    MINUSMINUS = 264,
    SHL = 265,
    SHR = 266,
    LTEQ = 267,
    GTEQ = 268,
    EQEQ = 269,
    NOTEQ = 270,
    LOGAND = 271,
    LOGOR = 272,
    ELLIPSIS = 273,
    TIMESEQ = 274,
    DIVEQ = 275,
    MODEQ = 276,
    PLUSEQ = 277,
    MINUSEQ = 278,
    SHLEQ = 279,
    SHREQ = 280,
    ANDEQ = 281,
    OREQ = 282,
    XOREQ = 283,
    PREINC = 284,
    POSTINC = 285,
    PREDEC = 286,
    POSTDEC = 287,
    AUTO = 288,
    BREAK = 289,
    CASE = 290,
    CHAR = 291,
    CONST = 292,
    CONTINUE = 293,
    DEFAULT = 294,
    DO = 295,
    DOUBLE = 296,
    ELSE = 297,
    ENUM = 298,
    EXTERN = 299,
    FLOAT = 300,
    FOR = 301,
    GOTO = 302,
    IF = 303,
    INLINE = 304,
    INT = 305,
    LONG = 306,
    REGISTER = 307,
    RESTRICT = 308,
    RETURN = 309,
    SHORT = 310,
    SIGNED = 311,
    SIZEOF = 312,
    STATIC = 313,
    STRUCT = 314,
    SWITCH = 315,
    TYPEDEF = 316,
    TYPEDEF_NAME = 317,
    UNION = 318,
    UNSIGNED = 319,
    VOID = 320,
    VOLATILE = 321,
    WHILE = 322,
    _BOOL = 323,
    _COMPLEX = 324,
    _IMAGINARY = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 24 "parser.y" /* yacc.c:1909  */


	char yychar;
	char *yystring;
	int yystring_size;

	struct num{
		enum number_type num_type;
		enum sign_type num_sign;
		long long yyint;
		long double yydouble;
	}number;

	struct ast_node *node;
	void *nil;

#line 142 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
