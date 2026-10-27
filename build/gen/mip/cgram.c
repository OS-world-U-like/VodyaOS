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
#line 107 "build/gen/mip/pre.y"

# include "mfile1"

	static int fake = 0;
	static char fakename[NCHNAM+1];

#line 78 "build/gen/mip/cgram.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  #define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NAME 2
#define STRING 3
#define ICON 4
#define FCON 5
#define PLUS 6
#define MINUS 8
#define MUL 11
#define AND 14
#define OR 17
#define ER 19
#define QUEST 21
#define COLON 22
#define ANDAND 23
#define OROR 24
#define ASOP 25
#define RELOP 26
#define EQUOP 27
#define DIVOP 28
#define SHIFTOP 29
#define INCOP 30
#define UNOP 31
#define STROP 32
#define TYPE 33
#define CLASS 34
#define STRUCT 35
#define RETURN 36
#define GOTO 37
#define IF 38
#define ELSE 39
#define SWITCH 40
#define BREAK 41
#define CONTINUE 42
#define WHILE 43
#define DO 44
#define FOR 45
#define DEFAULT 46
#define CASE 47
#define SIZEOF 48
#define ENUM 49
#define LP 50
#define RP 51
#define LC 52
#define RC 53
#define LB 54
#define RB 55
#define CM 56
#define SM 57
#define ASSIGN 58

  typedef int yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NAME 2
