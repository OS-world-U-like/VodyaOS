/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "build/gen/eqn/pre.y"
#
#include "e.h"
#
int	fromflg;

#line 77 "build/gen/eqn/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "e.def"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONTIG = 3,                     /* CONTIG  */
  YYSYMBOL_QTEXT = 4,                      /* QTEXT  */
  YYSYMBOL_SPACE = 5,                      /* SPACE  */
  YYSYMBOL_THIN = 6,                       /* THIN  */
  YYSYMBOL_TAB = 7,                        /* TAB  */
  YYSYMBOL_MATRIX = 8,                     /* MATRIX  */
  YYSYMBOL_LCOL = 9,                       /* LCOL  */
  YYSYMBOL_CCOL = 10,                      /* CCOL  */
  YYSYMBOL_RCOL = 11,                      /* RCOL  */
  YYSYMBOL_COL = 12,                       /* COL  */
  YYSYMBOL_MARK = 13,                      /* MARK  */
  YYSYMBOL_LINEUP = 14,                    /* LINEUP  */
  YYSYMBOL_SUM = 15,                       /* SUM  */
  YYSYMBOL_INT = 16,                       /* INT  */
  YYSYMBOL_PROD = 17,                      /* PROD  */
  YYSYMBOL_UNION = 18,                     /* UNION  */
  YYSYMBOL_INTER = 19,                     /* INTER  */
  YYSYMBOL_LPILE = 20,                     /* LPILE  */
  YYSYMBOL_PILE = 21,                      /* PILE  */
  YYSYMBOL_CPILE = 22,                     /* CPILE  */
  YYSYMBOL_RPILE = 23,                     /* RPILE  */
  YYSYMBOL_ABOVE = 24,                     /* ABOVE  */
  YYSYMBOL_DEFINE = 25,                    /* DEFINE  */
  YYSYMBOL_TDEFINE = 26,                   /* TDEFINE  */
  YYSYMBOL_NDEFINE = 27,                   /* NDEFINE  */
  YYSYMBOL_DELIM = 28,                     /* DELIM  */
  YYSYMBOL_GSIZE = 29,                     /* GSIZE  */
  YYSYMBOL_GFONT = 30,                     /* GFONT  */
  YYSYMBOL_INCLUDE = 31,                   /* INCLUDE  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_TO = 33,                        /* TO  */
  YYSYMBOL_OVER = 34,                      /* OVER  */
  YYSYMBOL_SQRT = 35,                      /* SQRT  */
  YYSYMBOL_SUP = 36,                       /* SUP  */
  YYSYMBOL_SUB = 37,                       /* SUB  */
  YYSYMBOL_SIZE = 38,                      /* SIZE  */
  YYSYMBOL_FONT = 39,                      /* FONT  */
  YYSYMBOL_ROMAN = 40,                     /* ROMAN  */
  YYSYMBOL_ITALIC = 41,                    /* ITALIC  */
  YYSYMBOL_BOLD = 42,                      /* BOLD  */
  YYSYMBOL_FAT = 43,                       /* FAT  */
  YYSYMBOL_UP = 44,                        /* UP  */
  YYSYMBOL_DOWN = 45,                      /* DOWN  */
  YYSYMBOL_BACK = 46,                      /* BACK  */
  YYSYMBOL_FWD = 47,                       /* FWD  */
  YYSYMBOL_LEFT = 48,                      /* LEFT  */
  YYSYMBOL_RIGHT = 49,                     /* RIGHT  */
  YYSYMBOL_DOT = 50,                       /* DOT  */
  YYSYMBOL_DOTDOT = 51,                    /* DOTDOT  */
  YYSYMBOL_HAT = 52,                       /* HAT  */
  YYSYMBOL_TILDE = 53,                     /* TILDE  */
  YYSYMBOL_BAR = 54,                       /* BAR  */
  YYSYMBOL_UNDER = 55,                     /* UNDER  */
  YYSYMBOL_VEC = 56,                       /* VEC  */
  YYSYMBOL_DYAD = 57,                      /* DYAD  */
  YYSYMBOL_58_ = 58,                       /* '{'  */
  YYSYMBOL_59_ = 59,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_stuff = 61,                     /* stuff  */
  YYSYMBOL_eqn = 62,                       /* eqn  */
  YYSYMBOL_lineupbox = 63,                 /* lineupbox  */
  YYSYMBOL_matrix = 64,                    /* matrix  */
  YYSYMBOL_collist = 65,                   /* collist  */
  YYSYMBOL_column = 66,                    /* column  */
  YYSYMBOL_lcol = 67,                      /* lcol  */
  YYSYMBOL_ccol = 68,                      /* ccol  */
  YYSYMBOL_rcol = 69,                      /* rcol  */
  YYSYMBOL_col = 70,                       /* col  */
  YYSYMBOL_sbox = 71,                      /* sbox  */
  YYSYMBOL_tbox = 72,                      /* tbox  */
  YYSYMBOL_box = 73,                       /* box  */
  YYSYMBOL_int = 74,                       /* int  */
  YYSYMBOL_fwd = 75,                       /* fwd  */
  YYSYMBOL_up = 76,                        /* up  */
  YYSYMBOL_back = 77,                      /* back  */
  YYSYMBOL_down = 78,                      /* down  */
  YYSYMBOL_diacrit = 79,                   /* diacrit  */
  YYSYMBOL_from = 80,                      /* from  */
  YYSYMBOL_to = 81,                        /* to  */
  YYSYMBOL_left = 82,                      /* left  */
  YYSYMBOL_right = 83,                     /* right  */
  YYSYMBOL_list = 84,                      /* list  */
  YYSYMBOL_lpile = 85,                     /* lpile  */
  YYSYMBOL_cpile = 86,                     /* cpile  */
  YYSYMBOL_pile = 87,                      /* pile  */
  YYSYMBOL_rpile = 88,                     /* rpile  */
  YYSYMBOL_size = 89,                      /* size  */
  YYSYMBOL_font = 90,                      /* font  */
  YYSYMBOL_sub = 91,                       /* sub  */
  YYSYMBOL_sup = 92,                       /* sup  */
  YYSYMBOL_pbox = 93,                      /* pbox  */
  YYSYMBOL_text = 94                       /* text  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   404

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    22,    22,    23,    24,    27,    28,    29,    30,    33,
      36,    38,    39,    42,    43,    44,    45,    48,    49,    50,
      51,    53,    56,    57,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    89,    92,    93,    94,    95,    97,    98,    99,   100,
     101,   102,   103,   104,   107,   112,   117,   118,   121,   122,
     123,   126,   127,   130,   131,   132,   133,   135,   138,   139,
     140,   141,   144,   147,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   162,   163
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONTIG", "QTEXT",
  "SPACE", "THIN", "TAB", "MATRIX", "LCOL", "CCOL", "RCOL", "COL", "MARK",
  "LINEUP", "SUM", "INT", "PROD", "UNION", "INTER", "LPILE", "PILE",
  "CPILE", "RPILE", "ABOVE", "DEFINE", "TDEFINE", "NDEFINE", "DELIM",
  "GSIZE", "GFONT", "INCLUDE", "FROM", "TO", "OVER", "SQRT", "SUP", "SUB",
  "SIZE", "FONT", "ROMAN", "ITALIC", "BOLD", "FAT", "UP", "DOWN", "BACK",
  "FWD", "LEFT", "RIGHT", "DOT", "DOTDOT", "HAT", "TILDE", "BAR", "UNDER",
  "VEC", "DYAD", "'{'", "'}'", "$accept", "stuff", "eqn", "lineupbox",
  "matrix", "collist", "column", "lcol", "ccol", "rcol", "col", "sbox",
  "tbox", "box", "int", "fwd", "up", "back", "down", "diacrit", "from",
  "to", "left", "right", "list", "lpile", "cpile", "pile", "rpile", "size",
  "font", "sub", "sup", "pbox", "text", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     114,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   346,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   346,
      23,    23,   -81,   -81,   -81,   346,    23,    23,    23,    23,
       9,   254,    34,   300,   -18,    53,     5,   346,   346,   346,
     346,   254,   -14,   -12,    -7,    -3,   346,   346,   -81,    53,
     134,   -81,   -81,   -81,   -81,   181,   -81,   -81,   -81,   -81,
     -81,   -81,   160,   -81,   346,   -81,    53,    82,   -81,   -81,
     346,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   346,   346,   346,   346,   346,   346,   181,   181,
     181,   181,   207,   254,   254,   254,   254,   181,   181,   -81,
      53,   -81,   -81,   -81,   -81,    10,   -81,     3,     6,     7,
       8,   134,    53,    53,   134,   134,   134,   134,     1,   -81,
     300,    -6,    -1,     0,     4,   -81,   -81,   254,   254,   254,
     254,   -81,   346,   -81,   346,   -81,   -81,   -81,   254,   -81,
     -81,   -81,   -81,    11,    12,    13,    21,    53,   134,   300,
     -81,   -81,   -81,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,    86,    85,    87,    88,    89,    10,     0,     8,
      90,    51,    91,    92,    93,    73,    75,    74,    76,     0,
       0,     0,    78,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     0,     5,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    25,
      29,    94,    95,    77,    81,    28,    53,    55,    54,    52,
      67,    66,     0,     1,     0,     7,     6,     0,    64,    65,
       0,    83,    82,    61,    63,    56,    62,    59,    60,    57,
      58,    45,     0,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    70,     0,     0,     0,     0,    26,    27,    84,
       9,    17,    18,    19,    20,     0,    11,     0,     0,     0,
       0,    24,    23,    44,    35,    36,    38,    39,     0,    41,
      71,     0,     0,     0,     0,    50,    12,     0,     0,     0,
       0,    43,     0,    34,     0,    37,    69,    68,     0,    30,
      31,    33,    32,     0,     0,     0,     0,    22,    21,    72,
      13,    14,    15,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,     2,   -81,   -81,   -81,   -53,   -81,   -81,   -81,
     -81,   -59,   -81,    -8,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -44,   -81,   -81,   -80,   -81,   -81,   -81,   -81,   -81,
     -81,    37,   -33,   -81,   -20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    32,   120,    65,    34,   105,   106,   107,   108,   109,
     110,   133,   131,    35,    36,    37,    38,    39,    40,    81,
      82,    83,    41,   119,   121,    42,    43,    44,    45,    46,
      47,    84,    85,    48,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    54,    33,    87,    51,    52,    56,    57,    58,    59,
      61,    50,    51,    52,   122,   123,   124,    55,   138,   101,
     102,   103,   104,   138,   138,    66,    51,    52,   138,    88,
      89,    90,    91,    62,    63,   138,   138,   138,    97,    98,
      67,    71,    72,    92,    93,   138,    94,   143,   144,   145,
     146,    95,   126,   139,    66,    96,   100,   135,   140,   141,
     136,   127,   111,   142,   128,   129,   130,    60,   132,   125,
     150,   151,   152,    86,   112,   113,   114,   115,   116,   117,
     153,   134,     0,   134,    66,    68,    69,    70,     0,    71,
      72,   101,   102,   103,   104,     0,     0,     0,   137,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
      80,     0,    66,     0,    -4,     1,     0,     2,     3,     4,
       5,     6,     7,     0,   147,     0,   148,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
     149,    66,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     2,     3,     4,     5,     6,     7,     0,
      71,    72,    31,     8,    64,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,     0,    19,     0,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       2,     3,     4,     5,     6,     7,     0,     0,    31,    99,
       8,    64,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,    19,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,   118,     2,     3,     4,
       5,     6,     7,     0,     0,    31,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     2,     3,     4,     5,     6,     7,     0,
       0,     0,    31,     8,    64,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     2,
       3,     4,     5,     6,     7,     0,     0,     0,    31,     8,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31
};

static const yytype_int16 yycheck[] =
{
       8,    21,     0,    36,     3,     4,    26,    27,    28,    29,
      30,    19,     3,     4,    94,    95,    96,    25,    24,     9,
      10,    11,    12,    24,    24,    33,     3,     4,    24,    37,
      38,    39,    40,    31,     0,    24,    24,    24,    46,    47,
      58,    36,    37,    41,    58,    24,    58,   127,   128,   129,
     130,    58,   105,    59,    62,    58,    64,   116,    59,    59,
      59,    58,    70,    59,    58,    58,    58,    58,   112,    59,
      59,    59,    59,    36,    82,    83,    84,    85,    86,    87,
      59,   114,    -1,   116,    92,    32,    33,    34,    -1,    36,
      37,     9,    10,    11,    12,    -1,    -1,    -1,   118,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,   120,    -1,     0,     1,    -1,     3,     4,     5,
       6,     7,     8,    -1,   132,    -1,   134,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
     138,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     3,     4,     5,     6,     7,     8,    -1,
      36,    37,    58,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    35,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    58,    59,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    35,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,     3,     4,     5,
       6,     7,     8,    -1,    -1,    58,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    58,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    58,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    35,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    58,    61,    62,    64,    73,    74,    75,    76,    77,
      78,    82,    85,    86,    87,    88,    89,    90,    93,    73,
      73,     3,     4,    94,    94,    73,    94,    94,    94,    94,
      58,    94,    62,     0,    14,    63,    73,    58,    32,    33,
      34,    36,    37,    50,    51,    52,    53,    54,    55,    56,
      57,    79,    80,    81,    91,    92,    91,    92,    73,    73,
      73,    73,    62,    58,    58,    58,    58,    73,    73,    59,
      73,     9,    10,    11,    12,    65,    66,    67,    68,    69,
      70,    73,    73,    73,    73,    73,    73,    73,    49,    83,
      62,    84,    84,    84,    84,    59,    66,    58,    58,    58,
      58,    72,    81,    71,    92,    71,    59,    94,    24,    59,
      59,    59,    59,    84,    84,    84,    84,    73,    73,    62,
      59,    59,    59,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    61,    61,    62,    62,    62,    62,    63,
      64,    65,    65,    66,    66,    66,    66,    67,    68,    69,
      70,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    74,    75,    76,    77,    78,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    81,    82,    82,    83,    83,
      83,    84,    84,    85,    86,    87,    88,    89,    90,    90,
      90,    90,    91,    92,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     2,     2,     1,     2,
       1,     1,     2,     4,     4,     4,     4,     1,     1,     1,
       1,     2,     2,     0,     3,     2,     2,     2,     2,     2,
       4,     4,     4,     4,     4,     3,     3,     4,     3,     3,
       1,     3,     1,     4,     3,     2,     2,     2,     2,     2,
       4,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       0,     1,     3,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* stuff: eqn  */
