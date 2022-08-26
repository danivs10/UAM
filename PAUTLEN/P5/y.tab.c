/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "alfa.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "alfa.h"

    void yyerror(const char* e);
    extern int yylex();
    extern FILE *yyin;
    extern FILE *yyout;
    extern char *yytext;
    extern int yyleng;
    extern int l;
    extern int pos;
    extern int e;

    int tipo_actual;
    int clase_actual;

    int value_scalar_actual;        /* Scalar value*/
    int vector_size;                /* Vector size */

    int pos_local_var_act=0;        /* Actual local variable position */
    int loc_var_num=0;              /* Number of local variables*/
    int param_act_num = 0;          /* Actual number of parametres */
    int pos_param_act = 0;          /* Actual parametre position */
    int param_call_act_num = 0;     /* Actual number of parametres in a call */
    int en_explist = 0;
    int vector_size_act = 0;        /* Actual size of the vector*/

    Hash_Table *GlobalTable;        /* Global table of symbols */
    Hash_Table *LocalTable;         /* Local table of symbols */
    Hash_Table *CurrentTable=NULL;       /* Indicates if we are in the local table or in the global */

    Simbol *aux=NULL;

    int is_func = 0;                /* Indicates if we are passing a parametre in the funccion */
    int fn_return = 0;              /* Indicates if it is return */
    int return_type = 0;            /* Indicates the return type*/
    int num_no = 0;                 /* Number of arithmetic negations */
    int num_comp = 0;               /* Number of comparations */
    int num_cond = 1;               /* Number of conditions */
    int en_explist;                 /* Function instead of parameter */  
    int num_loop = 0;               /* Counter for the loops operations */
    int num_parametros_llamada_actual;/*Numero de parametros de la llamada actual*/

#line 114 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_CONSTANTE_ENTERA = 258,
    TOK_CONSTANTE_REAL = 259,
    TOK_IDENTIFICADOR = 260,
    TOK_MAIN = 261,
    TOK_INT = 262,
    TOK_BOOLEAN = 263,
    TOK_ARRAY = 264,
    TOK_FUNCTION = 265,
    TOK_IF = 266,
    TOK_ELSE = 267,
    TOK_WHILE = 268,
    TOK_SCANF = 269,
    TOK_PRINTF = 270,
    TOK_RETURN = 271,
    TOK_PUNTOYCOMA = 272,
    TOK_COMA = 273,
    TOK_PARENTESISIZQUIERDO = 274,
    TOK_PARENTESISDERECHO = 275,
    TOK_CORCHETEIZQUIERDO = 276,
    TOK_CORCHETEDERECHO = 277,
    TOK_LLAVEIZQUIERDA = 278,
    TOK_LLAVEDERECHA = 279,
    TOK_ASIGNACION = 280,
    TOK_MAS = 281,
    TOK_MENOS = 282,
    TOK_DIVISION = 283,
    TOK_ASTERISCO = 284,
    TOK_AND = 285,
    TOK_OR = 286,
    TOK_NOT = 287,
    TOK_IGUAL = 288,
    TOK_DISTINTO = 289,
    TOK_MENORIGUAL = 290,
    TOK_MAYORIGUAL = 291,
    TOK_MENOR = 292,
    TOK_MAYOR = 293,
    TOK_TRUE = 294,
    TOK_FALSE = 295,
    TOK_ERROR = 296
  };
#endif
/* Tokens.  */
#define TOK_CONSTANTE_ENTERA 258
#define TOK_CONSTANTE_REAL 259
#define TOK_IDENTIFICADOR 260
#define TOK_MAIN 261
#define TOK_INT 262
#define TOK_BOOLEAN 263
#define TOK_ARRAY 264
#define TOK_FUNCTION 265
#define TOK_IF 266
#define TOK_ELSE 267
#define TOK_WHILE 268
#define TOK_SCANF 269
#define TOK_PRINTF 270
#define TOK_RETURN 271
#define TOK_PUNTOYCOMA 272
#define TOK_COMA 273
#define TOK_PARENTESISIZQUIERDO 274
#define TOK_PARENTESISDERECHO 275
#define TOK_CORCHETEIZQUIERDO 276
#define TOK_CORCHETEDERECHO 277
#define TOK_LLAVEIZQUIERDA 278
#define TOK_LLAVEDERECHA 279
#define TOK_ASIGNACION 280
#define TOK_MAS 281
#define TOK_MENOS 282
#define TOK_DIVISION 283
#define TOK_ASTERISCO 284
#define TOK_AND 285
#define TOK_OR 286
#define TOK_NOT 287
#define TOK_IGUAL 288
#define TOK_DISTINTO 289
#define TOK_MENORIGUAL 290
#define TOK_MAYORIGUAL 291
#define TOK_MENOR 292
#define TOK_MAYOR 293
#define TOK_TRUE 294
#define TOK_FALSE 295
#define TOK_ERROR 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "alfa.y" /* yacc.c:355  */

    char *string;
    int number;
    type_atributes atributos;

