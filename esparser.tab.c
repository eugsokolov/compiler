/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 3 "esparser.y"

/*
http://www.csc.villanova.edu/~tway/courses/csc4181/s2012/handouts/Tiny%20Symbol%20Table%20Info.pdf
http://research.microsoft.com/en-us/um/people/rgal/ar_language/external/compiler.pdf
http://www.mactech.com/articles/mactech/Vol.16/16.07/UsingFlexandBison/index.html
*/

//EUGENE SOKOLOV
//COMPILERS ECE466
//PARSER ANALYSIS: parser.y

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "esparser.tab.h"
#include "sym_table.h"

#define YYDEBUG 1
int yydebug = 0;

extern int yylex();
extern int yyparse();
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
void yyerror(const char *s);
void insert_symbol(char *s);

struct sym_table *curr;



/* Line 268 of yacc.c  */
#line 105 "esparser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     AUTO = 284,
     BREAK = 285,
     CASE = 286,
     CHAR = 287,
     CONST = 288,
     CONTINUE = 289,
     DEFAULT = 290,
     DO = 291,
     DOUBLE = 292,
     ELSE = 293,
     ENUM = 294,
     EXTERN = 295,
     FLOAT = 296,
     FOR = 297,
     GOTO = 298,
     IF = 299,
     INLINE = 300,
     INT = 301,
     LONG = 302,
     REGISTER = 303,
     RESTRICT = 304,
     RETURN = 305,
     SHORT = 306,
     SIGNED = 307,
     SIZEOF = 308,
     STATIC = 309,
     STRUCT = 310,
     SWITCH = 311,
     TYPEDEF = 312,
     TYPEDEF_NAME = 313,
     UNION = 314,
     UNSIGNED = 315,
     VOID = 316,
     VOLATILE = 317,
     WHILE = 318,
     _BOOL = 319,
     _COMPLEX = 320,
     _IMAGINARY = 321
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 36 "esparser.y"


	char yychar;
	char *yystring;

	struct number{
		enum number_type{
			TYPE_INT,
			TYPE_LONG,
			TYPE_LONGLONG,
			TYPE_FLOAT,
			TYPE_DOUBLE,
			TYPE_LONGDOUBLE
		} num_type;
		enum sign_type{
			TYPE_UNSIGNED,
			TYPE_SIGNED
		} num_sign;
		long long yyint;
		long double yydouble;
	}number;

	void *nil;