#line 22 "build/gen/eqn/pre.y"
                { putout(yyvsp[0]); }
#line 1318 "build/gen/eqn/y.tab.c"
    break;

  case 3: /* stuff: error  */
#line 23 "build/gen/eqn/pre.y"
                { error(!FATAL, "syntax error"); }
#line 1324 "build/gen/eqn/y.tab.c"
    break;

  case 4: /* stuff: %empty  */
#line 24 "build/gen/eqn/pre.y"
                { eqnreg = 0; }
#line 1330 "build/gen/eqn/y.tab.c"
    break;

  case 6: /* eqn: eqn box  */
#line 28 "build/gen/eqn/pre.y"
                        { eqnbox(yyvsp[-1], yyvsp[0], 0); }
#line 1336 "build/gen/eqn/y.tab.c"
    break;

  case 7: /* eqn: eqn lineupbox  */
#line 29 "build/gen/eqn/pre.y"
                        { eqnbox(yyvsp[-1], yyvsp[0], 1); }
#line 1342 "build/gen/eqn/y.tab.c"
    break;

  case 8: /* eqn: LINEUP  */
#line 30 "build/gen/eqn/pre.y"
                        { lineup(0); }
#line 1348 "build/gen/eqn/y.tab.c"
    break;

  case 9: /* lineupbox: LINEUP box  */