#line 242 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   132,   132,   138,   148,   159,   165,   169,   175,   181,
     186,   192,   197,   202,   208,   219,   223,   228,   232,   237,
     265,   281,   315,   319,   324,   328,   333,   338,   371,   375,
     380,   384,   389,   393,   398,   402,   406,   410,   415,   419,
     424,   454,   476,   514,   519,   524,   529,   541,   546,   553,
     559,   586,   593,   607,   619,   631,   643,   655,   667,   680,
     693,   706,   744,   754,   760,   766,   772,   798,   803,   808,
     814,   819,   825,   838,   851,   864,   877,   890,   904,   912,
     922,   930,   939,   953
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_CONSTANTE_ENTERA",
  "TOK_CONSTANTE_REAL", "TOK_IDENTIFICADOR", "TOK_MAIN", "TOK_INT",
  "TOK_BOOLEAN", "TOK_ARRAY", "TOK_FUNCTION", "TOK_IF", "TOK_ELSE",
  "TOK_WHILE", "TOK_SCANF", "TOK_PRINTF", "TOK_RETURN", "TOK_PUNTOYCOMA",
  "TOK_COMA", "TOK_PARENTESISIZQUIERDO", "TOK_PARENTESISDERECHO",
  "TOK_CORCHETEIZQUIERDO", "TOK_CORCHETEDERECHO", "TOK_LLAVEIZQUIERDA",
  "TOK_LLAVEDERECHA", "TOK_ASIGNACION", "TOK_MAS", "TOK_MENOS",
  "TOK_DIVISION", "TOK_ASTERISCO", "TOK_AND", "TOK_OR", "TOK_NOT",
  "TOK_IGUAL", "TOK_DISTINTO", "TOK_MENORIGUAL", "TOK_MAYORIGUAL",
  "TOK_MENOR", "TOK_MAYOR", "TOK_TRUE", "TOK_FALSE", "TOK_ERROR",
  "$accept", "programa", "init", "escritura1", "escritura2",
  "declaraciones", "declaracion", "clase", "clase_escalar", "tipo",
  "clase_vector", "identificadores", "funciones", "funcion",
  "fn_declaracion", "fn_name", "parametros_funcion",
  "resto_parametros_funcion", "parametro_funcion", "idpf",
  "declaraciones_funcion", "sentencias", "sentencia", "sentencia_simple",
  "bloque", "asignacion", "elemento_vector", "condicional", "if_exp_else",
  "if_exp", "while", "while_exp", "bucle", "lectura", "escritura",
  "retorno_funcion", "exp", "en_explist_act", "lista_expresiones",
  "resto_lista_expresiones", "comparacion", "constante",
  "constante_logica", "constante_entera", "identificador", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -39

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define YYTABLE_NINF -68

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -39,     4,     0,   -39,    -8,     1,   -39,   -39,     6,   -39,
       1,    14,   -39,   -39,   -39,    11,    46,   -39,   -39,    10,
      40,    69,     6,   -39,    46,    20,    55,   -39,    14,   -39,
      54,    78,    20,   -39,   -18,    75,    77,    83,    68,    68,
      73,    20,    81,   -39,   -39,    74,   -39,    89,    82,    68,
      85,   -39,   -39,   -39,   -39,     6,   -39,   -39,   -39,    79,
      68,    68,    68,   -39,   -39,    -1,    68,    68,    68,   -39,
     -39,   -39,    96,   -39,   -39,   -39,    96,   -39,   -39,   -39,
      68,    93,    94,    96,    95,   114,   100,   111,   -39,    84,
      96,    96,   110,    17,   112,    64,   -39,    68,    68,    68,
      68,    68,    68,    96,    20,    20,    20,   -39,   -39,   107,
       6,   -39,   -39,    68,   -39,    68,    68,    68,    68,    68,
      68,   -39,    64,    64,   -39,   -39,    12,    12,   109,   113,
     115,     1,   111,    39,   116,    96,    96,    96,    96,    96,
      96,   -39,   119,   -39,   -39,   -39,   -39,    68,   -39,   -39,
      39,   -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    12,    13,     0,     4,
       6,     0,     9,    11,    10,     0,    18,     7,    83,     0,
      15,     0,     0,     5,    18,     0,     0,     8,     0,    82,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,    30,     0,    33,    34,     0,    38,     0,     0,     0,
       0,    39,    35,    36,    37,    23,    16,    14,    21,     0,
       0,     0,     0,    47,    50,    61,     0,     0,     0,    80,
      81,    65,    51,    62,    78,    79,    52,    19,    31,    32,
       0,     0,     0,    48,     0,     0,     0,    25,     2,     0,
      40,    46,     0,     0,     0,    57,    60,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,    27,    26,     0,
       0,    22,    42,    69,    63,     0,     0,     0,     0,     0,
       0,    64,    53,    54,    55,    56,    58,    59,     0,     0,
       0,    29,    25,    71,     0,    72,    73,    74,    75,    76,
      77,    44,    43,    49,    28,    20,    24,     0,    68,    66,
      71,    70
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   -39,   -39,   -39,   -10,   -39,   -39,   -39,    -6,
     -39,   106,   117,   -39,   -39,   -39,   -39,     3,    28,   -39,
     -39,   -15,   -39,   -39,   -39,   -39,   -20,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -38,   -39,   -39,    -7,
     -39,   -39,   -39,   121,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    32,     9,    10,    11,    12,    13,
      14,    19,    23,    24,    25,    26,    86,   111,    87,   108,
     145,    40,    41,    42,    43,    44,    71,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    72,    92,   134,   148,
      94,    73,    74,    75,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    76,    15,    60,     3,    45,     4,    61,     6,     7,
       8,    83,    45,     6,     7,     5,    31,    59,   -67,    18,
      60,    45,    89,    90,    91,    34,    78,    27,    93,    95,
      96,    35,    21,    36,    37,    38,    39,   114,    97,    98,
      99,   100,   103,    97,    98,    99,   100,   101,   102,    85,
     115,   116,   117,   118,   119,   120,    22,   147,    28,   122,
     123,   124,   125,   126,   127,    97,    98,    99,   100,   101,
     102,    29,    29,    65,    55,   133,    57,   135,   136,   137,
     138,   139,   140,    58,    45,    45,    45,    66,    64,   128,
     129,   130,    99,   100,    62,    67,    63,    77,    79,    80,
      68,    81,    82,    88,    85,    84,   112,    69,    70,   150,
      97,    98,    99,   100,   101,   102,   104,   105,   106,   107,
     109,   144,    97,    98,    99,   100,   101,   102,   110,   113,
     131,   -45,   121,   141,    56,   146,   149,   142,   132,   143,
       0,    33,    30,   151
};

