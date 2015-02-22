/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     CHARLIT = 259,
     STRING = 260,
     NUMBER = 261,
     TIMESEQ = 262,
     DIVEQ = 263,
     MODEQ = 264,
     SHLEQ = 265,
     SHREQ = 266,
     ANDEQ = 267,
     OREQ = 268,
     XOREQ = 269,
     PLUSEQ = 270,
     MINUSEQ = 271,
     INDSEL = 272,
     PLUSPLUS = 273,
     MINUSMINUS = 274,
     SHL = 275,
     SHR = 276,
     LTEQ = 277,
     GTEQ = 278,
     EQEQ = 279,
     NOTEQ = 280,
     LOGAND = 281,
     LOGOR = 282,
     PREINC = 283,
     POSTINC = 284,
     PREDEC = 285,
     POSTDEC = 286,
     AUTO = 287,
     BREAK = 288,
     CASE = 289,
     CHAR = 290,
     CONST = 291,
     ELLIPSIS = 292,
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
     _IMAGINARY = 325,
     NEG = 326
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 27 "esparser.y"


//char *yystring;
//int yyint;
//char yychar;

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




/* Line 2068 of yacc.c  */
#line 155 "esparser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