#line 33 "build/gen/eqn/pre.y"
                        { yyval = yyvsp[0]; lineup(1); }
#line 1354 "build/gen/eqn/y.tab.c"
    break;

  case 10: /* matrix: MATRIX  */
#line 36 "build/gen/eqn/pre.y"
                        { yyval = ct; }
#line 1360 "build/gen/eqn/y.tab.c"
    break;

  case 13: /* column: lcol '{' list '}'  */
#line 42 "build/gen/eqn/pre.y"
                                { column('L', yyvsp[-3]); }
#line 1366 "build/gen/eqn/y.tab.c"
    break;

  case 14: /* column: ccol '{' list '}'  */
#line 43 "build/gen/eqn/pre.y"
                                { column('C', yyvsp[-3]); }
#line 1372 "build/gen/eqn/y.tab.c"
    break;

  case 15: /* column: rcol '{' list '}'  */
#line 44 "build/gen/eqn/pre.y"
                                { column('R', yyvsp[-3]); }
#line 1378 "build/gen/eqn/y.tab.c"
    break;

  case 16: /* column: col '{' list '}'  */
#line 45 "build/gen/eqn/pre.y"
                                { column('-', yyvsp[-3]); }
#line 1384 "build/gen/eqn/y.tab.c"
    break;

  case 17: /* lcol: LCOL  */