static const yytype_int16 yycheck[] =
{
      10,    39,     8,    21,     0,    25,     6,    25,     7,     8,
       9,    49,    32,     7,     8,    23,    22,    32,    19,     5,
      21,    41,    60,    61,    62,     5,    41,    17,    66,    67,
      68,    11,    21,    13,    14,    15,    16,    20,    26,    27,
      28,    29,    80,    26,    27,    28,    29,    30,    31,    55,
      33,    34,    35,    36,    37,    38,    10,    18,    18,    97,
      98,    99,   100,   101,   102,    26,    27,    28,    29,    30,
      31,     3,     3,     5,    19,   113,    22,   115,   116,   117,
     118,   119,   120,     5,   104,   105,   106,    19,     5,   104,
     105,   106,    28,    29,    19,    27,    19,    24,    17,    25,
      32,    12,    20,    24,   110,    20,    22,    39,    40,   147,
      26,    27,    28,    29,    30,    31,    23,    23,    23,     5,
      20,   131,    26,    27,    28,    29,    30,    31,    17,    19,
      23,    12,    20,    24,    28,   132,    20,    24,   110,    24,
      -1,    24,    21,   150
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     6,    23,     7,     8,     9,    47,
      48,    49,    50,    51,    52,    51,    45,    47,     5,    53,
      86,    21,    10,    54,    55,    56,    57,    17,    18,     3,
      85,    51,    46,    54,     5,    11,    13,    14,    15,    16,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    19,    53,    22,     5,    63,
      21,    25,    19,    19,     5,     5,    19,    27,    32,    39,
      40,    68,    78,    83,    84,    85,    78,    24,    63,    17,
      25,    12,    20,    78,    20,    51,    58,    60,    24,    78,
      78,    78,    79,    78,    82,    78,    78,    26,    27,    28,
      29,    30,    31,    78,    23,    23,    23,     5,    61,    20,
      17,    59,    22,    19,    20,    33,    34,    35,    36,    37,
      38,    20,    78,    78,    78,    78,    78,    78,    63,    63,
      63,    23,    60,    78,    80,    78,    78,    78,    78,    78,
      78,    24,    24,    24,    47,    62,    59,    18,    81,    20,
      78,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    46,    47,    47,    48,    49,
      49,    50,    51,    51,    52,    53,    53,    54,    54,    55,
      56,    57,    58,    58,    59,    59,    60,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    69,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     0,     0,     0,     1,     2,     3,     1,
       1,     1,     1,     1,     5,     1,     3,     2,     0,     3,
       6,     3,     2,     0,     3,     0,     2,     1,     1,     0,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     5,     5,     5,     3,     2,     2,     5,
       2,     2,     2,     3,     3,     3,     3,     2,     3,     3,
       2,     1,     1,     3,     3,     1,     5,     0,     2,     0,
       3,     0,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 132 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");
    escribir_fin(yyout);
    finish();
}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 138 "alfa.y" /* yacc.c:1646  */
    {
    /* Declaramos la tabla de simbolos local para la función main y que las
        declaraciones siguientes se añadan a la tabla local */
    GlobalTable = creat_hash_table();
    CurrentTable = GlobalTable;
    num_no = 0;
    escribir_subseccion_data(yyout);
    escribir_cabecera_bss(yyout);
}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 148 "alfa.y" /* yacc.c:1646  */
    {
    /* Llamada a funciones para escribir la sección data con los mensajes
    generales, y la
    tabla de símbolos así como todo lo necesario para que lo siguiente que
    haya que escribirse
    sea main: */
    
    escribir_segmento_codigo(yyout); 
}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 159 "alfa.y" /* yacc.c:1646  */
    {
    /* Aquí ya se podría llamar a la función que escribe inicio main */
    escribir_inicio_main(yyout);
}
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 165 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");
    }
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 169 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");
    
    }
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 175 "alfa.y" /* yacc.c:1646  */
    {
    /* Añadir el identificador a la tabla de símbolos */
    fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");
}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 181 "alfa.y" /* yacc.c:1646  */
    {
        clase_actual = ESCALAR;
        fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");
    }
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 186 "alfa.y" /* yacc.c:1646  */
    {
        clase_actual = VECTOR;
        fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");
    }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 192 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n");
}
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "alfa.y" /* yacc.c:1646  */
    {
        tipo_actual = INT;
        fprintf(yyout, ";R10:\t<tipo> ::= int\n");
    }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 202 "alfa.y" /* yacc.c:1646  */
    {
        tipo_actual = BOOLEAN;
        fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");
    }
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 208 "alfa.y" /* yacc.c:1646  */
    {
    vector_size_act = (yyvsp[-1].atributos).valor_entero;
    if((vector_size_act < 1) || (vector_size_act > MAX_VECTOR_SIZE)){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Vector fuera de rango. Rango (1, 64)\n", l, pos);
        finish();
        return -1;
    }
    fprintf(yyout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
}
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 219 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");
    }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 223 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");
    }
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 228 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n");
    }
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R21:\t<funciones> ::= \n");
    }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 237 "alfa.y" /* yacc.c:1646  */
    {
    hash_table_delete(LocalTable); 
    LocalTable = NULL;

    aux = isGlobal((yyvsp[-2].atributos).lexema);

    if(aux==NULL){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, variable not in global table\n", l, pos);
        finish();
        return -1;
    }
    
    if(fn_return == 0){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, function without return statement\n", l, pos);
        finish();
        return -1;
    }
    
    if(return_type != aux->tipo){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, incorrect return type\n", l, pos);
        finish();
        return -1;
    }
    
    fprintf(yyout, ";R22:<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 265 "alfa.y" /* yacc.c:1646  */
    {
        
    aux = isLocal((yyvsp[-5].atributos).lexema);
    aux->param = param_act_num;
    aux->localVar = loc_var_num;

    aux = isGlobal((yyvsp[-5].atributos).lexema);
    aux->param = param_act_num;
    aux->localVar = loc_var_num;

    strcpy((yyval.atributos).lexema, (yyvsp[-5].atributos).lexema);

    declararFuncion(yyout, (yyvsp[-5].atributos).lexema, loc_var_num);
}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 281 "alfa.y" /* yacc.c:1646  */
    {
    aux = get_value_from_hstable(GlobalTable, (yyvsp[0].atributos).lexema, sizeof((yyvsp[0].atributos).lexema));
    

    if(aux == NULL){
        aux = simboloinit((yyvsp[0].atributos).lexema, FUNCION, ESCALAR, tipo_actual, sizeof((yyvsp[0].atributos).lexema), 0, 0, 0, 0);
        if(aux == NULL) {
            finish();
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error when initializing the symbol\n", l, pos);
            return -1;
        }
        if(functionDeclaration((yyvsp[0].atributos).lexema, aux)==0) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error when declarating the function\n", l, pos);
            finish();
            return-1;
        }
        pos_local_var_act=1;
        loc_var_num=0;
        param_act_num = 0;
        pos_param_act = 0;
        vector_size_act = 0;
        (yyval.atributos).tipo = tipo_actual;
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
        fn_return=0;
        
    }else{
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, duplicated declaration\n", l, pos);
        finish();
        return -1;
    }
}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 315 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");
    }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 319 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R24:\t<parametros_funcion> ::=\n");
    }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 324 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");
    }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 328 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::=\n");
    }
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 333 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");
}
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 338 "alfa.y" /* yacc.c:1646  */
    {
    Simbol *s = NULL;

    if(!LocalTable){
        finish();
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, the local table doesnt exist\n", l, pos);
        return -1;
    }
    s = isLocal((yyvsp[0].atributos).lexema);
    if (s){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, duplicated variable\n", l, pos);
        finish();
        return -1;
    }else{
        s = simboloinit((yyvsp[0].atributos).lexema, PARAMETRO, ESCALAR, tipo_actual, sizeof((yyvsp[0].atributos).lexema), 0, 0, 0, pos_param_act);
        if(s == NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, symbol not created properly\n", l, pos);
            finish();
            return -1;
        }
        if(add_node2HashTable(LocalTable, (yyvsp[0].atributos).lexema, sizeof((yyvsp[0].atributos).lexema), s)==0){
            pos_param_act++;
            param_act_num++;
        }else{
            fprintf(stderr, "****Error Semantico en la linea %d: Repeated node.\n",l);
            finish();
            return -1;
        }
    }
    
}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 371 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");
    }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 375 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R29:\t<declaraciones_funcion> ::= \n");
    }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 380 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n");
    }
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 384 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");
    }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 389 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");
    }
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 393 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n");
    }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 398 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");
    }
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 402 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n");
    }
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 406 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n");
    }
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 410 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");
    }
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 415 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n");
    }
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 419 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n");
    }
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 424 "alfa.y" /* yacc.c:1646  */
    {
        Simbol *s = NULL;
        s = searchSimbolInTables(LocalTable, GlobalTable, (yyvsp[-2].atributos).lexema);
        if(s==NULL) {
            fprintf(stderr, "****Error Semantico en la linea %d: Acceso a variable no declarada (%s).\n",l,(yyvsp[-2].atributos).lexema);
            finish();
            return -1;
        }
        if (s->categoria==FUNCION || s->clase==VECTOR || s->tipo!=(yyvsp[0].atributos).tipo) {
            fprintf(stderr, "****Error Semantico en la linea %d: Asignacion incompatible.\n",l);
            finish();
            return -1;
        }
        
        if (LocalTable==NULL){
            asignar(yyout, (yyvsp[-2].atributos).lexema, (yyvsp[0].atributos).es_direccion);
        }
        else {
            if (s->categoria==PARAMETRO){
                    escribirParametro(yyout, s->paramPos, param_act_num);
            }
            else{
                    escribirVariableLocal(yyout, s->localVarPos);
            }
            invertirEnPila(yyout);
            asignarDestinoEnPila(yyout, (yyvsp[0].atributos).es_direccion);
        }
        fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
    }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 454 "alfa.y" /* yacc.c:1646  */
    {
        Simbol * aux;

        fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
        
        aux = searchSimbolInTables(LocalTable,GlobalTable,(yyvsp[-2].atributos).lexema);

        if(aux == NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, undeclared variable\n", l, pos);
            finish();
            return -1;
        }
        if(aux->tipo != (yyvsp[0].atributos).tipo){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Tipos incompatibles\n", l, pos);
            finish();
            return -1;
        }
        /*escribir_elemento_vector(yyout, $1.lexema, vector_size, $3.es_direccion);*/
        asignarDestinoEnPila(yyout, (yyvsp[0].atributos).es_direccion);
    }
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 476 "alfa.y" /* yacc.c:1646  */
    {
    Simbol *aux;

    aux = get_value_from_hstable(GlobalTable, (yyvsp[-3].atributos).lexema, sizeof((yyvsp[-3].atributos).lexema));
    if(aux==NULL) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable not declared %s\n", l, pos, (yyvsp[-3].atributos).lexema);
        finish();
        return -1;
    }

    if(aux->clase != VECTOR){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, The variable is not of type vector, you cannot index it\n", l, pos);
        finish();
        return -1;
    }

    if((yyvsp[-1].atributos).tipo != INT){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, The variable is not of type vector, you cannot index it\n", l, pos);
        finish();
        return -1;
    }

    if(en_explist == 0){
        escribir_elemento_vector(yyout, (yyvsp[-3].atributos).lexema, aux->tamanio, (yyvsp[-1].atributos).es_direccion);
    }else{
        escribir_elemento_vector(yyout, (yyvsp[-3].atributos).lexema, aux->tamanio, (yyvsp[-1].atributos).es_direccion);
        operandoEnPilaAArgumento(yyout,1);
    }

    (yyval.atributos).tipo = aux->tipo;
    (yyval.atributos).es_direccion = 1;
    strcpy((yyval.atributos).lexema, (yyvsp[-3].atributos).lexema);
    vector_size = aux->tamanio;

    fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 514 "alfa.y" /* yacc.c:1646  */
    {
        ifthen_fin(yyout, (yyvsp[-4].atributos).etiqueta);
        fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
    }
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 519 "alfa.y" /* yacc.c:1646  */
    {
        ifthenelse_fin(yyout, (yyvsp[-4].atributos).etiqueta);
        fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
    }
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 524 "alfa.y" /* yacc.c:1646  */
    {
    (yyval.atributos).etiqueta=(yyvsp[-4].atributos).etiqueta;
    ifthenelse_fin_then(yyout, (yyval.atributos).etiqueta);
}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 529 "alfa.y" /* yacc.c:1646  */
    {
    if((yyvsp[0].atributos).tipo != BOOLEAN){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, the type is not boolean\n", l, pos);
        finish();
        return -1;
    }

    (yyval.atributos).etiqueta = num_cond++;
    ifthen_inicio(yyout, (yyvsp[0].atributos).es_direccion, (yyval.atributos).etiqueta);
}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 541 "alfa.y" /* yacc.c:1646  */
    {
    num_loop++;
    while_inicio(yyout, num_loop);
}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 546 "alfa.y" /* yacc.c:1646  */
    {
    if ((yyvsp[0].atributos).tipo!=BOOLEAN) {
        fprintf(stderr, "****Error sintactico numeros 2 en [lin %d, col %d]\n", l, pos);       
    }
    while_exp_pila(yyout, (yyvsp[0].atributos).es_direccion, num_loop);
}
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 553 "alfa.y" /* yacc.c:1646  */
    {
    while_fin(yyout, num_loop);
    fprintf(yyout,";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 559 "alfa.y" /* yacc.c:1646  */
    {
    Simbol *s = NULL;
    s = searchSimbolInTables(LocalTable, GlobalTable, (yyvsp[0].atributos).lexema);
    if(s==NULL) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable not declared %s\n", l, pos, (yyvsp[0].atributos).lexema);
        finish();
        return -1;
    }
    if (s->categoria==FUNCION || s->categoria==VECTOR) {
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Incorrect category\n", l, pos);
        finish();
        return -1;
    }
    
    if (LocalTable!=NULL) {
        if (s->categoria==PARAMETRO){
            escribirParametro(yyout, s->paramPos, param_act_num);
        }
        else{
            escribirVariableLocal(yyout, s->localVarPos);
        }
    }
    leer(yyout, (yyvsp[0].atributos).lexema, s->tipo);
    fprintf(yyout,";R54:\t<lectura> ::= scanf <identificador>\n");
}
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 586 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout,";R56:\t<escritura> ::= printf <exp>\n");
    escribir(yyout, (yyvsp[0].atributos).es_direccion, (yyvsp[0].atributos).tipo);
    
}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 593 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout,";R61:\t<retorno_funcion> ::= return <exp>\n");
    if(LocalTable == NULL){
        fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Trying to return out of a function\n", l, pos);
        finish();
        return -1;
    }
    retornarFuncion(yyout,(yyvsp[0].atributos).es_direccion);
    return_type = (yyvsp[0].atributos).tipo;
    fn_return++;

}
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 607 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        sumar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n");
    }
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 619 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        restar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
    }
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 631 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        dividir(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
    }
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 643 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = INT;
        (yyval.atributos).es_direccion = 0;
        multiplicar(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n");
    }
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 655 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].atributos).tipo != INT) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo=INT;
        (yyval.atributos).es_direccion=0;
        cambiar_signo(yyout, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
    }
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 667 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != BOOLEAN || (yyvsp[0].atributos).tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        
        (yyval.atributos).tipo=BOOLEAN;
        (yyval.atributos).es_direccion=0;
        y(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
    }
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 680 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != BOOLEAN || (yyvsp[0].atributos).tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        
        (yyval.atributos).tipo=BOOLEAN;
        (yyval.atributos).es_direccion=0;
        o(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion);
        fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
    }
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 693 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[0].atributos).tipo != BOOLEAN) {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Non compatible types\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo=BOOLEAN;
        (yyval.atributos).es_direccion=0;
        no(yyout, (yyvsp[0].atributos).es_direccion, num_no);
        num_no++;
        fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n");
    }
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 706 "alfa.y" /* yacc.c:1646  */
    {
        Simbol *aux = NULL; 
        strcpy((yyval.atributos).lexema, (yyvsp[0].atributos).lexema);
        
        aux = searchSimbolInTables(LocalTable, GlobalTable, (yyvsp[0].atributos).lexema);
        if (aux == NULL)
        {
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Variable %s not in the table.\n", l, pos,  (yyvsp[0].atributos).lexema);
            finish();
            return -1;
        }
        if (aux->categoria==FUNCION || aux->clase==VECTOR)
        {
            fprintf(stderr,"****Error Semantico en la linea %d: Variable %s de clase incorrecta.\n", l, (yyvsp[0].atributos).lexema);
            finish();
            return -1;
        }

        (yyval.atributos).tipo = aux->tipo;
        (yyval.atributos).es_direccion = 1; /* ES UNA VARIABLE */
        
        if(LocalTable != NULL){
            if(aux->categoria == VARIABLE){
                escribirVariableLocal(yyout, aux->localVarPos);
            } else if(aux->categoria == PARAMETRO){
                escribirParametro(yyout, aux->paramPos, param_act_num);
            }
        } else {
            escribir_operando(yyout, (yyvsp[0].atributos).lexema, (yyval.atributos).es_direccion);
            if(en_explist){
                operandoEnPilaAArgumento(yyout, (yyval.atributos).es_direccion);
            }
        }
        
        fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n");
        
    }