#define STRING 3
#define ICON 4
#define FCON 5
#define PLUS 6
#define MINUS 8
#define MUL 11
#define AND 14
#define OR 17
#define ER 19
#define QUEST 21
#define COLON 22
#define ANDAND 23
#define OROR 24
#define ASOP 25
#define RELOP 26
#define EQUOP 27
#define DIVOP 28
#define SHIFTOP 29
#define INCOP 30
#define UNOP 31
#define STROP 32
#define TYPE 33
#define CLASS 34
#define STRUCT 35
#define RETURN 36
#define GOTO 37
#define IF 38
#define ELSE 39
#define SWITCH 40
#define BREAK 41
#define CONTINUE 42
#define WHILE 43
#define DO 44
#define FOR 45
#define DEFAULT 46
#define CASE 47
#define SIZEOF 48
#define ENUM 49
#define LP 50
#define RP 51
#define LC 52
#define RC 53
#define LB 54
#define RB 55
#define CM 56
#define SM 57
#define ASSIGN 58

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NAME = 3,                       /* NAME  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_ICON = 5,                       /* ICON  */
  YYSYMBOL_FCON = 6,                       /* FCON  */
  YYSYMBOL_PLUS = 7,                       /* PLUS  */
  YYSYMBOL_MINUS = 8,                      /* MINUS  */
  YYSYMBOL_MUL = 9,                        /* MUL  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_ER = 12,                        /* ER  */
  YYSYMBOL_QUEST = 13,                     /* QUEST  */
  YYSYMBOL_COLON = 14,                     /* COLON  */
  YYSYMBOL_ANDAND = 15,                    /* ANDAND  */
  YYSYMBOL_OROR = 16,                      /* OROR  */
  YYSYMBOL_ASOP = 17,                      /* ASOP  */
  YYSYMBOL_RELOP = 18,                     /* RELOP  */
  YYSYMBOL_EQUOP = 19,                     /* EQUOP  */
  YYSYMBOL_DIVOP = 20,                     /* DIVOP  */
  YYSYMBOL_SHIFTOP = 21,                   /* SHIFTOP  */
  YYSYMBOL_INCOP = 22,                     /* INCOP  */
  YYSYMBOL_UNOP = 23,                      /* UNOP  */
  YYSYMBOL_STROP = 24,                     /* STROP  */
  YYSYMBOL_TYPE = 25,                      /* TYPE  */
  YYSYMBOL_CLASS = 26,                     /* CLASS  */
  YYSYMBOL_STRUCT = 27,                    /* STRUCT  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_GOTO = 29,                      /* GOTO  */
  YYSYMBOL_IF = 30,                        /* IF  */
  YYSYMBOL_ELSE = 31,                      /* ELSE  */
  YYSYMBOL_SWITCH = 32,                    /* SWITCH  */
  YYSYMBOL_BREAK = 33,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 34,                  /* CONTINUE  */
  YYSYMBOL_WHILE = 35,                     /* WHILE  */
  YYSYMBOL_DO = 36,                        /* DO  */
  YYSYMBOL_FOR = 37,                       /* FOR  */
  YYSYMBOL_DEFAULT = 38,                   /* DEFAULT  */
  YYSYMBOL_CASE = 39,                      /* CASE  */
  YYSYMBOL_SIZEOF = 40,                    /* SIZEOF  */
  YYSYMBOL_ENUM = 41,                      /* ENUM  */
  YYSYMBOL_LP = 42,                        /* LP  */
  YYSYMBOL_RP = 43,                        /* RP  */
  YYSYMBOL_LC = 44,                        /* LC  */
  YYSYMBOL_RC = 45,                        /* RC  */
  YYSYMBOL_LB = 46,                        /* LB  */
  YYSYMBOL_RB = 47,                        /* RB  */
  YYSYMBOL_CM = 48,                        /* CM  */
  YYSYMBOL_SM = 49,                        /* SM  */
  YYSYMBOL_ASSIGN = 50,                    /* ASSIGN  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_ext_def_list = 52,              /* ext_def_list  */
  YYSYMBOL_external_def = 53,              /* external_def  */
  YYSYMBOL_data_def = 54,                  /* data_def  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_function_body = 56,             /* function_body  */
  YYSYMBOL_arg_dcl_list = 57,              /* arg_dcl_list  */
  YYSYMBOL_stmt_list = 58,                 /* stmt_list  */
  YYSYMBOL_dcl_stat_list = 59,             /* dcl_stat_list  */
  YYSYMBOL_declaration = 60,               /* declaration  */
  YYSYMBOL_oattributes = 61,               /* oattributes  */
  YYSYMBOL_attributes = 62,                /* attributes  */
  YYSYMBOL_class = 63,                     /* class  */
  YYSYMBOL_type = 64,                      /* type  */
  YYSYMBOL_enum_dcl = 65,                  /* enum_dcl  */
  YYSYMBOL_enum_head = 66,                 /* enum_head  */
  YYSYMBOL_moe_list = 67,                  /* moe_list  */
  YYSYMBOL_moe = 68,                       /* moe  */
  YYSYMBOL_struct_dcl = 69,                /* struct_dcl  */
  YYSYMBOL_str_head = 70,                  /* str_head  */
  YYSYMBOL_type_dcl_list = 71,             /* type_dcl_list  */
  YYSYMBOL_type_declaration = 72,          /* type_declaration  */
  YYSYMBOL_declarator_list = 73,           /* declarator_list  */
  YYSYMBOL_74_2 = 74,                      /* @2  */
  YYSYMBOL_declarator = 75,                /* declarator  */
  YYSYMBOL_nfdeclarator = 76,              /* nfdeclarator  */
  YYSYMBOL_fdeclarator = 77,               /* fdeclarator  */
  YYSYMBOL_name_lp = 78,                   /* name_lp  */
  YYSYMBOL_name_list = 79,                 /* name_list  */
  YYSYMBOL_init_dcl_list = 80,             /* init_dcl_list  */
  YYSYMBOL_81_3 = 81,                      /* @3  */
  YYSYMBOL_xnfdeclarator = 82,             /* xnfdeclarator  */
  YYSYMBOL_init_declarator = 83,           /* init_declarator  */
  YYSYMBOL_init_list = 84,                 /* init_list  */
  YYSYMBOL_initializer = 85,               /* initializer  */
  YYSYMBOL_optcomma = 86,                  /* optcomma  */
  YYSYMBOL_optsemi = 87,                   /* optsemi  */
  YYSYMBOL_optasgn = 88,                   /* optasgn  */
  YYSYMBOL_ibrace = 89,                    /* ibrace  */
  YYSYMBOL_compoundstmt = 90,              /* compoundstmt  */
  YYSYMBOL_begin = 91,                     /* begin  */
  YYSYMBOL_statement = 92,                 /* statement  */
  YYSYMBOL_label = 93,                     /* label  */
  YYSYMBOL_doprefix = 94,                  /* doprefix  */
  YYSYMBOL_ifprefix = 95,                  /* ifprefix  */
  YYSYMBOL_ifelprefix = 96,                /* ifelprefix  */
  YYSYMBOL_whprefix = 97,                  /* whprefix  */
  YYSYMBOL_forprefix = 98,                 /* forprefix  */
  YYSYMBOL_switchpart = 99,                /* switchpart  */
  YYSYMBOL_con_e = 100,                    /* con_e  */
  YYSYMBOL_101_4 = 101,                    /* @4  */
  YYSYMBOL_102_e = 102,                    /* .e  */
  YYSYMBOL_elist = 103,                    /* elist  */
  YYSYMBOL_e = 104,                        /* e  */
  YYSYMBOL_term = 105,                     /* term  */
  YYSYMBOL_cast_type = 106,                /* cast_type  */
  YYSYMBOL_null_decl = 107,                /* null_decl  */
  YYSYMBOL_funct_idn = 108                 /* funct_idn  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1021

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  306

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   257


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
       0,     2,     3,     4,     5,     6,     7,     2,     8,     2,
       2,     9,     2,     2,    10,     2,     2,    11,     2,    12,
       2,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   133,   135,   137,   141,   143,   145,   145,
     156,   158,   159,   162,   164,   169,   171,   173,   175,   177,
     179,   182,   184,   186,   188,   189,   191,   196,   200,   201,
     205,   209,   210,   213,   215,   219,   221,   225,   226,   229,
     231,   235,   237,   241,   243,   247,   248,   251,   253,   267,
     269,   269,   272,   273,   274,   284,   290,   295,   298,   301,
     304,   308,   310,   313,   315,   317,   319,   321,   323,   329,
     336,   343,   345,   349,   351,   351,   354,   358,   361,   363,
     366,   370,   374,   376,   378,   381,   385,   386,   389,   390,
     394,   395,   398,   404,   414,   423,   425,   426,   430,   436,
     443,   451,   461,   469,   476,   482,   489,   503,   512,   513,
     514,   515,   517,   524,   528,   534,   543,   548,   556,   567,
     579,   589,   589,   593,   595,   597,   599,   603,   613,   617,
     619,   621,   623,   625,   627,   629,   631,   633,   635,   637,
     639,   643,   645,   647,   649,   651,   653,   655,   657,   660,
     662,   664,   666,   668,   672,   679,   681,   685,   690,   692,
     698,   700,   702,   704,   706,   713,   726,   732,   736,   738,
     742,   751,   752,   754,   756,   758,   760,   762,   766,   777
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
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "STRING",
  "ICON", "FCON", "PLUS", "MINUS", "MUL", "AND", "OR", "ER", "QUEST",
  "COLON", "ANDAND", "OROR", "ASOP", "RELOP", "EQUOP", "DIVOP", "SHIFTOP",
  "INCOP", "UNOP", "STROP", "TYPE", "CLASS", "STRUCT", "RETURN", "GOTO",
  "IF", "ELSE", "SWITCH", "BREAK", "CONTINUE", "WHILE", "DO", "FOR",
  "DEFAULT", "CASE", "SIZEOF", "ENUM", "LP", "RP", "LC", "RC", "LB", "RB",
  "CM", "SM", "ASSIGN", "$accept", "ext_def_list", "external_def",
  "data_def", "$@1", "function_body", "arg_dcl_list", "stmt_list",
  "dcl_stat_list", "declaration", "oattributes", "attributes", "class",
  "type", "enum_dcl", "enum_head", "moe_list", "moe", "struct_dcl",
  "str_head", "type_dcl_list", "type_declaration", "declarator_list", "@2",
  "declarator", "nfdeclarator", "fdeclarator", "name_lp", "name_list",
  "init_dcl_list", "@3", "xnfdeclarator", "init_declarator", "init_list",
  "initializer", "optcomma", "optsemi", "optasgn", "ibrace",
  "compoundstmt", "begin", "statement", "label", "doprefix", "ifprefix",
  "ifelprefix", "whprefix", "forprefix", "switchpart", "con_e", "@4", ".e",
  "elist", "e", "term", "cast_type", "null_decl", "funct_idn", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-194)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-80)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -194,   106,  -194,  -194,   -19,  -194,    30,    68,  -194,  -194,
      92,  -194,     0,    65,  -194,    61,  -194,    78,    99,    91,
     118,  -194,   122,     4,     4,  -194,   285,   337,    -1,   -34,
     120,  -194,  -194,  -194,   175,     0,  -194,  -194,    -6,    18,
      71,   379,   136,   140,   145,   142,  -194,  -194,  -194,    55,
    -194,  -194,  -194,   871,   143,   159,  -194,    25,   164,  -194,
    -194,  -194,  -194,  -194,   167,   971,  -194,  -194,   179,  -194,
     127,  -194,   233,    60,   196,  -194,  -194,  -194,   971,   971,
     971,   971,   971,   979,   931,   881,   852,   134,   923,  -194,
     175,   197,  -194,  -194,   193,  -194,    16,    18,     0,   198,
    -194,   852,  -194,   199,  -194,  -194,   135,  -194,  -194,  -194,
      18,  -194,  -194,   134,   134,   134,   134,   134,   931,   134,
       2,   513,   210,  -194,   209,  -194,   881,   852,   288,   297,
     340,   349,   392,   401,   971,   971,   971,   971,   971,   971,
     444,   453,   971,   971,  -194,   255,  -194,   971,  -194,    56,
     852,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,    94,   165,   222,     2,    -5,   220,  -194,   971,   881,
     232,   209,   971,    39,   971,    39,   971,  -194,   971,   201,
     971,   357,   971,   409,   557,   305,   252,   852,   471,   588,
     971,  -194,   971,   174,   852,   852,  -194,   572,  -194,   971,
     160,  -194,  -194,   195,   117,   467,   220,  -194,   114,   240,
     134,  -194,  -194,   244,   852,   852,   852,   852,   852,   852,
     971,   852,   852,  -194,   852,  -194,    23,    15,   496,   296,
     262,   266,   260,   269,   279,  -194,   280,   315,   971,  -194,
    -194,  -194,  -194,   246,   246,   246,   246,   246,   971,   246,
     616,  -194,   102,   290,  -194,   289,  -194,   539,  -194,  -194,
    -194,  -194,   631,   286,   971,   971,  -194,  -194,   971,   971,
    -194,   675,  -194,   306,   309,  -194,  -194,   299,   808,  -194,
    -194,  -194,   308,  -194,  -194,  -194,   690,   734,   749,   307,
    -194,   318,  -194,   246,  -194,  -194,  -194,  -194,   971,   971,
    -194,   312,   793,  -194,   319,  -194
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     5,    28,    27,    43,    35,     2,     4,
       0,    21,    25,    26,    32,     0,    31,     0,    29,    42,
      34,    77,    61,     0,     0,     6,    76,     8,     0,     0,
      90,    73,    23,    24,     0,     0,    30,    70,    57,    63,
       0,     0,     0,   121,     0,   121,    12,    71,    69,     0,
      74,     7,    91,     0,    39,    86,    37,     0,    88,    45,
      62,    67,    58,    59,     0,     0,    64,    65,     0,     9,
       0,    68,     0,     0,   165,   168,   166,   167,     0,     0,
       0,     0,     0,     0,     0,     0,    80,   151,     0,   121,
      87,     0,    56,   121,    47,    49,    53,    52,    89,     0,
      60,   122,    66,     0,    94,    11,     0,    10,    17,    72,
      79,    75,   178,   155,   153,   154,   157,   156,     0,   158,
     171,     0,     0,    92,    86,    82,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,   179,     0,   162,     0,
     125,    40,    38,    33,    55,    50,   121,    46,    41,    20,
      19,     0,    14,     0,   171,   171,   170,   169,     0,    87,
       0,    86,     0,   130,     0,   131,     0,   133,     0,   135,
       0,   136,     0,   137,     0,   138,   139,   149,   127,   134,
       0,   129,     0,   132,   128,   150,   164,     0,   163,     0,
       0,    54,    18,     0,     0,   160,   174,   172,     0,   121,
     159,    83,    81,     0,   142,   143,   140,   145,   146,   147,
       0,   141,   144,   161,   126,    51,     0,   165,     0,     0,
       0,     0,     0,     0,     0,   115,     0,     0,     0,    93,
     108,    96,    13,     0,     0,     0,     0,     0,   124,     0,
       0,    15,     0,   177,   175,     0,    85,   148,   110,   109,
     112,   105,     0,     0,     0,     0,   103,   104,     0,   124,
     114,     0,   111,     0,    97,    98,    99,     0,   123,   102,
      95,    16,     0,   176,   106,   107,     0,     0,     0,     0,
     113,     0,   117,     0,   173,   116,   120,   118,   124,     0,
     101,     0,     0,   119,     0,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,   -65,   360,    12,  -194,  -194,  -194,   284,  -194,  -194,
    -194,   272,   275,  -194,   184,   -14,    -7,  -194,  -194,   183,
    -194,  -194,   320,   268,   219,  -116,  -194,  -194,  -194,   322,
    -194,  -193,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   -44,
    -194,  -158,  -194,   -53,   -60,   294,     8,  -194
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     8,     9,    46,    69,    70,   203,   162,   105,
      10,    11,    12,    13,    14,    15,    55,    56,    16,    17,
      58,    59,    94,   200,    95,    26,    97,    28,    49,    29,
      73,    30,    31,   124,   125,    91,    99,    53,   126,   241,
     108,   242,   243,   244,   245,   246,   247,   248,   249,    64,
      65,   277,   149,   250,    87,   122,   166,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    68,    47,    27,   164,   106,    18,    22,   170,    38,
      40,   164,   101,    23,    50,    51,    39,    41,   113,   114,
     115,   116,   117,   119,    32,     4,    92,     6,    22,   260,
     156,   121,   127,    19,    23,   150,    42,   165,   207,    93,
      43,     7,    48,    96,   165,   151,    24,    57,   130,   154,
     272,   273,   274,   275,   276,   213,   279,   112,    42,   140,
      44,    21,    43,    22,    45,   121,   110,    24,   258,    23,
     -48,    20,   259,   127,   -48,   173,   175,   177,   179,   181,
     183,   184,   185,   186,   187,   188,   189,   191,   193,   194,
     195,     5,    96,    21,   197,    22,   120,   204,    71,   198,
     300,    23,    24,    72,   199,    34,     2,     3,   210,   -22,
      57,   289,   201,    42,    60,   -22,   127,    43,    21,   214,
      22,   215,    35,   216,    36,   217,    23,   218,   103,   219,
     120,     4,     5,     6,    24,   -44,    92,   221,    22,   222,
     301,    25,   155,   202,    23,   210,   224,     7,   -22,    93,
      50,   281,     4,     5,     6,   -22,   144,   253,   145,    24,
     209,    92,   -36,    22,    37,   255,   251,   257,     7,    23,
      52,   104,   206,   208,    93,   262,   146,    24,    54,    62,
     147,   128,   129,   130,   160,   271,    96,    63,    66,    67,
       4,     5,     6,    89,   140,   278,   226,   110,   227,    75,
      76,    77,    24,    78,    79,    80,     7,    90,   128,   129,
     130,   286,   287,    98,   100,   288,   278,    81,    82,   138,
     139,   140,   141,   228,   229,   230,   102,   231,   232,   233,
     234,   235,   236,   237,   238,    83,   109,    84,   112,   104,
     239,   155,   153,   158,   240,   278,   302,   226,   159,   227,
      75,    76,    77,   168,    78,    79,    80,   169,   196,   128,
     129,   130,   131,   132,   133,   205,   209,   135,    81,    82,
     138,   139,   140,   141,   228,   229,   230,   212,   231,   232,
     233,   234,   235,   236,   237,   238,    83,   254,    84,   256,
     104,    74,    75,    76,    77,   240,    78,    79,    80,   263,
      74,    75,    76,    77,   264,    78,    79,    80,   265,   266,
      81,    82,   128,   129,   130,   131,   132,   133,   267,    81,
      82,   268,   269,   138,   139,   140,   141,    42,    83,   270,
      84,    43,   282,   -78,   -78,   285,   283,    83,   172,    84,
     292,   291,   293,    74,    75,    76,    77,   174,    78,    79,
      80,   294,    74,    75,    76,    77,   298,    78,    79,    80,
     299,   303,    81,    82,   128,   129,   130,   131,   305,   133,
     157,    81,    82,    33,   152,   138,   139,   140,   141,    44,
      83,   161,    84,    45,   225,   -79,   -79,   252,   211,    83,
     176,    84,   107,   111,   171,    74,    75,    76,    77,   178,
      78,    79,    80,     0,    74,    75,    76,    77,     0,    78,
      79,    80,   163,     0,    81,    82,   128,   129,   130,   131,
       0,    44,    61,    81,    82,    45,     0,   138,   139,   140,
     141,     0,    83,     0,    84,     0,     0,     0,     0,     0,
       0,    83,   180,    84,     0,     0,     0,    74,    75,    76,
      77,   182,    78,    79,    80,     0,    74,    75,    76,    77,
       0,    78,    79,    80,     0,     0,    81,    82,     0,     0,
      74,    75,    76,    77,     0,    81,    82,     0,   128,   129,
     130,     0,     0,     0,    83,     0,    84,     0,     0,    81,
      82,   140,   141,    83,   190,    84,     0,     0,     0,    74,
      75,    76,    77,   192,    78,    79,    80,    83,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,    81,    82,
     128,   129,   130,   131,   132,   133,   134,     0,   135,   136,
     137,   138,   139,   140,   141,     0,    83,     0,    84,     0,
       0,     0,     0,     0,     0,   261,   128,   129,   130,   131,
     132,   133,   134,     0,   135,   136,   167,   138,   139,   140,
     141,   142,     0,   143,   128,   129,   130,   131,   132,   133,
     134,   220,   135,   136,   137,   138,   139,   140,   141,   128,
     129,   130,   131,   132,   133,   134,     0,   135,   136,   137,
     138,   139,   140,   141,     0,   128,   129,   130,     0,     0,
       0,     0,     0,     0,     0,   142,   138,   143,   140,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   223,
     142,     0,   143,   128,   129,   130,   131,   132,   133,   134,
       0,   135,   136,   137,   138,   139,   140,   141,   128,   129,
     130,   131,   132,   133,   134,     0,   135,   136,   137,   138,
     139,   140,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   142,   280,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142,
     284,   143,   128,   129,   130,   131,   132,   133,   134,   290,
     135,   136,   137,   138,   139,   140,   141,   128,   129,   130,
     131,   132,   133,   134,     0,   135,   136,   137,   138,   139,
     140,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,     0,   143,     0,     0,     0,     0,
       0,     0,     0,   295,     0,     0,     0,     0,   142,     0,
     143,   128,   129,   130,   131,   132,   133,   134,     0,   135,
     136,   137,   138,   139,   140,   141,   128,   129,   130,   131,
     132,   133,   134,     0,   135,   136,   137,   138,   139,   140,
     141,     0,     0,     0,     0,     0,     0,   296,     0,     0,
       0,     0,   142,     0,   143,     0,     0,     0,     0,     0,
       0,     0,   297,     0,     0,     0,     0,   142,     0,   143,
     128,   129,   130,   131,   132,   133,   134,     0,   135,   136,
     137,   138,   139,   140,   141,   128,   129,   130,   131,   132,
     133,   134,     0,   135,   136,   137,   138,   139,   140,   141,
       0,     0,     0,     0,     0,     0,   304,     0,     0,     0,
       0,   142,     0,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   142,     0,   143,   128,
     129,   130,   131,   132,   133,   134,     0,   135,   136,   137,
     138,   139,   140,   141,    74,    75,    76,    77,     0,    78,
      79,    80,     0,     0,    74,    75,    76,    77,     0,    78,
      79,    80,     0,    81,    82,     0,     0,     0,     0,     0,
       0,     0,   143,    81,    82,     0,     0,     0,     0,     0,
       0,    83,     0,    84,     0,    85,     0,     0,     0,     0,
       0,    83,     0,    84,     0,   123,    74,    75,    76,    77,
       0,    78,    79,    80,    74,    75,    76,    77,     0,    78,
      79,    80,     0,     0,     0,    81,    82,     0,     0,     0,
       0,     0,     0,    81,    82,     0,     4,     0,     6,     0,
       0,     0,     0,    83,     0,    84,   148,     0,     0,     0,
       0,    83,     7,    84,    74,    75,    76,    77,     0,    78,
      79,    80,    74,    75,    76,    77,     0,    78,    79,    80,
       0,     0,     0,    81,    82,     0,     0,     0,     0,     0,
       0,    81,    82,     0,     0,     0,     0,     0,     0,     0,
       0,    83,     0,    84,     0,     0,     0,     0,     0,    83,
       0,   118
};

static const yytype_int16 yycheck[] =
{
      53,    45,     3,    10,     9,    70,    25,     3,   124,    23,
      24,     9,    65,     9,    48,    49,    23,    24,    78,    79,
      80,    81,    82,    83,    12,    25,     1,    27,     3,    14,
      14,    84,    85,     3,     9,    88,    42,    42,    43,    14,
      46,    41,    43,    57,    42,    89,    42,    35,     9,    93,
     243,   244,   245,   246,   247,   171,   249,    42,    42,    20,
      42,     1,    46,     3,    46,   118,    73,    42,    45,     9,
      45,     3,    49,   126,    49,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,    26,   106,     1,   147,     3,    84,   162,    43,    43,
     293,     9,    42,    48,    48,    44,     0,     1,   168,     3,
      98,   269,   156,    42,    43,     9,   169,    46,     1,   172,
       3,   174,    44,   176,    25,   178,     9,   180,     1,   182,
     118,    25,    26,    27,    42,    44,     1,   190,     3,   192,
     298,    49,    48,    49,     9,   205,   199,    41,    42,    14,
      48,    49,    25,    26,    27,    49,    22,    43,    24,    42,
      46,     1,    44,     3,    42,   209,    49,   220,    41,     9,
      50,    44,   164,   165,    14,   228,    42,    42,     3,    43,
      46,     7,     8,     9,    49,   238,   200,    47,    43,    47,
      25,    26,    27,    50,    20,   248,     1,   204,     3,     4,
       5,     6,    42,     8,     9,    10,    41,    48,     7,     8,
       9,   264,   265,    49,    47,   268,   269,    22,    23,    18,
      19,    20,    21,    28,    29,    30,    47,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     3,    42,    42,    44,
      45,    48,    45,    45,    49,   298,   299,     1,    49,     3,
       4,     5,     6,    43,     8,     9,    10,    48,     3,     7,
       8,     9,    10,    11,    12,    43,    46,    15,    22,    23,
      18,    19,    20,    21,    28,    29,    30,    45,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    47,    42,    45,
      44,     3,     4,     5,     6,    49,     8,     9,    10,     3,
       3,     4,     5,     6,    42,     8,     9,    10,    42,    49,
      22,    23,     7,     8,     9,    10,    11,    12,    49,    22,
      23,    42,    42,    18,    19,    20,    21,    42,    40,    14,
      42,    46,    42,    48,    49,    49,    47,    40,    50,    42,
      31,    35,    43,     3,     4,     5,     6,    50,     8,     9,
      10,    43,     3,     4,     5,     6,    49,     8,     9,    10,
      42,    49,    22,    23,     7,     8,     9,    10,    49,    12,
      98,    22,    23,    13,    90,    18,    19,    20,    21,    42,
      40,   106,    42,    46,   200,    48,    49,   204,   169,    40,
      50,    42,    70,    73,   126,     3,     4,     5,     6,    50,
       8,     9,    10,    -1,     3,     4,     5,     6,    -1,     8,
       9,    10,   118,    -1,    22,    23,     7,     8,     9,    10,
      -1,    42,    43,    22,    23,    46,    -1,    18,    19,    20,
      21,    -1,    40,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    50,    42,    -1,    -1,    -1,     3,     4,     5,
       6,    50,     8,     9,    10,    -1,     3,     4,     5,     6,
      -1,     8,     9,    10,    -1,    -1,    22,    23,    -1,    -1,
       3,     4,     5,     6,    -1,    22,    23,    -1,     7,     8,
       9,    -1,    -1,    -1,    40,    -1,    42,    -1,    -1,    22,
      23,    20,    21,    40,    50,    42,    -1,    -1,    -1,     3,
       4,     5,     6,    50,     8,     9,    10,    40,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    -1,    40,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    49,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    43,    18,    19,    20,
      21,    48,    -1,    50,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    -1,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    18,    50,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    50,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,
      50,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    50,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,     3,     4,     5,     6,    -1,     8,
       9,    10,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    10,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    42,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    42,    -1,    44,     3,     4,     5,     6,
      -1,     8,     9,    10,     3,     4,     5,     6,    -1,     8,
       9,    10,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    -1,
      -1,    -1,    -1,    40,    -1,    42,    43,    -1,    -1,    -1,
      -1,    40,    41,    42,     3,     4,     5,     6,    -1,     8,
       9,    10,     3,     4,     5,     6,    -1,     8,     9,    10,
      -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    42,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,     0,     1,    25,    26,    27,    41,    53,    54,
      61,    62,    63,    64,    65,    66,    69,    70,    25,     3,
       3,     1,     3,     9,    42,    49,    76,    77,    78,    80,
      82,    83,    64,    63,    44,    44,    25,    42,    76,    77,
      76,    77,    42,    46,    42,    46,    55,     3,    43,    79,
      48,    49,    50,    88,     3,    67,    68,    64,    71,    72,
      43,    43,    43,    47,   100,   101,    43,    47,   100,    56,
      57,    43,    48,    81,     3,     4,     5,     6,     8,     9,
      10,    22,    23,    40,    42,    44,   104,   105,   108,    50,
      48,    86,     1,    14,    73,    75,    76,    77,    49,    87,
      47,   104,    47,     1,    44,    60,    62,    90,    91,     3,
      77,    83,    42,   105,   105,   105,   105,   105,    42,   105,
      64,   104,   106,    44,    84,    85,    89,   104,     7,     8,
       9,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    21,    48,    50,    22,    24,    42,    46,    43,   103,
     104,   100,    68,    45,   100,    48,    14,    72,    45,    49,
      49,    73,    59,   106,     9,    42,   107,    43,    43,    48,
      86,    84,    50,   104,    50,   104,    50,   104,    50,   104,
      50,   104,    50,   104,   104,   104,   104,   104,   104,   104,
      50,   104,    50,   104,   104,   104,     3,   104,    43,    48,
      74,   100,    49,    58,    62,    43,   107,    43,   107,    46,
     105,    85,    45,    86,   104,   104,   104,   104,   104,   104,
      14,   104,   104,    47,   104,    75,     1,     3,    28,    29,
      30,    32,    33,    34,    35,    36,    37,    38,    39,    45,
      49,    90,    92,    93,    94,    95,    96,    97,    98,    99,
     104,    49,    80,    43,    47,   100,    45,   104,    45,    49,
      14,    49,   104,     3,    42,    42,    49,    49,    42,    42,
      14,   104,    92,    92,    92,    92,    92,   102,   104,    92,
      49,    49,    42,    47,    49,    49,   104,   104,   104,   102,
      14,    35,    31,    43,    43,    43,    43,    43,    49,    42,
      92,   102,   104,    49,    43,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    52,    53,    53,    54,    54,    55,    54,
      56,    57,    57,    58,    58,    59,    59,    59,    60,    60,
      60,    61,    61,    62,    62,    62,    62,    63,    64,    64,
      64,    64,    64,    65,    65,    66,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      74,    73,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      78,    79,    79,    80,    81,    80,    82,    82,    83,    83,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    90,    91,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    93,    93,    93,    94,    95,    96,    97,    98,
      99,   101,   100,   102,   102,   103,   103,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     106,   107,   107,   107,   107,   107,   107,   107,   108,   108
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     2,     3,     0,     4,
       2,     2,     0,     2,     0,     3,     4,     0,     3,     2,
       2,     1,     0,     2,     2,     1,     1,     1,     1,     2,
       3,     1,     1,     5,     2,     1,     2,     1,     3,     1,
       3,     5,     2,     1,     2,     1,     3,     2,     1,     1,
       0,     4,     1,     1,     3,     2,     1,     2,     3,     3,
       4,     1,     3,     2,     3,     3,     4,     3,     3,     2,
       2,     1,     3,     1,     0,     4,     1,     1,     1,     1,
       3,     6,     1,     3,     1,     4,     0,     1,     0,     1,
       0,     1,     1,     4,     1,     2,     1,     2,     2,     2,
       7,     4,     2,     2,     2,     2,     3,     3,     1,     2,
       2,     2,     2,     3,     2,     1,     4,     3,     4,     6,
       4,     0,     2,     1,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     5,     3,
       3,     1,     2,     2,     2,     2,     2,     2,     2,     4,
       4,     4,     2,     3,     3,     1,     1,     1,     1,     3,
       2,     0,     2,     5,     2,     3,     4,     3,     2,     2
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
  case 3: /* ext_def_list: %empty  */
