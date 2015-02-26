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
#line 2 "esparser.y"

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
#include "hash.h"
#include "sym_table.h"

int debug = 0;

extern int yylex();
extern int yyparse();
int yyleng;
int lineno;
char filename[256];
FILE *yyin;
void yyerror (const char *s);
void insert_symbol(char *s);

struct sym_table *curr;



/* Line 268 of yacc.c  */
#line 105 "esparser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 35 "esparser.y"


	char yychar;
        char *yystring;

        struct number{
                enum number_type num_type;
                enum number_type num_sign;
                unsigned long long int yyint;
                long double yydouble;
        }number;
	
struct symbol *lval;



/* Line 293 of yacc.c  */
#line 224 "esparser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 236 "esparser.tab.c"

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  187

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
       2,     2,     2,    82,     2,     2,     2,    85,    84,     2,
      72,    73,    69,    68,    77,    67,    81,    70,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    90,    76,
      86,    78,    87,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    79,     2,    80,    71,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    88,    75,    83,     2,     2,     2,
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
      23,    28,    30,    33,    35,    37,    41,    45,    47,    49,
      52,    54,    56,    60,    65,    67,    71,    74,    79,    82,
      84,    87,    91,    94,    96,    98,   100,   102,   104,   108,
     110,   114,   119,   123,   127,   131,   136,   139,   142,   150,
     157,   159,   161,   166,   168,   173,   176,   179,   182,   185,
     188,   191,   194,   197,   199,   203,   207,   211,   213,   217,
     221,   223,   227,   231,   233,   237,   241,   245,   249,   251,
     255,   259,   261,   265,   267,   271,   273,   277,   279,   283,
     285,   289,   291,   297,   299,   303,   307,   311,   315,   319,
     323,   327,   331,   335,   339,   343,   347,   349
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      92,     0,    -1,    93,    -1,    92,    93,    -1,   100,    -1,
      94,    -1,    95,    96,    -1,     4,    72,    73,    -1,    74,
      75,    -1,    -1,    74,    97,    98,    75,    -1,    99,    -1,
      98,    99,    -1,   100,    -1,   102,    -1,    46,   101,    76,
      -1,   101,    77,     4,    -1,     4,    -1,    96,    -1,   126,
      76,    -1,    76,    -1,   125,    -1,    74,   104,    75,    -1,
      74,   104,    77,    75,    -1,   103,    -1,   104,    77,   103,
      -1,   105,   103,    -1,   104,    77,   105,   103,    -1,   106,
      78,    -1,   107,    -1,   106,   107,    -1,    79,   108,    80,
      -1,    81,     4,    -1,   124,    -1,     4,    -1,     6,    -1,
       3,    -1,     5,    -1,    72,   126,    73,    -1,   125,    -1,
     110,    77,   125,    -1,   111,    79,   126,    80,    -1,   111,
      81,     4,    -1,   111,     7,     4,    -1,   111,    72,    73,
      -1,   111,    72,   110,    73,    -1,   127,     8,    -1,   127,
       9,    -1,    72,    46,    73,    74,   104,    77,    75,    -1,
      72,    46,    73,    74,   104,    75,    -1,   109,    -1,   113,
      -1,    72,    46,    73,   112,    -1,   111,    -1,    53,    72,
      46,    73,    -1,    67,   112,    -1,    68,   112,    -1,    82,
     112,    -1,    83,   112,    -1,    84,   112,    -1,    69,   112,
      -1,     8,   127,    -1,     9,   127,    -1,   112,    -1,   114,
      69,   112,    -1,   114,    70,   112,    -1,   114,    85,   112,
      -1,   114,    -1,   115,    68,   114,    -1,   115,    67,   114,
      -1,   115,    -1,   116,    10,   115,    -1,   116,    11,   115,
      -1,   116,    -1,   117,    86,   116,    -1,   117,    12,   116,
      -1,   117,    87,   116,    -1,   117,    13,   116,    -1,   117,
      -1,   118,    14,   117,    -1,   118,    15,   117,    -1,   120,
      -1,   119,    88,   120,    -1,   121,    -1,   120,    71,   121,
      -1,   118,    -1,   121,    84,   118,    -1,   119,    -1,   122,
      16,   119,    -1,   122,    -1,   123,    17,   122,    -1,   123,
      -1,   123,    89,   126,    90,   124,    -1,   124,    -1,   127,
      78,   125,    -1,   127,    19,   125,    -1,   127,    20,   125,
      -1,   127,    21,   125,    -1,   127,    22,   125,    -1,   127,
      23,   125,    -1,   127,    24,   125,    -1,   127,    25,   125,
      -1,   127,    26,   125,    -1,   127,    27,   125,    -1,   127,
      28,   125,    -1,   126,    77,   125,    -1,   125,    -1,     4,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    75,    79,    80,    84,    88,    95,    96,
      96,   112,   113,   117,   118,   122,   126,   129,   135,   136,
     139,   143,   144,   145,   149,   150,   151,   152,   156,   160,
     161,   165,   166,   170,   174,   183,   197,   201,   204,   210,
     211,   215,   220,   224,   228,   229,   230,   237,   244,   248,
     251,   255,   256,   263,   264,   268,   271,   275,   278,   281,
     285,   289,   296,   306,   307,   310,   318,   324,   325,   328,
     334,   335,   338,   345,   346,   349,   352,   355,   361,   362,
     365,   371,   372,   378,   379,   385,   386,   392,   393,   399,
     400,   406,   407,   413,   414,   418,   422,   426,   430,   434,
     438,   442,   446,   450,   454,   461,   464,   468
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
  "_IMAGINARY", "'-'", "'+'", "'*'", "'/'", "'^'", "'('", "')'", "'{'",
  "'}'", "';'", "','", "'='", "'['", "']'", "'.'", "'!'", "'~'", "'&'",
  "'%'", "'<'", "'>'", "'|'", "'?'", "':'", "$accept", "translation_unit",
  "top_level_declaration", "function_definition",
  "function_definition_specifier", "compound_statement", "$@1",
  "declaration_or_statement_list", "declaration_or_statement",
  "declaration", "identifier_list", "statement", "initializer",
  "initializer_list", "designation", "designator_list", "designator",
  "constant_e", "primary_e", "expression_list", "postfix_e", "cast_e",
  "unary_e", "multiplicative_e", "additive_e", "shift_e", "relational_e",
  "equality_e", "or_e", "xor_e", "and_e", "logical_and_e", "logical_or_e",
  "conditional_e", "assignment_e", "generic_e", "lval", 0
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
     315,   316,   317,   318,   319,   320,   321,    45,    43,    42,
      47,    94,    40,    41,   123,   125,    59,    44,    61,    91,
      93,    46,    33,   126,    38,    37,    60,    62,   124,    63,
      58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    94,    95,    96,    97,
      96,    98,    98,    99,    99,   100,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   105,   106,
     106,   107,   107,   108,   109,   109,   109,   109,   109,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   114,   114,   114,   114,   115,   115,   115,
     116,   116,   116,   117,   117,   117,   117,   117,   118,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   126,   126,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     2,     0,
       4,     1,     2,     1,     1,     3,     3,     1,     1,     2,
       1,     1,     3,     4,     1,     3,     2,     4,     2,     1,
       2,     3,     2,     1,     1,     1,     1,     1,     3,     1,
       3,     4,     3,     3,     3,     4,     2,     2,     7,     6,
       1,     1,     4,     1,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     5,     0,     4,     0,    17,
       0,     1,     3,     9,     6,     7,    15,     0,     8,     0,
      16,    36,    34,    37,    35,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,     0,    18,     0,    11,    13,
      14,    50,    53,    63,    51,    67,    70,    73,    78,    85,
      87,    81,    83,    89,    91,    93,   106,     0,     0,   107,
      61,    62,     0,    55,     0,    56,    60,     0,     0,    57,
      58,    59,    10,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,    46,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    43,    44,     0,    39,     0,
      42,    64,    65,    66,    69,    68,    71,    72,    75,    77,
      74,    76,    79,    80,    82,    84,    86,    88,    90,     0,
     105,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    94,    54,     0,    52,    45,     0,    41,     0,     0,
       0,     0,    24,     0,     0,     0,    29,    21,    40,    92,
       0,     0,    33,    32,    49,     0,    26,    28,    30,    22,
       0,    31,    48,    25,     0,    23,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    36,    19,    37,    38,     7,
      10,    40,   162,   163,   164,   165,   166,   171,    41,   117,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   167,    57,    64
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -166
static const yytype_int16 yypact[] =
{
      -2,   -61,    34,     1,  -166,  -166,   -15,  -166,     8,  -166,
      -6,  -166,  -166,    19,  -166,  -166,  -166,   125,  -166,   209,
    -166,  -166,    41,  -166,  -166,   142,   142,    49,   384,   384,
     384,   263,  -166,   384,   384,   384,  -166,   109,  -166,  -166,
    -166,  -166,    44,  -166,  -166,   -66,    43,   117,    10,   124,
      61,    81,    70,   143,    -9,  -166,  -166,    65,   400,  -166,
    -166,  -166,   114,  -166,   135,  -166,  -166,    90,   -38,  -166,
    -166,  -166,  -166,  -166,   160,   291,   384,   166,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,  -166,   384,  -166,
    -166,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   100,   298,  -166,  -166,  -166,   -37,  -166,   -63,
    -166,  -166,  -166,  -166,   -66,   -66,    43,    43,   117,   117,
     117,   117,    10,    10,    81,    70,   124,    61,   143,   -57,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   245,  -166,  -166,   384,  -166,   384,   245,
     384,   170,  -166,   -29,   333,   -36,  -166,  -166,  -166,  -166,
      45,    95,  -166,  -166,  -166,   127,  -166,  -166,  -166,  -166,
     163,  -166,  -166,  -166,   333,  -166,  -166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,   176,  -166,  -166,   180,  -166,  -166,   145,   -10,
    -166,  -166,  -143,    28,  -165,  -166,    23,  -166,  -166,  -166,
    -166,    -4,  -166,    66,    67,   -33,    68,    96,   103,    99,
     106,   105,  -166,   -34,    -3,   -18,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -108
static const yytype_int16 yytable[] =
{
      58,    11,     1,    78,    79,     1,    60,    61,    95,    39,
     184,     8,    58,    68,    98,   184,    56,   157,    58,    80,
      98,   176,    85,    86,    63,    65,    66,    39,    56,    69,
      70,    71,   183,   158,    56,   114,   155,   183,     9,    98,
     156,   186,   177,   160,     2,   161,   174,     2,   175,  -107,
    -107,    74,   128,   129,   130,   131,    58,    58,   119,    13,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
      16,    17,   118,    56,   121,   122,   123,    58,   139,    58,
      96,    15,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    56,    18,   140,    87,    88,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   154,
      81,    82,    21,    22,    23,    24,    75,    25,    26,  -107,
     179,    62,   180,    76,   169,    77,   172,    83,    84,    20,
      21,    22,    23,    24,    58,    25,    26,    58,    89,    90,
      58,    97,    98,    99,   100,    58,    59,   124,   125,    91,
     126,   127,    92,   168,    93,     2,    58,   132,   133,    94,
     112,    58,    27,   113,   115,    58,    21,    22,    23,    24,
     120,    25,    26,   152,   173,   181,    28,    29,    30,    12,
      27,    31,    73,    13,    72,    32,    14,   170,   178,   136,
     134,    33,    34,    35,    28,    29,    30,   137,   135,    31,
     138,   159,   182,     0,     0,     0,   160,     0,   161,    33,
      34,    35,    21,    22,    23,    24,    27,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    30,     0,     0,    31,     0,   159,   185,     0,
       0,     0,   160,     0,   161,    33,    34,    35,    21,    22,
      23,    24,     0,    25,    26,     2,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,    21,    22,    23,    24,
       0,    25,    26,     0,     0,     0,    28,    29,    30,     0,
       0,    31,     0,    13,     0,    32,     0,     0,     0,     0,
       0,    33,    34,    35,    21,    22,    23,    24,    27,    25,
      26,    21,    22,    23,    24,     0,    25,    26,     0,    67,
       0,     0,    28,    29,    30,     0,    27,    31,     0,   159,
       0,     0,     0,     0,   160,     0,   161,    33,    34,    35,
      28,    29,    30,     0,     0,    31,    21,    22,    23,    24,
       0,    25,    26,     0,    27,    33,    34,    35,     0,     0,
       0,    27,     0,     0,     0,     0,     0,     0,    28,    29,
      30,     0,     0,    31,   116,    28,    29,    30,     0,     0,
      31,     0,   153,    33,    34,    35,     0,     0,     0,     0,
      33,    34,    35,     0,     0,     0,    27,    21,    22,    23,
      24,     0,    25,    26,     0,     0,     0,     0,     0,     0,
      28,    29,    30,     0,     0,    31,     0,   159,    99,   100,
       0,     0,     0,     0,     0,    33,    34,    35,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-166))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      19,     0,     4,    69,    70,     4,    25,    26,    17,    19,
     175,    72,    31,    31,    77,   180,    19,    80,    37,    85,
      77,   164,    12,    13,    28,    29,    30,    37,    31,    33,
      34,    35,   175,    90,    37,    73,    73,   180,     4,    77,
      77,   184,    78,    79,    46,    81,    75,    46,    77,     8,
       9,     7,    85,    86,    87,    88,    75,    76,    76,    74,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      76,    77,    75,    76,    78,    79,    80,    96,    96,    98,
      89,    73,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    96,    75,    98,    86,    87,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   113,
      67,    68,     3,     4,     5,     6,    72,     8,     9,    78,
      75,    72,    77,    79,   158,    81,   160,    10,    11,     4,
       3,     4,     5,     6,   153,     8,     9,   156,    14,    15,
     159,    76,    77,     8,     9,   164,     4,    81,    82,    88,
      83,    84,    71,   156,    84,    46,   175,    89,    90,    16,
      46,   180,    53,    73,     4,   184,     3,     4,     5,     6,
       4,     8,     9,    73,     4,    80,    67,    68,    69,     3,
      53,    72,    37,    74,    75,    76,     6,   159,   165,    93,
      91,    82,    83,    84,    67,    68,    69,    94,    92,    72,
      95,    74,    75,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,     3,     4,     5,     6,    53,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    -1,    -1,    72,    -1,    74,    75,    -1,
      -1,    -1,    79,    -1,    81,    82,    83,    84,     3,     4,
       5,     6,    -1,     8,     9,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    67,    68,    69,    -1,
      -1,    72,    -1,    74,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    82,    83,    84,     3,     4,     5,     6,    53,     8,
       9,     3,     4,     5,     6,    -1,     8,     9,    -1,    46,
      -1,    -1,    67,    68,    69,    -1,    53,    72,    -1,    74,
      -1,    -1,    -1,    -1,    79,    -1,    81,    82,    83,    84,
      67,    68,    69,    -1,    -1,    72,     3,     4,     5,     6,
      -1,     8,     9,    -1,    53,    82,    83,    84,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    -1,    -1,    72,    73,    67,    68,    69,    -1,    -1,
      72,    -1,    74,    82,    83,    84,    -1,    -1,    -1,    -1,
      82,    83,    84,    -1,    -1,    -1,    53,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    -1,    -1,    72,    -1,    74,     8,     9,
      -1,    -1,    -1,    -1,    -1,    82,    83,    84,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    -1,    -1,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    46,    92,    93,    94,    95,   100,    72,     4,
     101,     0,    93,    74,    96,    73,    76,    77,    75,    97,
       4,     3,     4,     5,     6,     8,     9,    53,    67,    68,
      69,    72,    76,    82,    83,    84,    96,    98,    99,   100,
     102,   109,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     4,
     127,   127,    72,   112,   127,   112,   112,    46,   126,   112,
     112,   112,    75,    99,     7,    72,    79,    81,    69,    70,
      85,    67,    68,    10,    11,    12,    13,    86,    87,    14,
      15,    88,    71,    84,    16,    17,    89,    76,    77,     8,
       9,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    78,    46,    73,    73,     4,    73,   110,   125,   126,
       4,   112,   112,   112,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   117,   120,   121,   118,   119,   122,   126,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,    73,    74,   112,    73,    77,    80,    90,    74,
      79,    81,   103,   104,   105,   106,   107,   125,   125,   124,
     104,   108,   124,     4,    75,    77,   103,    78,   107,    75,
      77,    80,    75,   103,   105,    75,   103
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
#line 88 "esparser.y"
    {
                //currently no declarations supported
                insert_symbol((yyvsp[(1) - (3)].yystring));
        }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 96 "esparser.y"
    {
                enum scope_type scope;
                if (curr->scope_type == FILE_SCOPE) {
                        //compound statement is attached to a function
                        scope = FUNCTION_SCOPE;
                } else {
                        //compound statement is a block
                        scope = BLOCK_SCOPE;
                }
                curr = symTable_new(scope, lineno, filename, curr);
        }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 106 "esparser.y"
    {
                curr = symTable_pop(curr);
        }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 126 "esparser.y"
    {
                insert_symbol((yyvsp[(3) - (3)].yystring));
        }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 129 "esparser.y"
    {
                insert_symbol((yyvsp[(1) - (1)].yystring));
        }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 136 "esparser.y"
    {
                //fprintf(stderr, "Parse error expression value = %lld", $1);
        }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 174 "esparser.y"
    {
                struct symbol *s = symTable_getSymbol(curr, (yyvsp[(1) - (1)].yystring));
                if (s) {
                        (yyval.number.yyint) = s->value;
                } else {
                        (yyval.number.yyint) = 0;
                        fprintf(stderr, "Undefined identifier %s", (yyvsp[(1) - (1)].yystring));
                }
        }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 183 "esparser.y"
    {
                if ((yyvsp[(1) - (1)].number).num_type == TYPE_INT ||
                    (yyvsp[(1) - (1)].number).num_type == TYPE_LONG ||
                    (yyvsp[(1) - (1)].number).num_type == TYPE_LONGLONG) {
                        (yyval.number.yyint) = (yyvsp[(1) - (1)].number).yyint;
                } else {
                        (yyval.number.yyint) = (long long)(yyvsp[(1) - (1)].number).yydouble;
                        fprintf(stderr,
                                "Truncating real number %Lg to integer %lld",
                                (yyvsp[(1) - (1)].number).yydouble,
                                (yyval.number.yyint));
                        printf("exprval=%lld",(yyval.number.yyint));
                }
        }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 197 "esparser.y"
    {
                //TODO: handle other types
                (yyval.number.yyint) = (long long)(yyvsp[(1) - (1)].yychar);
        }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 201 "esparser.y"
    {
                (yyval.number.yyint) = (long long)(yyvsp[(1) - (1)].yystring);
        }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 204 "esparser.y"
    {
                (yyval.number.yyint) = (long long)(yyvsp[(2) - (3)].number.yyint);
        }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 215 "esparser.y"
    {
                //TODO: add support
                fprintf(stderr, "Arrays not implemented");
                (yyval.number.yyint) = 0;
        }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 220 "esparser.y"
    {
                fprintf(stderr, "Struct/union not implemented");
                (yyval.number.yyint) = 0;
        }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 224 "esparser.y"
    {
                fprintf(stderr, "Struct/union not implemented");
                (yyval.number.yyint) = 0;
        }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 230 "esparser.y"
    {
                if ((yyvsp[(1) - (2)].lval)) {
                        (yyval.number.yyint) = (yyvsp[(1) - (2)].lval)->value++;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 237 "esparser.y"
    {
                if ((yyvsp[(1) - (2)].lval)) {
                        (yyval.number.yyint) = (yyvsp[(1) - (2)].lval)->value--;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 244 "esparser.y"
    {
                //TODO: change later for more types
                (yyval.number.yyint) = 1;
        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 248 "esparser.y"
    {
                (yyval.number.yyint) = 1;
        }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 256 "esparser.y"
    {
                //TODO: add other types later
                (yyval.number.yyint) = (long long)(yyvsp[(4) - (4)].number.yyint);
        }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 264 "esparser.y"
    {
                //TODO: add other types later
                (yyval.number.yyint) = sizeof(long long);
        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 268 "esparser.y"
    {
                (yyval.number.yyint) = -(yyvsp[(2) - (2)].number.yyint);
        }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 271 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(2) - (2)].number.yyint);
                printf("exprval=%lld",(yyval.number.yyint));
        }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 275 "esparser.y"
    {
                (yyval.number.yyint) = !(yyvsp[(2) - (2)].number.yyint);
        }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 278 "esparser.y"
    {
                (yyval.number.yyint) = ~(yyvsp[(2) - (2)].number.yyint);
        }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 281 "esparser.y"
    {
                //TODO: change later since address
                (yyval.number.yyint) = (long long) &(yyvsp[(2) - (2)].number.yyint);
        }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 285 "esparser.y"
    {
                //TODO: no pointers yet
                (yyval.number.yyint) = (yyvsp[(2) - (2)].number.yyint);
        }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 289 "esparser.y"
    {
                if ((yyvsp[(2) - (2)].lval)) {
                        (yyval.number.yyint) = ++(yyvsp[(2) - (2)].lval)->value;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 296 "esparser.y"
    {
                if ((yyvsp[(2) - (2)].lval)) {
                        (yyval.number.yyint) = --(yyvsp[(2) - (2)].lval)->value;
                } else {
                        fprintf(stderr, "symbol undefined");
                }
        }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 307 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) * (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 310 "esparser.y"
    {
                if ((yyvsp[(3) - (3)].number.yyint)) {
                        (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) / (yyvsp[(3) - (3)].number.yyint);
                } else {
                        fprintf(stderr, "divide by 0");
                        (yyval.number.yyint) = 0;
                }
        }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 318 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) % (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 325 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) + (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 328 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) - (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 335 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) << (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 338 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) >> (yyvsp[(3) - (3)].number.yyint);
                printf("exprval=%lld",(yyval.number.yyint));
        }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 346 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) < (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 349 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) <= (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 352 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) > (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 355 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) >= (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 362 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) == (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 365 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) != (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 372 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) | (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 379 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) ^ (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 386 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) & (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 393 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) && (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 400 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].number.yyint) || (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 407 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (5)].number.yyint) ? (yyvsp[(3) - (5)].number.yyint) : (yyvsp[(5) - (5)].number.yyint);
        }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 414 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(3) - (3)].number.yyint);
                printf( "exprval=%lld", (yyval.number.yyint));
        }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 418 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value * (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 422 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value / (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 426 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value % (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 430 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value + (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 434 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value - (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 438 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value << (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 442 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value >> (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 446 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value & (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 450 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value | (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 454 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(1) - (3)].lval)->value ^ (yyvsp[(3) - (3)].number.yyint);
                (yyvsp[(1) - (3)].lval)->value = (yyval.number.yyint);
        }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 461 "esparser.y"
    {
                (yyval.number.yyint) = (yyvsp[(3) - (3)].number.yyint);
        }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 468 "esparser.y"
    {
                struct symbol *s = symTable_getSymbol(curr, (yyvsp[(1) - (1)].yystring));
                if (s) {
                        (yyval.lval) = s;
                } else {
                        fprintf(stderr, "Unidentified identifier %s", (yyvsp[(1) - (1)].yystring));
                        (yyval.lval) = 0;
                }
        }
    break;



/* Line 1806 of yacc.c  */
#line 2325 "esparser.tab.c"
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
#line 484 "esparser.y"



void insert_symbol(char *s){

	struct symbol *st = sym_new(filename, lineno);
	if(symTable_push(curr, s, st) != FALSE){
		st = symTable_getSymbol(curr,s);
		fprintf(stderr, "Error: %s previously defined in %s:%d\n", s, st->filename, st->linenumber);
	}
}

void yyerror(const char *s){
	fprintf(stderr, "Parse Error: unrecognized syntax:: %s\n", s);
}

main(){

	printf("parsing..\n");

//	yyin = stdin;	
	curr= symTable_new(FILE_SCOPE, lineno, filename, NULL);
	yyparse();
	printf("EOF\n");
}