/* Line 293 of yacc.c  */
#line 234 "esparser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 246 "esparser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,     2,     2,    84,    81,     2,
      67,    68,    82,    72,    73,    78,    77,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    90,    71,
      85,    74,    86,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    87,    70,    80,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    19,    22,
      23,    28,    30,    33,    35,    37,    40,    42,    44,    48,
      52,    54,    56,    58,    62,    64,    66,    68,    72,    74,
      79,    83,    87,    89,    92,    95,    99,   104,   106,   110,
     112,   117,   119,   124,   127,   130,   133,   136,   139,   142,
     145,   148,   150,   154,   158,   162,   164,   168,   172,   174,
     178,   182,   184,   188,   192,   196,   200,   202,   206,   210,
     212,   216,   218,   222,   224,   228,   230,   234,   236,   240,
     242,   248,   250,   254,   258,   262,   266,   270,   274,   278,
     282,   286,   290,   294,   296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      92,     0,    -1,    93,    -1,    92,    93,    -1,   101,    -1,
      94,    -1,    95,    96,    -1,     4,    67,    68,    -1,    69,
      70,    -1,    -1,    69,    97,    98,    70,    -1,    99,    -1,
      98,    99,    -1,   101,    -1,   100,    -1,   123,    71,    -1,
      96,    -1,    71,    -1,    46,   104,    71,    -1,   102,   103,
      71,    -1,    72,    -1,    72,    -1,    72,    -1,   104,    73,
       4,    -1,     4,    -1,     4,    -1,     6,    -1,    67,   123,
      68,    -1,   105,    -1,   106,    75,   123,    76,    -1,   106,
      77,     4,    -1,   106,     7,     4,    -1,   107,    -1,   106,
       8,    -1,   106,     9,    -1,   106,    67,    68,    -1,   106,
      67,   108,    68,    -1,   122,    -1,   108,    73,   122,    -1,
     110,    -1,    67,    46,    68,   109,    -1,   106,    -1,    53,
      67,    46,    68,    -1,    78,   109,    -1,    72,   109,    -1,
      79,   109,    -1,    80,   109,    -1,    81,   109,    -1,    82,
     109,    -1,     8,   110,    -1,     9,   110,    -1,   109,    -1,
     111,    82,   109,    -1,   111,    83,   109,    -1,   111,    84,
     109,    -1,   111,    -1,   112,    72,   111,    -1,   112,    78,
     111,    -1,   112,    -1,   113,    10,   112,    -1,   113,    11,
     112,    -1,   113,    -1,   114,    85,   113,    -1,   114,    12,
     113,    -1,   114,    86,   113,    -1,   114,    13,   113,    -1,
     114,    -1,   115,    14,   114,    -1,   115,    15,   114,    -1,
     117,    -1,   116,    87,   117,    -1,   118,    -1,   117,    88,
     118,    -1,   115,    -1,   118,    81,   115,    -1,   120,    -1,
     119,    17,   120,    -1,   116,    -1,   120,    16,   116,    -1,
     119,    -1,   119,    89,   123,    90,   121,    -1,   121,    -1,
     110,    74,   122,    -1,   110,    22,   122,    -1,   110,    23,
     122,    -1,   110,    19,   122,    -1,   110,    20,   122,    -1,
     110,    21,   122,    -1,   110,    24,   122,    -1,   110,    25,
     122,    -1,   110,    26,   122,    -1,   110,    27,   122,    -1,
     110,    28,   122,    -1,   122,    -1,   123,    73,   122,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    93,    94,    98,   102,   109,   110,
     110,   121,   122,   126,   127,   131,   132,   133,   142,   143,
     147,   151,   155,   186,   187,   195,   208,   218,   222,   223,
     227,   231,   235,   236,   237,   241,   242,   246,   247,   251,
     252,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   269,   270,   271,   278,   282,   283,   284,   288,   289,
     290,   294,   295,   296,   297,   298,   302,   303,   304,   308,
     309,   313,   314,   318,   319,   323,   324,   328,   329,   333,
     334,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   353,   354
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHARLIT", "IDENT", "STRING", "NUMBER",
  "INDSEL", "PLUSPLUS", "MINUSMINUS", "SHL", "SHR", "LTEQ", "GTEQ", "EQEQ",
  "NOTEQ", "LOGAND", "LOGOR", "ELLIPSIS", "TIMESEQ", "DIVEQ", "MODEQ",
  "PLUSEQ", "MINUSEQ", "SHLEQ", "SHREQ", "ANDEQ", "OREQ", "XOREQ", "AUTO",
  "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE",
  "ELSE", "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE", "INT",
  "LONG", "REGISTER", "RESTRICT", "RETURN", "SHORT", "SIGNED", "SIZEOF",
  "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "TYPEDEF_NAME", "UNION",
  "UNSIGNED", "VOID", "VOLATILE", "WHILE", "_BOOL", "_COMPLEX",
  "_IMAGINARY", "'('", "')'", "'{'", "'}'", "';'", "'+'", "','", "'='",
  "'['", "']'", "'.'", "'-'", "'!'", "'~'", "'&'", "'*'", "'/'", "'%'",
  "'<'", "'>'", "'|'", "'^'", "'?'", "':'", "$accept", "translation_unit",
  "top_level_declaration", "function_definition", "function_specifier",
  "compound_statement", "$@1", "declaration_or_statement_list",
  "declaration_or_statement", "statement", "declaration",
  "declaration_specifiers", "initialized_declarator_list",
  "identifier_list", "primary_expr", "postfix_expr", "function_call",
  "expression_list", "cast_expr", "unary_expr", "multiplicative_expr",
  "additive_expr", "shift_expr", "relational_expr", "equality_expr",
  "bit_or_expr", "bit_xor_expr", "bit_and_expr", "logical_or_expr",
  "logical_and_expr", "conditional_expr", "assignment_expr", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,    40,    41,   123,
     125,    59,    43,    44,    61,    91,    93,    46,    45,    33,
     126,    38,    42,    47,    37,    60,    62,   124,    94,    63,
      58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    94,    95,    96,    97,
      96,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     102,    95,   103,   104,   104,   105,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   108,   108,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   111,   111,   112,   112,   112,   113,   113,
     113,   114,   114,   114,   114,   114,   115,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     2,     0,
       4,     1,     2,     1,     1,     2,     1,     1,     3,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     4,
       3,     3,     1,     2,     2,     3,     4,     1,     3,     1,
       4,     1,     4,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    20,     0,     2,     5,     0,     4,     0,
       0,    24,     0,     1,     3,     9,     6,    22,     0,     7,
      18,     0,     8,     0,    19,    23,    25,    26,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,    16,
       0,    11,    14,    13,    28,    41,    32,    51,    39,    55,
      58,    61,    66,    73,    77,    69,    71,    79,    75,    81,
      93,     0,     0,     0,    49,    50,     0,     0,     0,    44,
      39,    43,    45,    46,    47,    48,    10,    12,     0,    33,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,    27,    31,
      35,     0,    37,     0,    30,    85,    86,    87,    83,    84,
      88,    89,    90,    91,    92,    82,    52,    53,    54,    56,
      57,    59,    60,    63,    65,    62,    64,    67,    68,    70,
      72,    74,    76,     0,    78,    94,    42,    40,    36,     0,
      29,     0,    38,    80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    39,    23,    40,    41,    42,
       8,     9,    18,    12,    44,    45,    46,   121,    47,    70,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
      50,   -14,    18,   -32,    26,   -72,   -72,   -24,   -72,   -12,
      10,   -72,   -42,   -72,   -72,    21,   -72,   -72,    17,   -72,
     -72,    93,   -72,    75,   -72,   -72,   -72,   -72,   193,   193,
      35,   126,   -72,   209,   209,   209,   209,   209,   209,   -72,
      34,   -72,   -72,   -72,   -72,    42,   -72,   -72,   163,   -27,
     -51,    -1,    -9,    71,    23,    30,    39,     1,    95,   -72,
     -72,   -25,   209,   209,   -72,   -72,    78,    55,   -48,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   121,   -72,
     -72,   172,   209,   122,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   -72,   209,    59,   209,   -72,   -72,
     -72,   -45,   -72,   -29,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -27,
     -27,   -51,   -51,    -1,    -1,    -1,    -1,    -9,    -9,    30,
      39,    71,    95,   -71,    23,   -72,   -72,   -72,   -72,   209,
     -72,   209,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -72,   -72,   125,   -72,   -72,   124,   -72,   -72,    97,   -72,
     -16,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -22,   -23,
      -5,     7,   -69,    -7,    28,    20,    31,    32,   -72,    29,
     -18,    77,   -30
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -22
static const yytype_int16 yytable[] =
{
      48,    68,   115,   102,   103,    64,    65,    43,    48,   100,
     101,    69,    71,    72,    73,    74,    75,    48,   111,   161,
     118,    98,    11,   158,    43,   115,    13,    99,   159,    20,
       1,    21,    68,   143,   144,   145,   146,   -21,    26,    48,
      27,    69,    28,    29,   115,    15,   114,   160,   115,    78,
      79,    80,   123,    10,     1,    95,    96,    97,    48,    48,
      17,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,     2,   136,   137,   138,   104,   105,    19,    26,
       2,    27,   153,    28,    29,   106,   107,    30,    24,    48,
     112,    22,    48,   139,   140,   157,     2,    25,     3,   147,
     148,    31,    66,    15,    76,    32,    33,   141,   142,    81,
     108,   113,    34,    35,    36,    37,    38,    82,   109,    83,
     110,     2,     3,   117,   116,   119,   124,   156,    30,    14,
      26,    16,    27,   154,    28,    29,    48,    77,   151,   149,
     152,   150,    31,   163,    15,     0,    32,    33,     0,     0,
       0,     0,     0,    34,    35,    36,    37,    38,   122,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,    67,     0,     0,     0,    26,     0,    27,    30,
      28,    29,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,   155,    31,     0,     0,     0,    26,    63,    27,
       0,    28,    29,     0,    34,    35,    36,    37,    38,     0,
       0,     0,     0,    26,     0,    27,     0,    28,    29,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   162,    94,     0,    31,
     120,     0,     0,     0,    63,     0,    30,     0,     0,     0,
      34,    35,    36,    37,    38,     0,     0,     0,     0,     0,
      62,     0,    30,     0,     0,    63,     0,     0,     0,     0,
       0,    34,    35,    36,    37,    38,    31,     0,     0,     0,
       0,    63,     0,     0,     0,     0,     0,    34,    35,    36,
      37,    38
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-72))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      23,    31,    73,    12,    13,    28,    29,    23,    31,    10,
      11,    33,    34,    35,    36,    37,    38,    40,    17,    90,
      68,    72,     4,    68,    40,    73,     0,    78,    73,    71,
       4,    73,    62,   102,   103,   104,   105,    69,     4,    62,
       6,    63,     8,     9,    73,    69,    71,    76,    73,     7,
       8,     9,    82,    67,     4,    82,    83,    84,    81,    82,
      72,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    46,    95,    96,    97,    85,    86,    68,     4,
      46,     6,   112,     8,     9,    14,    15,    53,    71,   112,
      89,    70,   115,    98,    99,   117,    46,     4,    72,   106,
     107,    67,    67,    69,    70,    71,    72,   100,   101,    67,
      87,    16,    78,    79,    80,    81,    82,    75,    88,    77,
      81,    46,    72,    68,    46,     4,     4,    68,    53,     4,
       4,     7,     6,   113,     8,     9,   159,    40,   110,   108,
     111,   109,    67,   161,    69,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    81,    -1,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    46,    -1,    -1,    -1,     4,    -1,     6,    53,
       8,     9,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,   115,    67,    -1,    -1,    -1,     4,    72,     6,
      -1,     8,     9,    -1,    78,    79,    80,    81,    82,    -1,
      -1,    -1,    -1,     4,    -1,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   159,    74,    -1,    67,
      68,    -1,    -1,    -1,    72,    -1,    53,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    53,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    67,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    46,    72,    92,    93,    94,    95,   101,   102,
      67,     4,   104,     0,    93,    69,    96,    72,   103,    68,
      71,    73,    70,    97,    71,     4,     4,     6,     8,     9,
      53,    67,    71,    72,    78,    79,    80,    81,    82,    96,
      98,    99,   100,   101,   105,   106,   107,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,    67,    72,   110,   110,    67,    46,   123,   109,
     110,   109,   109,   109,   109,   109,    70,    99,     7,     8,
       9,    67,    75,    77,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    74,    82,    83,    84,    72,    78,
      10,    11,    12,    13,    85,    86,    14,    15,    87,    88,
      81,    17,    89,    16,    71,    73,    46,    68,    68,     4,
      68,   108,   122,   123,     4,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   109,   109,   109,   111,
     111,   112,   112,   113,   113,   113,   113,   114,   114,   117,
     118,   115,   120,   123,   116,   122,    68,   109,    68,    73,
      76,    90,   122,   121
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:

/* Line 1806 of yacc.c  */
#line 102 "esparser.y"
    {
		//no parameters currently
                insert_symbol((yyvsp[(1) - (3)].yystring));
        }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 109 "esparser.y"
    { (yyval.nil) = NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 110 "esparser.y"
    { //midaction rule
                if (curr->scope_type == FILE_SCOPE)
                        curr = symTable_new(FUNCTION_SCOPE, lineno, filename, curr);
                else
                        curr = symTable_new(BLOCK_SCOPE, lineno, filename, curr);
        }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 115 "esparser.y"
    {
                curr = symTable_pop(curr);
        }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 186 "esparser.y"
    { insert_symbol((yyvsp[(3) - (3)].yystring)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 187 "esparser.y"
    { insert_symbol((yyvsp[(1) - (1)].yystring)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 195 "esparser.y"
    {
		char *ident = yylval.yystring;
		ident[strlen(yylval.yystring)] = '\0';
		fprintf(stderr, "ident: %s\n", ident);
                struct symbol *s = symTable_getSymbol(curr, (yyvsp[(1) - (1)].yystring), curr->scope_type);
		//symTable_print(curr);
		//fprintf(stderr, "sym: %d\n", (long long)s);
		if (s != NULL) (yyval.number.yyint) = (long long)s;
                else {
                        (yyval.number.yyint) = 0;
                        fprintf(stderr, "Undefined identifier %s\n", (yyvsp[(1) - (1)].yystring));
                }
        }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 208 "esparser.y"
    {
	
                if ((yyvsp[(1) - (1)].number).num_type == TYPE_INT || (yyvsp[(1) - (1)].number).num_type == TYPE_LONG || (yyvsp[(1) - (1)].number).num_type == TYPE_LONGLONG)
                        (yyval.number.yyint) = yylval.number.yyint;
                else {
                        (yyval.number.yyint) = (long long)yylval.number.yydouble;
                        fprintf(stderr,"Truncating real number %Lg to integer %lld\n",yylval.number.yydouble,(yyval.number.yyint));
                        printf("exprval=%lld\n",(yyval.number.yyint));
                }
        }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 218 "esparser.y"
    { (yyval.number.yyint) = (long long)(yyvsp[(2) - (3)].number.yyint); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 223 "esparser.y"
    {
                fprintf(stderr, "Arrays not implemented\n");
                (yyval.number.yyint) = 0;
        }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 227 "esparser.y"
    {
                fprintf(stderr, "component-selection not implemented\n");
                (yyval.number.yyint) = 0;
        }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 231 "esparser.y"
    {
                fprintf(stderr, "component-selection not implemented\n");
                (yyval.number.yyint) = 0;
        }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 236 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (2)].number.yyint)++; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 237 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (2)].number.yyint)--; }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 252 "esparser.y"
    {(yyval.number.yyint) = (int)(yyvsp[(4) - (4)].number.yyint); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 257 "esparser.y"
    { (yyval.number.yyint) = sizeof(long long); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 258 "esparser.y"
    { (yyval.number.yyint) = -(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 259 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(2) - (2)].number.yyint);  printf("exprval=%lld\n",(yyval.number.yyint)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 260 "esparser.y"
    { (yyval.number.yyint) = !(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 261 "esparser.y"
    { (yyval.number.yyint) = ~(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 262 "esparser.y"
    { (yyval.number.yyint) = (long long) &(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 263 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(2) - (2)].number.yyint); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 264 "esparser.y"
    { (yyval.number.yyint) = ++(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 265 "esparser.y"
    { (yyval.number.yyint) = --(yyvsp[(2) - (2)].number.yyint); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 270 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) * (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 271 "esparser.y"
    {
		if ((yyvsp[(3) - (3)].number.yyint) != 0) (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) / (yyvsp[(3) - (3)].number.yyint);
		else {
		        fprintf(stderr, "Parse Error: divide by 0\n");
		        (yyval.number.yyint) = 0;
		}
        }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 278 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) % (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 283 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) + (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 284 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) - (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 289 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) << (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 290 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) >> (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 295 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) < (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 296 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) <= (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 297 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) > (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 298 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) >= (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 303 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) == (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 304 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) != (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 309 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) | (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 314 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) ^ (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 319 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) & (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 324 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) || (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 329 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) && (yyvsp[(3) - (3)].number.yyint); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 334 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (5)].number.yyint) ? (yyvsp[(3) - (5)].number.yyint) : (yyvsp[(5) - (5)].number.yyint); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 339 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(3) - (3)].number.yyint);printf( "exprval=%lld\n", (yyval.number.yyint)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 340 "esparser.y"
    {(yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) + (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 341 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) - (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint);}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 342 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) * (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 343 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) / (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 344 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) % (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 345 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) << (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 346 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) >> (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 347 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) & (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 348 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) | (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 349 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) ^ (yyvsp[(3) - (3)].number.yyint);(yyvsp[(1) - (3)].number.yyint) = (yyval.number.yyint); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 354 "esparser.y"
    { (yyval.number.yyint) = (yyvsp[(3) - (3)].number.yyint); }
    break;



/* Line 1806 of yacc.c  */
#line 2098 "esparser.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 357 "esparser.y"


void insert_symbol(char *s){

	struct symbol *st = sym_new(filename, lineno);
	if(symTable_push(curr, s, st, curr->scope_type) != TRUE){
		st = symTable_getSymbol(curr,s, curr->scope_type);
		fprintf(stderr, "Error: %s previously defined around %s:%d\n", s, st->filename, st->linenumber);
	}
symTable_print(curr);
//fprintf(stderr, "sym val: %s with %lld\n", s,st->value);
}

void yyerror(const char *s){
	fprintf(stderr, "Parse Error: unrecognized syntax:: %s\n", s);
}

main(){

	printf("parsing..\n");

	strcpy(filename, "<stdin>");	
	curr= symTable_new(FILE_SCOPE, lineno, filename, NULL);
	yyparse();

	printf("EOF\n");
}