#line 133 "build/gen/mip/pre.y"
                        { ftnend(); }
#line 1661 "build/gen/mip/cgram.c"
    break;

  case 4: /* external_def: data_def  */
#line 136 "build/gen/mip/pre.y"
                        { curclass = SNULL;  blevel = 0; }
#line 1667 "build/gen/mip/cgram.c"
    break;

  case 5: /* external_def: error  */
#line 138 "build/gen/mip/pre.y"
                        { curclass = SNULL;  blevel = 0; }
#line 1673 "build/gen/mip/cgram.c"
    break;

  case 6: /* data_def: oattributes SM  */
#line 142 "build/gen/mip/pre.y"
                        {  (yyvsp[-1].nodep)->op = FREE; }
#line 1679 "build/gen/mip/cgram.c"
    break;

  case 7: /* data_def: oattributes init_dcl_list SM  */
#line 144 "build/gen/mip/pre.y"
                        {  (yyvsp[-2].nodep)->op = FREE; }
#line 1685 "build/gen/mip/cgram.c"
    break;

  case 8: /* $@1: %empty  */
#line 145 "build/gen/mip/pre.y"
                                           {
				defid( tymerge((yyvsp[-1].nodep),(yyvsp[0].nodep)), curclass==STATIC?STATIC:EXTDEF );
				}