#line 48 "build/gen/eqn/pre.y"
                        { yyval = ct++; }
#line 1390 "build/gen/eqn/y.tab.c"
    break;

  case 18: /* ccol: CCOL  */
#line 49 "build/gen/eqn/pre.y"
                        { yyval = ct++; }
#line 1396 "build/gen/eqn/y.tab.c"
    break;

  case 19: /* rcol: RCOL  */
#line 50 "build/gen/eqn/pre.y"
                        { yyval = ct++; }
#line 1402 "build/gen/eqn/y.tab.c"
    break;

  case 20: /* col: COL  */
#line 51 "build/gen/eqn/pre.y"
                        { yyval = ct++; }
#line 1408 "build/gen/eqn/y.tab.c"
    break;

  case 21: /* sbox: sup box  */
#line 53 "build/gen/eqn/pre.y"
                                        { yyval = yyvsp[0]; }
#line 1414 "build/gen/eqn/y.tab.c"
    break;

  case 22: /* tbox: to box  */
#line 56 "build/gen/eqn/pre.y"
                                        { yyval = yyvsp[0]; }
#line 1420 "build/gen/eqn/y.tab.c"
    break;

  case 23: /* tbox: %empty  */
#line 57 "build/gen/eqn/pre.y"
                                        { yyval = 0; }