#line 2272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 744 "alfa.y" /* yacc.c:1646  */
    {
        char aux[100];
        snprintf(aux,sizeof(aux),"%d",(yyvsp[0].atributos).valor_entero);
        escribir_operando(yyout, aux, (yyvsp[0].atributos).es_direccion);
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");
    }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 754 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
        fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");
    }
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 760 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[-1].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[-1].atributos).es_direccion;
        fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");
    }
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 766 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector>\n");
    }
#line 2316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 772 "alfa.y" /* yacc.c:1646  */
    {
        Simbol* s = NULL;

        if((s = isLocal((yyvsp[-4].atributos).lexema))==NULL){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Acceso a funcion no declarada (%s).\n", l, pos, (yyvsp[-4].atributos).lexema);
            finish();
            return -1;
        }

        if(s->categoria != FUNCION){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Acceso a funcion no declarada (%s).\n", l, pos, (yyvsp[-4].atributos).lexema);
            return -1;
        }

        if (s->param != num_parametros_llamada_actual){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Acceso a funcion no declarada (%s).\n", l, pos, (yyvsp[-4].atributos).lexema);
            return -1;
        }

        llamarFuncion(yyout, s->lexema, s->param);
        en_explist=0;
        (yyval.atributos).tipo = s->tipo;
        (yyval.atributos).es_direccion = 0;
        fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
    }
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 798 "alfa.y" /* yacc.c:1646  */
    {
    en_explist = 1;
}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 803 "alfa.y" /* yacc.c:1646  */
    {
        num_parametros_llamada_actual++;
        fprintf(yyout, ";R89:\t<lista_expresiones ::= <exp> <resto_lista_expresiones>\n");
    }
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 808 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R90:\t<lista_expresiones> ::=\n");
        num_parametros_llamada_actual = 0;
    }
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 814 "alfa.y" /* yacc.c:1646  */
    {
        num_parametros_llamada_actual++;
        fprintf(yyout, ";R91:\t<resto_lista_expresiones ::= , <exp> <resto_lista_expresiones>\n");
    }
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 819 "alfa.y" /* yacc.c:1646  */
    {
        fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=\n");
        num_parametros_llamada_actual = 0;
    }
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 825 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        igual(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R93:\t<comparacion> ::= <exp> == <exp>\n");
    }