#line 1693 "build/gen/mip/cgram.c"
    break;

  case 9: /* data_def: oattributes fdeclarator $@1 function_body  */
#line 148 "build/gen/mip/pre.y"
                        {  
			    if( blevel ) cerror( "function level error" );
			    if( reached ) retstat |= NRETVAL; 
			    (yyvsp[-3].nodep)->op = FREE;
			    ftnend();
			    }
#line 1704 "build/gen/mip/cgram.c"
    break;

  case 12: /* arg_dcl_list: %empty  */
#line 159 "build/gen/mip/pre.y"
                        {  blevel = 1; }
#line 1710 "build/gen/mip/cgram.c"
    break;

  case 14: /* stmt_list: %empty  */
#line 164 "build/gen/mip/pre.y"
                        {  bccode();
			    locctr(PROG);
			    }
#line 1718 "build/gen/mip/cgram.c"
    break;

  case 15: /* dcl_stat_list: dcl_stat_list attributes SM  */
#line 170 "build/gen/mip/pre.y"
                        {  (yyvsp[-1].nodep)->op = FREE; }
#line 1724 "build/gen/mip/cgram.c"
    break;

  case 16: /* dcl_stat_list: dcl_stat_list attributes init_dcl_list SM  */
#line 172 "build/gen/mip/pre.y"
                        {  (yyvsp[-2].nodep)->op = FREE; }
#line 1730 "build/gen/mip/cgram.c"
    break;

  case 18: /* declaration: attributes declarator_list SM  */
#line 176 "build/gen/mip/pre.y"
                        { curclass = SNULL;  (yyvsp[-2].nodep)->op = FREE; }
#line 1736 "build/gen/mip/cgram.c"
    break;

  case 19: /* declaration: attributes SM  */
#line 178 "build/gen/mip/pre.y"
                        { curclass = SNULL;  (yyvsp[-1].nodep)->op = FREE; }
#line 1742 "build/gen/mip/cgram.c"
    break;

  case 20: /* declaration: error SM  */
#line 180 "build/gen/mip/pre.y"
                        {  curclass = SNULL; }
#line 1748 "build/gen/mip/cgram.c"
    break;

  case 22: /* oattributes: %empty  */
#line 184 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = mkty(INT,0,INT);  curclass = SNULL; }
#line 1754 "build/gen/mip/cgram.c"
    break;

  case 23: /* attributes: class type  */
#line 187 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = (yyvsp[0].nodep); }
#line 1760 "build/gen/mip/cgram.c"
    break;

  case 25: /* attributes: class  */
#line 190 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = mkty(INT,0,INT); }
#line 1766 "build/gen/mip/cgram.c"
    break;

  case 26: /* attributes: type  */
#line 192 "build/gen/mip/pre.y"
                        { curclass = SNULL ; }
#line 1772 "build/gen/mip/cgram.c"
    break;

  case 27: /* class: CLASS  */
#line 197 "build/gen/mip/pre.y"
                        {  curclass = (yyvsp[0].intval); }
#line 1778 "build/gen/mip/cgram.c"
    break;

  case 29: /* type: TYPE TYPE  */
#line 202 "build/gen/mip/pre.y"
                        {  (yyvsp[-1].nodep)->type = types( (yyvsp[-1].nodep)->type, (yyvsp[0].nodep)->type, UNDEF );
			    (yyvsp[0].nodep)->op = FREE;
			    }
#line 1786 "build/gen/mip/cgram.c"
    break;

  case 30: /* type: TYPE TYPE TYPE  */
#line 206 "build/gen/mip/pre.y"
                        {  (yyvsp[-2].nodep)->type = types( (yyvsp[-2].nodep)->type, (yyvsp[-1].nodep)->type, (yyvsp[0].nodep)->type );
			    (yyvsp[-1].nodep)->op = (yyvsp[0].nodep)->op = FREE;
			    }
#line 1794 "build/gen/mip/cgram.c"
    break;

  case 33: /* enum_dcl: enum_head LC moe_list optcomma RC  */
#line 214 "build/gen/mip/pre.y"
                        { (yyval.nodep) = dclstruct((yyvsp[-4].intval)); }
#line 1800 "build/gen/mip/cgram.c"
    break;

  case 34: /* enum_dcl: ENUM NAME  */