#line 1426 "build/gen/eqn/y.tab.c"
    break;

  case 24: /* box: box OVER box  */
#line 60 "build/gen/eqn/pre.y"
                        { boverb(yyvsp[-2], yyvsp[0]); }
#line 1432 "build/gen/eqn/y.tab.c"
    break;

  case 25: /* box: MARK box  */
#line 61 "build/gen/eqn/pre.y"
                        { mark(yyvsp[0]); }
#line 1438 "build/gen/eqn/y.tab.c"
    break;

  case 26: /* box: size box  */
#line 62 "build/gen/eqn/pre.y"
                                        { size(yyvsp[-1], yyvsp[0]); }
#line 1444 "build/gen/eqn/y.tab.c"
    break;

  case 27: /* box: font box  */
#line 63 "build/gen/eqn/pre.y"
                                        { font(yyvsp[-1], yyvsp[0]); }
#line 1450 "build/gen/eqn/y.tab.c"
    break;

  case 28: /* box: FAT box  */
#line 64 "build/gen/eqn/pre.y"
                        { fatbox(yyvsp[0]); }
#line 1456 "build/gen/eqn/y.tab.c"
    break;

  case 29: /* box: SQRT box  */
#line 65 "build/gen/eqn/pre.y"
                        { sqrt(yyvsp[0]); }
#line 1462 "build/gen/eqn/y.tab.c"
    break;

  case 30: /* box: lpile '{' list '}'  */
#line 66 "build/gen/eqn/pre.y"
                                { lpile('L', yyvsp[-3], ct); ct = yyvsp[-3]; }
#line 1468 "build/gen/eqn/y.tab.c"
    break;

  case 31: /* box: cpile '{' list '}'  */
#line 67 "build/gen/eqn/pre.y"
                                { lpile('C', yyvsp[-3], ct); ct = yyvsp[-3]; }
#line 1474 "build/gen/eqn/y.tab.c"
    break;

  case 32: /* box: rpile '{' list '}'  */
#line 68 "build/gen/eqn/pre.y"
                                { lpile('R', yyvsp[-3], ct); ct = yyvsp[-3]; }
#line 1480 "build/gen/eqn/y.tab.c"
    break;

  case 33: /* box: pile '{' list '}'  */
#line 69 "build/gen/eqn/pre.y"
                                { lpile('-', yyvsp[-3], ct); ct = yyvsp[-3]; }
#line 1486 "build/gen/eqn/y.tab.c"
    break;

  case 34: /* box: box sub box sbox  */