#line 2407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 838 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        distinto(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R94:\t<comparacion> ::= <exp> != <exp>\n");
    }
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 851 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        menor_igual(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R95:\t<comparacion> ::= <exp> <= <exp>\n");
    }
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 864 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        mayor_igual(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R96:\t<comparacion> ::= <exp> >= <exp>\n");
    }
#line 2458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 877 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        menor(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R97:\t<comparacion> ::= <exp> < <exp>\n");
    }
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 890 "alfa.y" /* yacc.c:1646  */
    {
        if((yyvsp[-2].atributos).tipo != INT || (yyvsp[0].atributos).tipo != INT){
            fprintf(stderr, "****Error Semántico en [lin %d, col %d]: Error, Comparacion con operandos boolean.\n", l, pos);
            finish();
            return -1;
        }
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;

        mayor(yyout, (yyvsp[-2].atributos).es_direccion, (yyvsp[0].atributos).es_direccion, num_comp++);
        fprintf(yyout,";R98:\t<comparacion> ::= <exp> > <exp>\n");
    }
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 904 "alfa.y" /* yacc.c:1646  */
    {
    fprintf(yyout,";R99:\t<constante> ::= <constante_logica>\n");
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;
        
    }
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 912 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = (yyvsp[0].atributos).tipo;
        (yyval.atributos).es_direccion = (yyvsp[0].atributos).es_direccion;
        (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;

        fprintf(yyout,";R100:\t<constante> ::= <constante_entera>\n");
        
    }