#line 216 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = rstruct((yyvsp[0].intval),0);  stwart = instruct; }
#line 1806 "build/gen/mip/cgram.c"
    break;

  case 35: /* enum_head: ENUM  */
#line 220 "build/gen/mip/pre.y"
                        {  (yyval.intval) = bstruct(-1,0); }
#line 1812 "build/gen/mip/cgram.c"
    break;

  case 36: /* enum_head: ENUM NAME  */
#line 222 "build/gen/mip/pre.y"
                        {  (yyval.intval) = bstruct((yyvsp[0].intval),0); }
#line 1818 "build/gen/mip/cgram.c"
    break;

  case 39: /* moe: NAME  */
#line 230 "build/gen/mip/pre.y"
                        {  moedef( (yyvsp[0].intval) ); }
#line 1824 "build/gen/mip/cgram.c"
    break;

  case 40: /* moe: NAME ASSIGN con_e  */
#line 232 "build/gen/mip/pre.y"
                        {  strucoff = (yyvsp[0].intval);  moedef( (yyvsp[-2].intval) ); }
#line 1830 "build/gen/mip/cgram.c"
    break;

  case 41: /* struct_dcl: str_head LC type_dcl_list optsemi RC  */
#line 236 "build/gen/mip/pre.y"
                        { (yyval.nodep) = dclstruct((yyvsp[-4].intval));  }
#line 1836 "build/gen/mip/cgram.c"
    break;

  case 42: /* struct_dcl: STRUCT NAME  */
#line 238 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = rstruct((yyvsp[0].intval),(yyvsp[-1].intval)); }
#line 1842 "build/gen/mip/cgram.c"
    break;

  case 43: /* str_head: STRUCT  */
#line 242 "build/gen/mip/pre.y"
                        {  (yyval.intval) = bstruct(-1,(yyvsp[0].intval));  stwart=0; }
#line 1848 "build/gen/mip/cgram.c"
    break;

  case 44: /* str_head: STRUCT NAME  */
#line 244 "build/gen/mip/pre.y"
                        {  (yyval.intval) = bstruct((yyvsp[0].intval),(yyvsp[-1].intval));  stwart=0;  }
#line 1854 "build/gen/mip/cgram.c"
    break;

  case 47: /* type_declaration: type declarator_list  */
#line 252 "build/gen/mip/pre.y"
                        { curclass = SNULL;  stwart=0; (yyvsp[-1].nodep)->op = FREE; }
#line 1860 "build/gen/mip/cgram.c"
    break;

  case 48: /* type_declaration: type  */
#line 254 "build/gen/mip/pre.y"
                        {  if( curclass != MOU ){
				curclass = SNULL;
				}
			    else {
				sprintf( fakename, "$%dFAKE", fake++ );
				defid( tymerge((yyvsp[0].nodep), bdty(NAME,NIL,lookup( fakename, SMOS ))), curclass );
				}
			    stwart = 0;
			    (yyvsp[0].nodep)->op = FREE;
			    }
#line 1875 "build/gen/mip/cgram.c"
    break;

  case 49: /* declarator_list: declarator  */
#line 268 "build/gen/mip/pre.y"
                        { defid( tymerge((yyvsp[-1].nodep),(yyvsp[0].nodep)), curclass);  stwart = instruct; }
#line 1881 "build/gen/mip/cgram.c"
    break;

  case 50: /* @2: %empty  */
#line 269 "build/gen/mip/pre.y"
                                       {(yyval.nodep)=(yyvsp[-2].nodep);}
#line 1887 "build/gen/mip/cgram.c"
    break;

  case 51: /* declarator_list: declarator_list CM @2 declarator  */
#line 270 "build/gen/mip/pre.y"
                        { defid( tymerge((yyvsp[-4].nodep),(yyvsp[0].nodep)), curclass);  stwart = instruct; }
#line 1893 "build/gen/mip/cgram.c"
    break;

  case 54: /* declarator: nfdeclarator COLON con_e  */
#line 276 "build/gen/mip/pre.y"
                        {  if( !(instruct&INSTRUCT) ) uerror( "field outside of structure" );
			    if( (yyvsp[0].intval)<0 || (yyvsp[0].intval) >= FIELD ){
				uerror( "illegal field size" );
				(yyvsp[0].intval) = 1;
				}
			    defid( tymerge((yyvsp[-3].nodep),(yyvsp[-2].nodep)), FIELD|(yyvsp[0].intval) );
			    (yyval.nodep) = NIL;
			    }
#line 1906 "build/gen/mip/cgram.c"
    break;

  case 55: /* declarator: COLON con_e  */
#line 286 "build/gen/mip/pre.y"
                        {  if( !(instruct&INSTRUCT) ) uerror( "field outside of structure" );
			    falloc( stab, (yyvsp[0].intval), -1, (yyvsp[-2].nodep) );  /* alignment or hole */
			    (yyval.nodep) = NIL;
			    }
#line 1915 "build/gen/mip/cgram.c"
    break;

  case 56: /* declarator: error  */
#line 291 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = NIL; }
#line 1921 "build/gen/mip/cgram.c"
    break;

  case 57: /* nfdeclarator: MUL nfdeclarator  */
#line 296 "build/gen/mip/pre.y"
                        {  umul:
				(yyval.nodep) = bdty( UNARY MUL, (yyvsp[0].nodep), 0 ); }
#line 1928 "build/gen/mip/cgram.c"
    break;

  case 58: /* nfdeclarator: nfdeclarator LP RP  */
#line 299 "build/gen/mip/pre.y"
                        {  uftn:
				(yyval.nodep) = bdty( UNARY CALL, (yyvsp[-2].nodep), 0 );  }
#line 1935 "build/gen/mip/cgram.c"
    break;

  case 59: /* nfdeclarator: nfdeclarator LB RB  */
#line 302 "build/gen/mip/pre.y"
                        {  uary:
				(yyval.nodep) = bdty( LB, (yyvsp[-2].nodep), 0 );  }
#line 1942 "build/gen/mip/cgram.c"
    break;

  case 60: /* nfdeclarator: nfdeclarator LB con_e RB  */
#line 305 "build/gen/mip/pre.y"
                        {  bary:
				if( (int)(yyvsp[-1].intval) <= 0 ) werror( "zero or negative subscript" );
				(yyval.nodep) = bdty( LB, (yyvsp[-3].nodep), (yyvsp[-1].intval) );  }
#line 1950 "build/gen/mip/cgram.c"
    break;

  case 61: /* nfdeclarator: NAME  */
#line 309 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = bdty( NAME, NIL, (yyvsp[0].intval) );  }
#line 1956 "build/gen/mip/cgram.c"
    break;

  case 62: /* nfdeclarator: LP nfdeclarator RP  */
#line 311 "build/gen/mip/pre.y"
                        { (yyval.nodep)=(yyvsp[-1].nodep); }
#line 1962 "build/gen/mip/cgram.c"
    break;

  case 63: /* fdeclarator: MUL fdeclarator  */
#line 314 "build/gen/mip/pre.y"
                        {  goto umul; }
#line 1968 "build/gen/mip/cgram.c"
    break;

  case 64: /* fdeclarator: fdeclarator LP RP  */
#line 316 "build/gen/mip/pre.y"
                        {  goto uftn; }
#line 1974 "build/gen/mip/cgram.c"
    break;

  case 65: /* fdeclarator: fdeclarator LB RB  */
#line 318 "build/gen/mip/pre.y"
                        {  goto uary; }
#line 1980 "build/gen/mip/cgram.c"
    break;

  case 66: /* fdeclarator: fdeclarator LB con_e RB  */
#line 320 "build/gen/mip/pre.y"
                        {  goto bary; }
#line 1986 "build/gen/mip/cgram.c"
    break;

  case 67: /* fdeclarator: LP fdeclarator RP  */
#line 322 "build/gen/mip/pre.y"
                        { (yyval.nodep) = (yyvsp[-1].nodep); }
#line 1992 "build/gen/mip/cgram.c"
    break;

  case 68: /* fdeclarator: name_lp name_list RP  */
#line 324 "build/gen/mip/pre.y"
                        {
				if( blevel!=0 ) uerror("function declaration in bad context");
				(yyval.nodep) = bdty( UNARY CALL, bdty(NAME,NIL,(yyvsp[-2].intval)), 0 );
				stwart = 0;
				}
#line 2002 "build/gen/mip/cgram.c"
    break;

  case 69: /* fdeclarator: name_lp RP  */
#line 330 "build/gen/mip/pre.y"
                        {
				(yyval.nodep) = bdty( UNARY CALL, bdty(NAME,NIL,(yyvsp[-1].intval)), 0 );
				stwart = 0;
				}
#line 2011 "build/gen/mip/cgram.c"
    break;

  case 70: /* name_lp: NAME LP  */
#line 337 "build/gen/mip/pre.y"
                        {
				/* turn off typedefs for argument names */
				stwart = SEENAME;
				}
#line 2020 "build/gen/mip/cgram.c"
    break;

  case 71: /* name_list: NAME  */
#line 344 "build/gen/mip/pre.y"
                        { ftnarg( (yyvsp[0].intval) );  stwart = SEENAME; }
#line 2026 "build/gen/mip/cgram.c"
    break;

  case 72: /* name_list: name_list CM NAME  */
#line 346 "build/gen/mip/pre.y"
                        { ftnarg( (yyvsp[0].intval) );  stwart = SEENAME; }
#line 2032 "build/gen/mip/cgram.c"
    break;

  case 74: /* @3: %empty  */
#line 351 "build/gen/mip/pre.y"
                                     {(yyval.nodep)=(yyvsp[-2].nodep);}
#line 2038 "build/gen/mip/cgram.c"
    break;

  case 76: /* xnfdeclarator: nfdeclarator  */