#line 70 "build/gen/eqn/pre.y"
                                                { shift2(yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1492 "build/gen/eqn/y.tab.c"
    break;

  case 35: /* box: box sub box  */
#line 71 "build/gen/eqn/pre.y"
                                                { bshiftb(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1498 "build/gen/eqn/y.tab.c"
    break;

  case 36: /* box: box sup box  */
#line 72 "build/gen/eqn/pre.y"
                                                { bshiftb(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1504 "build/gen/eqn/y.tab.c"
    break;

  case 37: /* box: int sub box sbox  */
#line 73 "build/gen/eqn/pre.y"
                                                { integral(yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1510 "build/gen/eqn/y.tab.c"
    break;

  case 38: /* box: int sub box  */
#line 74 "build/gen/eqn/pre.y"
                                                { integral(yyvsp[-2], yyvsp[0], 0); }
#line 1516 "build/gen/eqn/y.tab.c"
    break;

  case 39: /* box: int sup box  */
#line 75 "build/gen/eqn/pre.y"
                                                { integral(yyvsp[-2], 0, yyvsp[0]); }
#line 1522 "build/gen/eqn/y.tab.c"
    break;

  case 40: /* box: int  */
#line 76 "build/gen/eqn/pre.y"
                                                { integral(yyvsp[0], 0, 0); }
#line 1528 "build/gen/eqn/y.tab.c"
    break;

  case 41: /* box: left eqn right  */
#line 77 "build/gen/eqn/pre.y"
                                { paren(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1534 "build/gen/eqn/y.tab.c"
    break;

  case 43: /* box: box from box tbox  */
#line 79 "build/gen/eqn/pre.y"
                                                { fromto(yyvsp[-3], yyvsp[-1], yyvsp[0]); fromflg=0; }
#line 1540 "build/gen/eqn/y.tab.c"
    break;

  case 44: /* box: box to box  */
#line 80 "build/gen/eqn/pre.y"
                                        { fromto(yyvsp[-2], 0, yyvsp[0]); }
#line 1546 "build/gen/eqn/y.tab.c"
    break;

  case 45: /* box: box diacrit  */
#line 81 "build/gen/eqn/pre.y"
                        { diacrit(yyvsp[-1], yyvsp[0]); }
#line 1552 "build/gen/eqn/y.tab.c"
    break;

  case 46: /* box: fwd box  */
#line 82 "build/gen/eqn/pre.y"
                                        { move(FWD, yyvsp[-1], yyvsp[0]); }
#line 1558 "build/gen/eqn/y.tab.c"
    break;

  case 47: /* box: up box  */
#line 83 "build/gen/eqn/pre.y"
                                        { move(UP, yyvsp[-1], yyvsp[0]); }
#line 1564 "build/gen/eqn/y.tab.c"
    break;

  case 48: /* box: back box  */
#line 84 "build/gen/eqn/pre.y"
                                        { move(BACK, yyvsp[-1], yyvsp[0]); }
#line 1570 "build/gen/eqn/y.tab.c"
    break;

  case 49: /* box: down box  */
#line 85 "build/gen/eqn/pre.y"
                                        { move(DOWN, yyvsp[-1], yyvsp[0]); }
#line 1576 "build/gen/eqn/y.tab.c"
    break;

  case 50: /* box: matrix '{' collist '}'  */
#line 86 "build/gen/eqn/pre.y"
                                        { matrix(yyvsp[-3]); }
#line 1582 "build/gen/eqn/y.tab.c"
    break;

  case 51: /* int: INT  */
#line 89 "build/gen/eqn/pre.y"
                { setintegral(); }
#line 1588 "build/gen/eqn/y.tab.c"
    break;

  case 52: /* fwd: FWD text  */
#line 92 "build/gen/eqn/pre.y"
                        { yyval = atoi((char *) yyvsp[-1]); }
#line 1594 "build/gen/eqn/y.tab.c"
    break;

  case 53: /* up: UP text  */
#line 93 "build/gen/eqn/pre.y"
                        { yyval = atoi((char *) yyvsp[-1]); }
#line 1600 "build/gen/eqn/y.tab.c"
    break;

  case 54: /* back: BACK text  */
#line 94 "build/gen/eqn/pre.y"
                        { yyval = atoi((char *) yyvsp[-1]); }
#line 1606 "build/gen/eqn/y.tab.c"
    break;

  case 55: /* down: DOWN text  */
#line 95 "build/gen/eqn/pre.y"
                        { yyval = atoi((char *) yyvsp[-1]); }
#line 1612 "build/gen/eqn/y.tab.c"
    break;

  case 56: /* diacrit: HAT  */
#line 97 "build/gen/eqn/pre.y"
                { yyval = HAT; }
#line 1618 "build/gen/eqn/y.tab.c"
    break;

  case 57: /* diacrit: VEC  */
#line 98 "build/gen/eqn/pre.y"
                { yyval = VEC; }
#line 1624 "build/gen/eqn/y.tab.c"
    break;

  case 58: /* diacrit: DYAD  */
#line 99 "build/gen/eqn/pre.y"
                { yyval = DYAD; }
#line 1630 "build/gen/eqn/y.tab.c"
    break;

  case 59: /* diacrit: BAR  */
#line 100 "build/gen/eqn/pre.y"
                { yyval = BAR; }
#line 1636 "build/gen/eqn/y.tab.c"
    break;

  case 60: /* diacrit: UNDER  */
#line 101 "build/gen/eqn/pre.y"
                { yyval = UNDER; }
#line 1642 "build/gen/eqn/y.tab.c"
    break;

  case 61: /* diacrit: DOT  */
#line 102 "build/gen/eqn/pre.y"
                { yyval = DOT; }
#line 1648 "build/gen/eqn/y.tab.c"
    break;

  case 62: /* diacrit: TILDE  */
#line 103 "build/gen/eqn/pre.y"
                { yyval = TILDE; }
#line 1654 "build/gen/eqn/y.tab.c"
    break;

  case 63: /* diacrit: DOTDOT  */
#line 104 "build/gen/eqn/pre.y"
                        { yyval = DOTDOT; }
#line 1660 "build/gen/eqn/y.tab.c"
    break;

  case 64: /* from: FROM  */
#line 107 "build/gen/eqn/pre.y"
                { yyval=ps; ps -= 3; fromflg = 1;
		if(dbg)printf(".\tfrom: old ps %d, new ps %d, fflg %d\n", yyval, ps, fromflg);
		}
#line 1668 "build/gen/eqn/y.tab.c"
    break;

  case 65: /* to: TO  */
#line 112 "build/gen/eqn/pre.y"
                { yyval=ps; if(fromflg==0)ps -= 3; 
			if(dbg)printf(".\tto: old ps %d, new ps %d\n", yyval, ps);
		}
#line 1676 "build/gen/eqn/y.tab.c"
    break;

  case 66: /* left: LEFT text  */
#line 117 "build/gen/eqn/pre.y"
                        { yyval = ((char *)yyvsp[0])[0]; }
#line 1682 "build/gen/eqn/y.tab.c"
    break;

  case 67: /* left: LEFT '{'  */
#line 118 "build/gen/eqn/pre.y"
                        { yyval = '{'; }
#line 1688 "build/gen/eqn/y.tab.c"
    break;

  case 68: /* right: RIGHT text  */
#line 121 "build/gen/eqn/pre.y"
                        { yyval = ((char *)yyvsp[0])[0]; }
#line 1694 "build/gen/eqn/y.tab.c"
    break;

  case 69: /* right: RIGHT '}'  */
#line 122 "build/gen/eqn/pre.y"
                        { yyval = '}'; }
#line 1700 "build/gen/eqn/y.tab.c"
    break;

  case 70: /* right: %empty  */
#line 123 "build/gen/eqn/pre.y"
                        { yyval = 0; }
#line 1706 "build/gen/eqn/y.tab.c"
    break;

  case 71: /* list: eqn  */
#line 126 "build/gen/eqn/pre.y"
                { lp[ct++] = yyvsp[0]; }
#line 1712 "build/gen/eqn/y.tab.c"
    break;

  case 72: /* list: list ABOVE eqn  */
#line 127 "build/gen/eqn/pre.y"
                                { lp[ct++] = yyvsp[0]; }
#line 1718 "build/gen/eqn/y.tab.c"
    break;

  case 73: /* lpile: LPILE  */
#line 130 "build/gen/eqn/pre.y"
                { yyval = ct; }
#line 1724 "build/gen/eqn/y.tab.c"
    break;

  case 74: /* cpile: CPILE  */
#line 131 "build/gen/eqn/pre.y"
                { yyval = ct; }
#line 1730 "build/gen/eqn/y.tab.c"
    break;

  case 75: /* pile: PILE  */
#line 132 "build/gen/eqn/pre.y"
                { yyval = ct; }
#line 1736 "build/gen/eqn/y.tab.c"
    break;

  case 76: /* rpile: RPILE  */
#line 133 "build/gen/eqn/pre.y"
                { yyval = ct; }
#line 1742 "build/gen/eqn/y.tab.c"
    break;

  case 77: /* size: SIZE text  */
#line 135 "build/gen/eqn/pre.y"
                        { yyval = ps; setsize((char *) yyvsp[0]); }
#line 1748 "build/gen/eqn/y.tab.c"
    break;

  case 78: /* font: ROMAN  */
#line 138 "build/gen/eqn/pre.y"
                        { setfont(ROM); }
#line 1754 "build/gen/eqn/y.tab.c"
    break;

  case 79: /* font: ITALIC  */
#line 139 "build/gen/eqn/pre.y"
                        { setfont(ITAL); }
#line 1760 "build/gen/eqn/y.tab.c"
    break;

  case 80: /* font: BOLD  */
#line 140 "build/gen/eqn/pre.y"
                        { setfont(BLD); }
#line 1766 "build/gen/eqn/y.tab.c"
    break;

  case 81: /* font: FONT text  */
#line 141 "build/gen/eqn/pre.y"
                        { setfont(((char *)yyvsp[0])[0]); }
#line 1772 "build/gen/eqn/y.tab.c"
    break;

  case 82: /* sub: SUB  */
#line 144 "build/gen/eqn/pre.y"
                { shift(SUB); }
#line 1778 "build/gen/eqn/y.tab.c"
    break;

  case 83: /* sup: SUP  */
#line 147 "build/gen/eqn/pre.y"
                { shift(SUP); }
#line 1784 "build/gen/eqn/y.tab.c"
    break;

  case 84: /* pbox: '{' eqn '}'  */
#line 150 "build/gen/eqn/pre.y"
                        { yyval = yyvsp[-1]; }
#line 1790 "build/gen/eqn/y.tab.c"
    break;

  case 85: /* pbox: QTEXT  */
#line 151 "build/gen/eqn/pre.y"
                        { text(QTEXT, (char *) yyvsp[0]); }
#line 1796 "build/gen/eqn/y.tab.c"
    break;

  case 86: /* pbox: CONTIG  */
#line 152 "build/gen/eqn/pre.y"
                        { text(CONTIG, (char *) yyvsp[0]); }
#line 1802 "build/gen/eqn/y.tab.c"
    break;

  case 87: /* pbox: SPACE  */
#line 153 "build/gen/eqn/pre.y"
                        { text(SPACE, 0); }
#line 1808 "build/gen/eqn/y.tab.c"
    break;

  case 88: /* pbox: THIN  */
#line 154 "build/gen/eqn/pre.y"
                        { text(THIN, 0); }
#line 1814 "build/gen/eqn/y.tab.c"
    break;

  case 89: /* pbox: TAB  */
#line 155 "build/gen/eqn/pre.y"
                        { text(TAB, 0); }
#line 1820 "build/gen/eqn/y.tab.c"
    break;

  case 90: /* pbox: SUM  */
#line 156 "build/gen/eqn/pre.y"
                        { funny(SUM); }
#line 1826 "build/gen/eqn/y.tab.c"
    break;

  case 91: /* pbox: PROD  */
#line 157 "build/gen/eqn/pre.y"
                        { funny(PROD); }
#line 1832 "build/gen/eqn/y.tab.c"
    break;

  case 92: /* pbox: UNION  */
#line 158 "build/gen/eqn/pre.y"
                        { funny(UNION); }
#line 1838 "build/gen/eqn/y.tab.c"
    break;

  case 93: /* pbox: INTER  */
#line 159 "build/gen/eqn/pre.y"
                        { funny(INTER); }
#line 1844 "build/gen/eqn/y.tab.c"
    break;


#line 1848 "build/gen/eqn/y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 166 "build/gen/eqn/pre.y"