#line 2517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 922 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).valor_entero = 1;

        fprintf(yyout,";R102:\t<constante_logica> ::= true\n");
    }
#line 2529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 930 "alfa.y" /* yacc.c:1646  */
    {
        (yyval.atributos).tipo = BOOLEAN;
        (yyval.atributos).es_direccion = 0;
        (yyval.atributos).valor_entero = 0;

        fprintf(yyout,";R103:\t<constante_logica> ::= false\n");
    }
#line 2541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 939 "alfa.y" /* yacc.c:1646  */
    {
    char aux[15];
    
    (yyval.atributos).tipo = INT;
    (yyval.atributos).es_direccion = 0;
    (yyval.atributos).valor_entero = (yyvsp[0].atributos).valor_entero;

    /* escribe código con tu librería para meter en la pila la constante
    push dword $1.valor_entero
    */
    
    fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");
}
#line 2559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 953 "alfa.y" /* yacc.c:1646  */
    {
    Simbol *s=NULL;
    s = searchSimbolInTables(LocalTable, GlobalTable, (yyvsp[0].atributos).lexema);
    if (s==NULL) {
        if (clase_actual == ESCALAR) {
            if (LocalTable == NULL) {
                declarar_variable(yyout, (yyvsp[0].atributos).lexema, tipo_actual, 1);
            }
            s = simboloinit((yyvsp[0].atributos).lexema, VARIABLE, clase_actual, tipo_actual, 0, 0, pos_local_var_act, 0, 0);
        } else {
            if (LocalTable == NULL) {
                declarar_variable(yyout, (yyvsp[0].atributos).lexema, tipo_actual, vector_size_act);
            }
            s = simboloinit((yyvsp[0].atributos).lexema, VARIABLE, clase_actual, tipo_actual, vector_size_act, 0, 0, 0, 0);
        }
        /* Creo el simbol */
        if (LocalTable!=NULL){
            loc_var_num++;
            pos_local_var_act++;
        }
        add_node2HashTable(CurrentTable, (yyvsp[0].atributos).lexema, sizeof((yyvsp[0].atributos).lexema), s);
        fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
    } else {
        fprintf(stderr,"****Error semántico en [lin %d, col %d]: Declaracion duplicada.\n", l, pos);
        finish();
        return -1;
    }
}
#line 2592 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2596 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 983 "alfa.y" /* yacc.c:1906  */


void yyerror (const char* err){
    if(err != NULL){
        fprintf(stdout,"****Error sintactico en [lin %d, col %d]\n", l, pos);
    }
    finish();
}