#line 355 "build/gen/mip/pre.y"
                        {  defid( (yyvsp[0].nodep) = tymerge((yyvsp[-1].nodep),(yyvsp[0].nodep)), curclass);
			    beginit((yyvsp[0].nodep)->rval);
			    }
#line 2046 "build/gen/mip/cgram.c"
    break;

  case 78: /* init_declarator: nfdeclarator  */
#line 362 "build/gen/mip/pre.y"
                        {  nidcl( tymerge((yyvsp[-1].nodep),(yyvsp[0].nodep)) ); }
#line 2052 "build/gen/mip/cgram.c"
    break;

  case 79: /* init_declarator: fdeclarator  */
#line 364 "build/gen/mip/pre.y"
                        {  defid( tymerge((yyvsp[-1].nodep),(yyvsp[0].nodep)), uclass(curclass) );
			}
#line 2059 "build/gen/mip/cgram.c"
    break;

  case 80: /* init_declarator: xnfdeclarator optasgn e  */
#line 368 "build/gen/mip/pre.y"
                        {  doinit( (yyvsp[0].nodep) );
			    endinit(); }
#line 2066 "build/gen/mip/cgram.c"
    break;

  case 81: /* init_declarator: xnfdeclarator optasgn LC init_list optcomma RC  */
#line 371 "build/gen/mip/pre.y"
                        {  endinit(); }
#line 2072 "build/gen/mip/cgram.c"
    break;

  case 84: /* initializer: e  */
#line 380 "build/gen/mip/pre.y"
                        {  doinit( (yyvsp[0].nodep) ); }
#line 2078 "build/gen/mip/cgram.c"
    break;

  case 85: /* initializer: ibrace init_list optcomma RC  */
#line 382 "build/gen/mip/pre.y"
                        {  irbrace(); }
#line 2084 "build/gen/mip/cgram.c"
    break;

  case 90: /* optasgn: %empty  */
#line 394 "build/gen/mip/pre.y"
                        {  werror( "old-fashioned initialization: use =" ); }
#line 2090 "build/gen/mip/cgram.c"
    break;

  case 92: /* ibrace: LC  */
#line 399 "build/gen/mip/pre.y"
                        {  ilbrace(); }
#line 2096 "build/gen/mip/cgram.c"
    break;

  case 93: /* compoundstmt: begin dcl_stat_list stmt_list RC  */
#line 405 "build/gen/mip/pre.y"
                        {  --blevel;
			    if( blevel == 1 ) blevel = 0;
			    clearst( blevel );
			    checkst( blevel );
			    autooff = *--psavbc;
			    regvar = *--psavbc;
			    }
#line 2108 "build/gen/mip/cgram.c"
    break;

  case 94: /* begin: LC  */
#line 415 "build/gen/mip/pre.y"
                        {  if( blevel == 1 ) dclargs();
			    ++blevel;
			    if( psavbc > &asavbc[BCSZ-2] ) cerror( "nesting too deep" );
			    *psavbc++ = regvar;
			    *psavbc++ = autooff;
			    }
#line 2119 "build/gen/mip/cgram.c"
    break;

  case 95: /* statement: e SM  */
#line 424 "build/gen/mip/pre.y"
                        { ecomp( (yyvsp[-1].nodep) ); }
#line 2125 "build/gen/mip/cgram.c"
    break;

  case 97: /* statement: ifprefix statement  */
#line 427 "build/gen/mip/pre.y"
                        { deflab((yyvsp[-1].intval));
			   reached = 1;
			   }
#line 2133 "build/gen/mip/cgram.c"
    break;

  case 98: /* statement: ifelprefix statement  */
#line 431 "build/gen/mip/pre.y"
                        {  if( (yyvsp[-1].intval) != NOLAB ){
				deflab( (yyvsp[-1].intval) );
				reached = 1;
				}
			    }
#line 2143 "build/gen/mip/cgram.c"
    break;

  case 99: /* statement: whprefix statement  */
#line 437 "build/gen/mip/pre.y"
                        {  branch(  contlab );
			    deflab( brklab );
			    if( (flostat&FBRK) || !(flostat&FLOOP)) reached = 1;
			    else reached = 0;
			    resetbc(0);
			    }
#line 2154 "build/gen/mip/cgram.c"
    break;

  case 100: /* statement: doprefix statement WHILE LP e RP SM  */
#line 444 "build/gen/mip/pre.y"
                        {  deflab( contlab );
			    if( flostat & FCONT ) reached = 1;
			    ecomp( buildtree( CBRANCH, buildtree( NOT, (yyvsp[-2].nodep), NIL ), bcon( (yyvsp[-6].intval) ) ) );
			    deflab( brklab );
			    reached = 1;
			    resetbc(0);
			    }
#line 2166 "build/gen/mip/cgram.c"
    break;

  case 101: /* statement: forprefix .e RP statement  */
#line 452 "build/gen/mip/pre.y"
                        {  deflab( contlab );
			    if( flostat&FCONT ) reached = 1;
			    if( (yyvsp[-2].nodep) ) ecomp( (yyvsp[-2].nodep) );
			    branch( (yyvsp[-3].intval) );
			    deflab( brklab );
			    if( (flostat&FBRK) || !(flostat&FLOOP) ) reached = 1;
			    else reached = 0;
			    resetbc(0);
			    }
#line 2180 "build/gen/mip/cgram.c"
    break;

  case 102: /* statement: switchpart statement  */
#line 462 "build/gen/mip/pre.y"
                        {  if( reached ) branch( brklab );
			    deflab( (yyvsp[-1].intval) );
			   swend();
			    deflab(brklab);
			    if( (flostat&FBRK) || !(flostat&FDEF) ) reached = 1;
			    resetbc(FCONT);
			    }
#line 2192 "build/gen/mip/cgram.c"
    break;

  case 103: /* statement: BREAK SM  */
#line 470 "build/gen/mip/pre.y"
                        {  if( brklab == NOLAB ) uerror( "illegal break");
			    else if(reached) branch( brklab );
			    flostat |= FBRK;
			    if( brkflag ) goto rch;
			    reached = 0;
			    }
#line 2203 "build/gen/mip/cgram.c"
    break;

  case 104: /* statement: CONTINUE SM  */
#line 477 "build/gen/mip/pre.y"
                        {  if( contlab == NOLAB ) uerror( "illegal continue");
			    else branch( contlab );
			    flostat |= FCONT;
			    goto rch;
			    }
#line 2213 "build/gen/mip/cgram.c"
    break;

  case 105: /* statement: RETURN SM  */
#line 483 "build/gen/mip/pre.y"
                        {  retstat |= NRETVAL;
			    branch( retlab );
			rch:
			    if( !reached ) werror( "statement not reached");
			    reached = 0;
			    }
#line 2224 "build/gen/mip/cgram.c"
    break;

  case 106: /* statement: RETURN e SM  */
#line 490 "build/gen/mip/pre.y"
                        {  register NODE *temp;
			    idname = curftn;
			    temp = buildtree( NAME, NIL, NIL );
			    temp->type = DECREF( temp->type );
			    temp = buildtree( RETURN, temp, (yyvsp[-1].nodep) );
			    /* now, we have the type of the RHS correct */
			    temp->left->op = FREE;
			    temp->op = FREE;
			    ecomp( buildtree( FORCE, temp->right, NIL ) );
			    retstat |= RETVAL;
			    branch( retlab );
			    reached = 0;
			    }
#line 2242 "build/gen/mip/cgram.c"
    break;

  case 107: /* statement: GOTO NAME SM  */
#line 504 "build/gen/mip/pre.y"
                        {  register NODE *q;
			    q = block( FREE, NIL, NIL, INT|ARY, 0, INT );
			    q->rval = idname = (yyvsp[-1].intval);
			    defid( q, ULABEL );
			    stab[idname].suse = -lineno;
			    branch( stab[idname].offset );
			    goto rch;
			    }
#line 2255 "build/gen/mip/cgram.c"
    break;

  case 112: /* label: NAME COLON  */
#line 518 "build/gen/mip/pre.y"
                        {  register NODE *q;
			    q = block( FREE, NIL, NIL, INT|ARY, 0, LABEL );
			    q->rval = (yyvsp[-1].intval);
			    defid( q, LABEL );
			    reached = 1;
			    }
#line 2266 "build/gen/mip/cgram.c"
    break;

  case 113: /* label: CASE e COLON  */
#line 525 "build/gen/mip/pre.y"
                        {  addcase((yyvsp[-1].nodep));
			    reached = 1;
			    }
#line 2274 "build/gen/mip/cgram.c"
    break;

  case 114: /* label: DEFAULT COLON  */
#line 529 "build/gen/mip/pre.y"
                        {  reached = 1;
			    adddef();
			    flostat |= FDEF;
			    }
#line 2283 "build/gen/mip/cgram.c"
    break;

  case 115: /* doprefix: DO  */
#line 535 "build/gen/mip/pre.y"
                        {  savebc();
			    if( !reached ) werror( "loop not entered at top");
			    brklab = getlab();
			    contlab = getlab();
			    deflab( (yyval.intval) = getlab() );
			    reached = 1;
			    }
#line 2295 "build/gen/mip/cgram.c"
    break;

  case 116: /* ifprefix: IF LP e RP  */
#line 544 "build/gen/mip/pre.y"
                        {  ecomp( buildtree( CBRANCH, (yyvsp[-1].nodep), bcon( (yyval.intval)=getlab()) ) ) ;
			    reached = 1;
			    }
#line 2303 "build/gen/mip/cgram.c"
    break;

  case 117: /* ifelprefix: ifprefix statement ELSE  */
#line 549 "build/gen/mip/pre.y"
                        {  if( reached ) branch( (yyval.intval) = getlab() );
			    else (yyval.intval) = NOLAB;
			    deflab( (yyvsp[-2].intval) );
			    reached = 1;
			    }
#line 2313 "build/gen/mip/cgram.c"
    break;

  case 118: /* whprefix: WHILE LP e RP  */
#line 557 "build/gen/mip/pre.y"
                        {  savebc();
			    if( !reached ) werror( "loop not entered at top");
			    if( (yyvsp[-1].nodep)->op == ICON && (yyvsp[-1].nodep)->lval != 0 ) flostat = FLOOP;
			    deflab( contlab = getlab() );
			    reached = 1;
			    brklab = getlab();
			    if( flostat == FLOOP ) tfree( (yyvsp[-1].nodep) );
			    else ecomp( buildtree( CBRANCH, (yyvsp[-1].nodep), bcon( brklab) ) );
			    }
#line 2327 "build/gen/mip/cgram.c"
    break;

  case 119: /* forprefix: FOR LP .e SM .e SM  */
#line 568 "build/gen/mip/pre.y"
                        {  if( (yyvsp[-3].nodep) ) ecomp( (yyvsp[-3].nodep) );
			    else if( !reached ) werror( "loop not entered at top");
			    savebc();
			    contlab = getlab();
			    brklab = getlab();
			    deflab( (yyval.intval) = getlab() );
			    reached = 1;
			    if( (yyvsp[-1].nodep) ) ecomp( buildtree( CBRANCH, (yyvsp[-1].nodep), bcon( brklab) ) );
			    else flostat |= FLOOP;
			    }
#line 2342 "build/gen/mip/cgram.c"
    break;

  case 120: /* switchpart: SWITCH LP e RP  */
#line 580 "build/gen/mip/pre.y"
                        {  savebc();
			    brklab = getlab();
			    ecomp( buildtree( FORCE, (yyvsp[-1].nodep), NIL ) );
			    branch( (yyval.intval) = getlab() );
			    swstart();
			    reached = 0;
			    }
#line 2354 "build/gen/mip/cgram.c"
    break;

  case 121: /* @4: %empty  */
#line 589 "build/gen/mip/pre.y"
                   { (yyval.intval)=instruct; stwart=instruct=0; }
#line 2360 "build/gen/mip/cgram.c"
    break;

  case 122: /* con_e: @4 e  */
#line 591 "build/gen/mip/pre.y"
                        {  (yyval.intval) = icons( (yyvsp[0].nodep) );  instruct=(yyvsp[-1].intval); }
#line 2366 "build/gen/mip/cgram.c"
    break;

  case 124: /* .e: %empty  */
#line 595 "build/gen/mip/pre.y"
                        { (yyval.nodep)=0; }
#line 2372 "build/gen/mip/cgram.c"
    break;

  case 126: /* elist: elist CM e  */
#line 600 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2378 "build/gen/mip/cgram.c"
    break;

  case 127: /* e: e RELOP e  */
#line 604 "build/gen/mip/pre.y"
                        {
			preconf:
			    if( yychar==RELOP||yychar==EQUOP||yychar==AND||yychar==OR||yychar==ER ){
			    precplaint:
				if( hflag ) werror( "precedence confusion possible: parenthesize!" );
				}
			bop:
			    (yyval.nodep) = buildtree( (yyvsp[-1].intval), (yyvsp[-2].nodep), (yyvsp[0].nodep) );
			    }
#line 2392 "build/gen/mip/cgram.c"
    break;

  case 128: /* e: e CM e  */
#line 614 "build/gen/mip/pre.y"
                        {  (yyvsp[-1].intval) = COMOP;
			    goto bop;
			    }
#line 2400 "build/gen/mip/cgram.c"
    break;

  case 129: /* e: e DIVOP e  */
#line 618 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2406 "build/gen/mip/cgram.c"
    break;

  case 130: /* e: e PLUS e  */
#line 620 "build/gen/mip/pre.y"
                        {  if(yychar==SHIFTOP) goto precplaint; else goto bop; }
#line 2412 "build/gen/mip/cgram.c"
    break;

  case 131: /* e: e MINUS e  */
#line 622 "build/gen/mip/pre.y"
                        {  if(yychar==SHIFTOP ) goto precplaint; else goto bop; }
#line 2418 "build/gen/mip/cgram.c"
    break;

  case 132: /* e: e SHIFTOP e  */
#line 624 "build/gen/mip/pre.y"
                        {  if(yychar==PLUS||yychar==MINUS) goto precplaint; else goto bop; }
#line 2424 "build/gen/mip/cgram.c"
    break;

  case 133: /* e: e MUL e  */
#line 626 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2430 "build/gen/mip/cgram.c"
    break;

  case 134: /* e: e EQUOP e  */
#line 628 "build/gen/mip/pre.y"
                        {  goto preconf; }
#line 2436 "build/gen/mip/cgram.c"
    break;

  case 135: /* e: e AND e  */
#line 630 "build/gen/mip/pre.y"
                        {  if( yychar==RELOP||yychar==EQUOP ) goto preconf;  else goto bop; }
#line 2442 "build/gen/mip/cgram.c"
    break;

  case 136: /* e: e OR e  */
#line 632 "build/gen/mip/pre.y"
                        {  if(yychar==RELOP||yychar==EQUOP) goto preconf; else goto bop; }
#line 2448 "build/gen/mip/cgram.c"
    break;

  case 137: /* e: e ER e  */
#line 634 "build/gen/mip/pre.y"
                        {  if(yychar==RELOP||yychar==EQUOP) goto preconf; else goto bop; }
#line 2454 "build/gen/mip/cgram.c"
    break;

  case 138: /* e: e ANDAND e  */
#line 636 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2460 "build/gen/mip/cgram.c"
    break;

  case 139: /* e: e OROR e  */
#line 638 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2466 "build/gen/mip/cgram.c"
    break;

  case 140: /* e: e MUL ASSIGN e  */
#line 640 "build/gen/mip/pre.y"
                        {  abop:
				(yyval.nodep) = buildtree( ASG (yyvsp[-2].intval), (yyvsp[-3].nodep), (yyvsp[0].nodep) );
				}
#line 2474 "build/gen/mip/cgram.c"
    break;

  case 141: /* e: e DIVOP ASSIGN e  */
#line 644 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2480 "build/gen/mip/cgram.c"
    break;

  case 142: /* e: e PLUS ASSIGN e  */
#line 646 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2486 "build/gen/mip/cgram.c"
    break;

  case 143: /* e: e MINUS ASSIGN e  */
#line 648 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2492 "build/gen/mip/cgram.c"
    break;

  case 144: /* e: e SHIFTOP ASSIGN e  */
#line 650 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2498 "build/gen/mip/cgram.c"
    break;

  case 145: /* e: e AND ASSIGN e  */
#line 652 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2504 "build/gen/mip/cgram.c"
    break;

  case 146: /* e: e OR ASSIGN e  */
#line 654 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2510 "build/gen/mip/cgram.c"
    break;

  case 147: /* e: e ER ASSIGN e  */
#line 656 "build/gen/mip/pre.y"
                        {  goto abop; }
#line 2516 "build/gen/mip/cgram.c"
    break;

  case 148: /* e: e QUEST e COLON e  */
#line 658 "build/gen/mip/pre.y"
                        {  (yyval.nodep)=buildtree(QUEST, (yyvsp[-4].nodep), buildtree( COLON, (yyvsp[-2].nodep), (yyvsp[0].nodep) ) );
			    }
#line 2523 "build/gen/mip/cgram.c"
    break;

  case 149: /* e: e ASOP e  */
#line 661 "build/gen/mip/pre.y"
                        {  werror( "old-fashioned assignment operator" );  goto bop; }
#line 2529 "build/gen/mip/cgram.c"
    break;

  case 150: /* e: e ASSIGN e  */
#line 663 "build/gen/mip/pre.y"
                        {  goto bop; }
#line 2535 "build/gen/mip/cgram.c"
    break;

  case 152: /* term: term INCOP  */
#line 667 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = buildtree( (yyvsp[0].intval), (yyvsp[-1].nodep), bcon(1) ); }
#line 2541 "build/gen/mip/cgram.c"
    break;

  case 153: /* term: MUL term  */
#line 669 "build/gen/mip/pre.y"
                        { ubop:
			    (yyval.nodep) = buildtree( UNARY (yyvsp[-1].intval), (yyvsp[0].nodep), NIL );
			    }
#line 2549 "build/gen/mip/cgram.c"
    break;

  case 154: /* term: AND term  */
#line 673 "build/gen/mip/pre.y"
                        {  if( ISFTN((yyvsp[0].nodep)->type) || ISARY((yyvsp[0].nodep)->type) ){
				werror( "& before array or function: ignored" );
				(yyval.nodep) = (yyvsp[0].nodep);
				}
			    else goto ubop;
			    }
#line 2560 "build/gen/mip/cgram.c"
    break;

  case 155: /* term: MINUS term  */
#line 680 "build/gen/mip/pre.y"
                        {  goto ubop; }
#line 2566 "build/gen/mip/cgram.c"
    break;

  case 156: /* term: UNOP term  */
#line 682 "build/gen/mip/pre.y"
                        {
			    (yyval.nodep) = buildtree( (yyvsp[-1].intval), (yyvsp[0].nodep), NIL );
			    }
#line 2574 "build/gen/mip/cgram.c"
    break;

  case 157: /* term: INCOP term  */
#line 686 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = buildtree( (yyvsp[-1].intval)==INCR ? ASG PLUS : ASG MINUS,
						(yyvsp[0].nodep),
						bcon(1)  );
			    }
#line 2583 "build/gen/mip/cgram.c"
    break;

  case 158: /* term: SIZEOF term  */
#line 691 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = doszof( (yyvsp[0].nodep) ); }
#line 2589 "build/gen/mip/cgram.c"
    break;

  case 159: /* term: LP cast_type RP term  */
#line 693 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = buildtree( CAST, (yyvsp[-2].nodep), (yyvsp[0].nodep) );
			    (yyval.nodep)->left->op = FREE;
			    (yyval.nodep)->op = FREE;
			    (yyval.nodep) = (yyval.nodep)->right;
			    }
#line 2599 "build/gen/mip/cgram.c"
    break;

  case 160: /* term: SIZEOF LP cast_type RP  */
#line 699 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = doszof( (yyvsp[-1].nodep) ); }
#line 2605 "build/gen/mip/cgram.c"
    break;

  case 161: /* term: term LB e RB  */
#line 701 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = buildtree( UNARY MUL, buildtree( PLUS, (yyvsp[-3].nodep), (yyvsp[-1].nodep) ), NIL ); }
#line 2611 "build/gen/mip/cgram.c"
    break;

  case 162: /* term: funct_idn RP  */
#line 703 "build/gen/mip/pre.y"
                        {  (yyval.nodep)=buildtree(UNARY CALL,(yyvsp[-1].nodep),NIL); }
#line 2617 "build/gen/mip/cgram.c"
    break;

  case 163: /* term: funct_idn elist RP  */
#line 705 "build/gen/mip/pre.y"
                        {  (yyval.nodep)=buildtree(CALL,(yyvsp[-2].nodep),(yyvsp[-1].nodep)); }
#line 2623 "build/gen/mip/cgram.c"
    break;

  case 164: /* term: term STROP NAME  */
#line 707 "build/gen/mip/pre.y"
                        {  if( (yyvsp[-1].intval) == DOT ){
				(yyvsp[-2].nodep) = buildtree( UNARY AND, (yyvsp[-2].nodep), NIL );
				}
			    idname = (yyvsp[0].intval);
			    (yyval.nodep) = buildtree( STREF, (yyvsp[-2].nodep), buildtree( NAME, NIL, NIL ) );
			    }
#line 2634 "build/gen/mip/cgram.c"
    break;

  case 165: /* term: NAME  */
#line 714 "build/gen/mip/pre.y"
                        {  idname = (yyvsp[0].intval);
			    /* recognize identifiers in initializations */
			    if( blevel==0 && stab[idname].stype == UNDEF ) {
				register NODE *q;
				werror( "undeclared initializer name %.8s", stab[idname].sname );
				q = block( FREE, NIL, NIL, INT, 0, INT );
				q->rval = idname;
				defid( q, EXTERN );
				}
			    (yyval.nodep)=buildtree(NAME,NIL,NIL);
			    stab[(yyvsp[0].intval)].suse = -lineno;
			}
#line 2651 "build/gen/mip/cgram.c"
    break;

  case 166: /* term: ICON  */
#line 727 "build/gen/mip/pre.y"
                        {  (yyval.nodep)=bcon(0);
			    (yyval.nodep)->lval = lastcon;
			    (yyval.nodep)->rval = NONAME;
			    if( (yyvsp[0].intval) ) (yyval.nodep)->csiz = (yyval.nodep)->type = ctype(LONG);
			    }
#line 2661 "build/gen/mip/cgram.c"
    break;

  case 167: /* term: FCON  */
#line 733 "build/gen/mip/pre.y"
                        {  (yyval.nodep)=buildtree(FCON,NIL,NIL);
			    (yyval.nodep)->dval = dcon;
			    }
#line 2669 "build/gen/mip/cgram.c"
    break;

  case 168: /* term: STRING  */
#line 737 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = getstr(); /* get string contents */ }
#line 2675 "build/gen/mip/cgram.c"
    break;

  case 169: /* term: LP e RP  */
#line 739 "build/gen/mip/pre.y"
                        { (yyval.nodep)=(yyvsp[-1].nodep); }
#line 2681 "build/gen/mip/cgram.c"
    break;

  case 170: /* cast_type: type null_decl  */
#line 743 "build/gen/mip/pre.y"
                        {
			(yyval.nodep) = tymerge( (yyvsp[-1].nodep), (yyvsp[0].nodep) );
			(yyval.nodep)->op = NAME;
			(yyvsp[-1].nodep)->op = FREE;
			}
#line 2691 "build/gen/mip/cgram.c"
    break;

  case 171: /* null_decl: %empty  */
#line 751 "build/gen/mip/pre.y"
                        { (yyval.nodep) = bdty( NAME, NIL, -1 ); }
#line 2697 "build/gen/mip/cgram.c"
    break;

  case 172: /* null_decl: LP RP  */
#line 753 "build/gen/mip/pre.y"
                        { (yyval.nodep) = bdty( UNARY CALL, bdty(NAME,NIL,-1),0); }
#line 2703 "build/gen/mip/cgram.c"
    break;

  case 173: /* null_decl: LP null_decl RP LP RP  */
#line 755 "build/gen/mip/pre.y"
                        {  (yyval.nodep) = bdty( UNARY CALL, (yyvsp[-3].nodep), 0 ); }
#line 2709 "build/gen/mip/cgram.c"
    break;

  case 174: /* null_decl: MUL null_decl  */
#line 757 "build/gen/mip/pre.y"
                        {  goto umul; }
#line 2715 "build/gen/mip/cgram.c"
    break;

  case 175: /* null_decl: null_decl LB RB  */
#line 759 "build/gen/mip/pre.y"
                        {  goto uary; }
#line 2721 "build/gen/mip/cgram.c"
    break;

  case 176: /* null_decl: null_decl LB con_e RB  */
#line 761 "build/gen/mip/pre.y"
                        {  goto bary;  }
#line 2727 "build/gen/mip/cgram.c"
    break;

  case 177: /* null_decl: LP null_decl RP  */
#line 763 "build/gen/mip/pre.y"
                        { (yyval.nodep) = (yyvsp[-1].nodep); }
#line 2733 "build/gen/mip/cgram.c"
    break;

  case 178: /* funct_idn: NAME LP  */
#line 767 "build/gen/mip/pre.y"
                        {  if( stab[(yyvsp[-1].intval)].stype == UNDEF ){
				register NODE *q;
				q = block( FREE, NIL, NIL, FTN|INT, 0, INT );
				q->rval = (yyvsp[-1].intval);
				defid( q, EXTERN );
				}
			    idname = (yyvsp[-1].intval);
			    (yyval.nodep)=buildtree(NAME,NIL,NIL);
			    stab[idname].suse = -lineno;
			}
#line 2748 "build/gen/mip/cgram.c"
    break;


#line 2752 "build/gen/mip/cgram.c"

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

#line 779 "build/gen/mip/pre.y"


NODE *
mkty( t, d, s ) unsigned t; {
	return( block( TYPE, NIL, NIL, t, d, s ) );
	}

NODE *
bdty( op, p, v ) NODE *p; {
	register NODE *q;

	q = block( op, p, NIL, INT, 0, INT );

	switch( op ){

	case UNARY MUL:
	case UNARY CALL:
		break;

	case LB:
		q->right = bcon(v);
		break;

	case NAME:
		q->rval = v;
		break;

	default:
		cerror( "bad bdty" );
		}

	return( q );
	}

dstash( n ){ /* put n into the dimension table */
	if( curdim >= DIMTABSZ-1 ){
		cerror( "dimension table overflow");
		}
	dimtab[ curdim++ ] = n;
	}

savebc() {
	if( psavbc > & asavbc[BCSZ-4 ] ){
		cerror( "whiles, fors, etc. too deeply nested");
		}
	*psavbc++ = brklab;
	*psavbc++ = contlab;
	*psavbc++ = flostat;
	*psavbc++ = swx;
	flostat = 0;
	}

resetbc(mask){

	swx = *--psavbc;
	flostat = *--psavbc | (flostat&mask);
	contlab = *--psavbc;
	brklab = *--psavbc;

	}

addcase(p) NODE *p; { /* add case to switch */

	p = optim( p );  /* change enum to ints */
	if( p->op != ICON ){
		uerror( "non-constant case expression");
		return;
		}
	if( swp == swtab ){
		uerror( "case not in switch");
		return;
		}
	if( swp >= &swtab[SWITSZ] ){
		cerror( "switch table overflow");
		}
	swp->sval = p->lval;
	deflab( swp->slab = getlab() );
	++swp;
	tfree(p);
	}

adddef(){ /* add default case to switch */
	if( swtab[swx].slab >= 0 ){
		uerror( "duplicate default in switch");
		return;
		}
	if( swp == swtab ){
		uerror( "default not inside switch");
		return;
		}
	deflab( swtab[swx].slab = getlab() );
	}

swstart(){
	/* begin a switch block */
	if( swp >= &swtab[SWITSZ] ){
		cerror( "switch table overflow");
		}
	swx = swp - swtab;
	swp->slab = -1;
	++swp;
	}

swend(){ /* end a switch block */

	register struct sw *swbeg, *p, *q, *r, *r1;
	CONSZ temp;
	int tempi;

	swbeg = &swtab[swx+1];

	/* sort */

	r1 = swbeg;
	r = swp-1;

	while( swbeg < r ){
		/* bubble largest to end */
		for( q=swbeg; q<r; ++q ){
			if( q->sval > (q+1)->sval ){
				/* swap */
				r1 = q+1;
				temp = q->sval;
				q->sval = r1->sval;
				r1->sval = temp;
				tempi = q->slab;
				q->slab = r1->slab;
				r1->slab = tempi;
				}
			}
		r = r1;
		r1 = swbeg;
		}

	/* it is now sorted */

	for( p = swbeg+1; p<swp; ++p ){
		if( p->sval == (p-1)->sval ){
			uerror( "duplicate case in switch, %d", tempi=p->sval );
			return;
			}
		}

	genswitch( swbeg-1, swp-swbeg );
	swp = swbeg-1;
	}
