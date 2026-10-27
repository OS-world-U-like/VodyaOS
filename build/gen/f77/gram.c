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
#line 96 "build/gen/f77/gram.in"

#include "defs"

static int nstars;
static int ndim;
static int vartype;
static ftnint varleng;
static struct { ptr lb, ub; } dims[8];
static struct labelblock *labarray[MAXLABLIST];
static int lastwasbranch = NO;
static int thiswasbranch = NO;
extern ftnint yystno;

ftnint convci();
double convcd();
struct addrblock *nextdata(), *mkbitcon();
struct constblock *mklogcon(), *mkaddcon(), *mkrealcon();
struct constblock *mkstrcon(), *mkcxcon();
struct listblock *mklist();
struct listblock *mklist();
struct impldoblock *mkiodo();
struct extsym *comblock();


#line 96 "build/gen/f77/y.tab.c"

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
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEOS = 1,                      /* SEOS  */
    SCOMMENT = 2,                  /* SCOMMENT  */
    SLABEL = 3,                    /* SLABEL  */
    SUNKNOWN = 4,                  /* SUNKNOWN  */
    SHOLLERITH = 5,                /* SHOLLERITH  */
    SICON = 6,                     /* SICON  */
    SRCON = 7,                     /* SRCON  */
    SDCON = 8,                     /* SDCON  */
    SBITCON = 9,                   /* SBITCON  */
    SOCTCON = 10,                  /* SOCTCON  */
    SHEXCON = 11,                  /* SHEXCON  */
    STRUE = 12,                    /* STRUE  */
    SFALSE = 13,                   /* SFALSE  */
    SNAME = 14,                    /* SNAME  */
    SNAMEEQ = 15,                  /* SNAMEEQ  */
    SFIELD = 16,                   /* SFIELD  */
    SSCALE = 17,                   /* SSCALE  */
    SINCLUDE = 18,                 /* SINCLUDE  */
    SLET = 19,                     /* SLET  */
    SASSIGN = 20,                  /* SASSIGN  */
    SAUTOMATIC = 21,               /* SAUTOMATIC  */
    SBACKSPACE = 22,               /* SBACKSPACE  */
    SBLOCK = 23,                   /* SBLOCK  */
    SCALL = 24,                    /* SCALL  */
    SCHARACTER = 25,               /* SCHARACTER  */
    SCLOSE = 26,                   /* SCLOSE  */
    SCOMMON = 27,                  /* SCOMMON  */
    SCOMPLEX = 28,                 /* SCOMPLEX  */
    SCONTINUE = 29,                /* SCONTINUE  */
    SDATA = 30,                    /* SDATA  */
    SDCOMPLEX = 31,                /* SDCOMPLEX  */
    SDIMENSION = 32,               /* SDIMENSION  */
    SDO = 33,                      /* SDO  */
    SDOUBLE = 34,                  /* SDOUBLE  */
    SELSE = 35,                    /* SELSE  */
    SELSEIF = 36,                  /* SELSEIF  */
    SEND = 37,                     /* SEND  */
    SENDFILE = 38,                 /* SENDFILE  */
    SENDIF = 39,                   /* SENDIF  */
    SENTRY = 40,                   /* SENTRY  */
    SEQUIV = 41,                   /* SEQUIV  */
    SEXTERNAL = 42,                /* SEXTERNAL  */
    SFORMAT = 43,                  /* SFORMAT  */
    SFUNCTION = 44,                /* SFUNCTION  */
    SGOTO = 45,                    /* SGOTO  */
    SASGOTO = 46,                  /* SASGOTO  */
    SCOMPGOTO = 47,                /* SCOMPGOTO  */
    SARITHIF = 48,                 /* SARITHIF  */
    SLOGIF = 49,                   /* SLOGIF  */
    SIMPLICIT = 50,                /* SIMPLICIT  */
    SINQUIRE = 51,                 /* SINQUIRE  */
    SINTEGER = 52,                 /* SINTEGER  */
    SINTRINSIC = 53,               /* SINTRINSIC  */
    SLOGICAL = 54,                 /* SLOGICAL  */
    SOPEN = 55,                    /* SOPEN  */
    SPARAM = 56,                   /* SPARAM  */
    SPAUSE = 57,                   /* SPAUSE  */
    SPRINT = 58,                   /* SPRINT  */
    SPROGRAM = 59,                 /* SPROGRAM  */
    SPUNCH = 60,                   /* SPUNCH  */
    SREAD = 61,                    /* SREAD  */
    SREAL = 62,                    /* SREAL  */
    SRETURN = 63,                  /* SRETURN  */
    SREWIND = 64,                  /* SREWIND  */
    SSAVE = 65,                    /* SSAVE  */
    SSTATIC = 66,                  /* SSTATIC  */
    SSTOP = 67,                    /* SSTOP  */
    SSUBROUTINE = 68,              /* SSUBROUTINE  */
    STHEN = 69,                    /* STHEN  */
    STO = 70,                      /* STO  */
    SUNDEFINED = 71,               /* SUNDEFINED  */
    SWRITE = 72,                   /* SWRITE  */
    SLPAR = 73,                    /* SLPAR  */
    SRPAR = 74,                    /* SRPAR  */
    SEQUALS = 75,                  /* SEQUALS  */
    SCOLON = 76,                   /* SCOLON  */
    SCOMMA = 77,                   /* SCOMMA  */
    SCURRENCY = 78,                /* SCURRENCY  */
    SPLUS = 79,                    /* SPLUS  */
    SMINUS = 80,                   /* SMINUS  */
    SSTAR = 81,                    /* SSTAR  */
    SSLASH = 82,                   /* SSLASH  */
    SPOWER = 83,                   /* SPOWER  */
    SCONCAT = 84,                  /* SCONCAT  */
    SAND = 85,                     /* SAND  */
    SOR = 86,                      /* SOR  */
    SNEQV = 87,                    /* SNEQV  */
    SEQV = 88,                     /* SEQV  */
    SNOT = 89,                     /* SNOT  */
    SEQ = 90,                      /* SEQ  */
    SLT = 91,                      /* SLT  */
    SGT = 92,                      /* SGT  */
    SLE = 93,                      /* SLE  */
    SGE = 94,                      /* SGE  */
    SNE = 95                       /* SNE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SEOS 1
#define SCOMMENT 2
#define SLABEL 3
#define SUNKNOWN 4
#define SHOLLERITH 5
#define SICON 6
#define SRCON 7
#define SDCON 8
#define SBITCON 9
#define SOCTCON 10
#define SHEXCON 11
#define STRUE 12
#define SFALSE 13
#define SNAME 14
#define SNAMEEQ 15
#define SFIELD 16
#define SSCALE 17
#define SINCLUDE 18
#define SLET 19
#define SASSIGN 20
#define SAUTOMATIC 21
#define SBACKSPACE 22
#define SBLOCK 23
#define SCALL 24
#define SCHARACTER 25
#define SCLOSE 26
#define SCOMMON 27
#define SCOMPLEX 28
#define SCONTINUE 29
#define SDATA 30
#define SDCOMPLEX 31
#define SDIMENSION 32
#define SDO 33
#define SDOUBLE 34
#define SELSE 35
#define SELSEIF 36
#define SEND 37
#define SENDFILE 38
#define SENDIF 39
#define SENTRY 40
#define SEQUIV 41
#define SEXTERNAL 42
#define SFORMAT 43
#define SFUNCTION 44
#define SGOTO 45
#define SASGOTO 46
#define SCOMPGOTO 47
#define SARITHIF 48
#define SLOGIF 49
#define SIMPLICIT 50
#define SINQUIRE 51
#define SINTEGER 52
#define SINTRINSIC 53
#define SLOGICAL 54
#define SOPEN 55
#define SPARAM 56
#define SPAUSE 57
#define SPRINT 58
#define SPROGRAM 59
#define SPUNCH 60
#define SREAD 61
#define SREAL 62
#define SRETURN 63
#define SREWIND 64
#define SSAVE 65
#define SSTATIC 66
#define SSTOP 67
#define SSUBROUTINE 68
#define STHEN 69
#define STO 70
#define SUNDEFINED 71
#define SWRITE 72
#define SLPAR 73
#define SRPAR 74
#define SEQUALS 75
#define SCOLON 76
#define SCOMMA 77
#define SCURRENCY 78
#define SPLUS 79
#define SMINUS 80
#define SSTAR 81
#define SSLASH 82
#define SPOWER 83
#define SCONCAT 84
#define SAND 85
#define SOR 86
#define SNEQV 87
#define SEQV 88
#define SNOT 89
#define SEQ 90
#define SLT 91
#define SGT 92
#define SLE 93
#define SGE 94
#define SNE 95

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEOS = 3,                       /* SEOS  */
  YYSYMBOL_SCOMMENT = 4,                   /* SCOMMENT  */
  YYSYMBOL_SLABEL = 5,                     /* SLABEL  */
  YYSYMBOL_SUNKNOWN = 6,                   /* SUNKNOWN  */
  YYSYMBOL_SHOLLERITH = 7,                 /* SHOLLERITH  */
  YYSYMBOL_SICON = 8,                      /* SICON  */
  YYSYMBOL_SRCON = 9,                      /* SRCON  */
  YYSYMBOL_SDCON = 10,                     /* SDCON  */
  YYSYMBOL_SBITCON = 11,                   /* SBITCON  */
  YYSYMBOL_SOCTCON = 12,                   /* SOCTCON  */
  YYSYMBOL_SHEXCON = 13,                   /* SHEXCON  */
  YYSYMBOL_STRUE = 14,                     /* STRUE  */
  YYSYMBOL_SFALSE = 15,                    /* SFALSE  */
  YYSYMBOL_SNAME = 16,                     /* SNAME  */
  YYSYMBOL_SNAMEEQ = 17,                   /* SNAMEEQ  */
  YYSYMBOL_SFIELD = 18,                    /* SFIELD  */
  YYSYMBOL_SSCALE = 19,                    /* SSCALE  */
  YYSYMBOL_SINCLUDE = 20,                  /* SINCLUDE  */
  YYSYMBOL_SLET = 21,                      /* SLET  */
  YYSYMBOL_SASSIGN = 22,                   /* SASSIGN  */
  YYSYMBOL_SAUTOMATIC = 23,                /* SAUTOMATIC  */
  YYSYMBOL_SBACKSPACE = 24,                /* SBACKSPACE  */
  YYSYMBOL_SBLOCK = 25,                    /* SBLOCK  */
  YYSYMBOL_SCALL = 26,                     /* SCALL  */
  YYSYMBOL_SCHARACTER = 27,                /* SCHARACTER  */
  YYSYMBOL_SCLOSE = 28,                    /* SCLOSE  */
  YYSYMBOL_SCOMMON = 29,                   /* SCOMMON  */
  YYSYMBOL_SCOMPLEX = 30,                  /* SCOMPLEX  */
  YYSYMBOL_SCONTINUE = 31,                 /* SCONTINUE  */
  YYSYMBOL_SDATA = 32,                     /* SDATA  */
  YYSYMBOL_SDCOMPLEX = 33,                 /* SDCOMPLEX  */
  YYSYMBOL_SDIMENSION = 34,                /* SDIMENSION  */
  YYSYMBOL_SDO = 35,                       /* SDO  */
  YYSYMBOL_SDOUBLE = 36,                   /* SDOUBLE  */
  YYSYMBOL_SELSE = 37,                     /* SELSE  */
  YYSYMBOL_SELSEIF = 38,                   /* SELSEIF  */
  YYSYMBOL_SEND = 39,                      /* SEND  */
  YYSYMBOL_SENDFILE = 40,                  /* SENDFILE  */
  YYSYMBOL_SENDIF = 41,                    /* SENDIF  */
  YYSYMBOL_SENTRY = 42,                    /* SENTRY  */
  YYSYMBOL_SEQUIV = 43,                    /* SEQUIV  */
  YYSYMBOL_SEXTERNAL = 44,                 /* SEXTERNAL  */
  YYSYMBOL_SFORMAT = 45,                   /* SFORMAT  */
  YYSYMBOL_SFUNCTION = 46,                 /* SFUNCTION  */
  YYSYMBOL_SGOTO = 47,                     /* SGOTO  */
  YYSYMBOL_SASGOTO = 48,                   /* SASGOTO  */
  YYSYMBOL_SCOMPGOTO = 49,                 /* SCOMPGOTO  */
  YYSYMBOL_SARITHIF = 50,                  /* SARITHIF  */
  YYSYMBOL_SLOGIF = 51,                    /* SLOGIF  */
  YYSYMBOL_SIMPLICIT = 52,                 /* SIMPLICIT  */
  YYSYMBOL_SINQUIRE = 53,                  /* SINQUIRE  */
  YYSYMBOL_SINTEGER = 54,                  /* SINTEGER  */
  YYSYMBOL_SINTRINSIC = 55,                /* SINTRINSIC  */
  YYSYMBOL_SLOGICAL = 56,                  /* SLOGICAL  */
  YYSYMBOL_SOPEN = 57,                     /* SOPEN  */
  YYSYMBOL_SPARAM = 58,                    /* SPARAM  */
  YYSYMBOL_SPAUSE = 59,                    /* SPAUSE  */
  YYSYMBOL_SPRINT = 60,                    /* SPRINT  */
  YYSYMBOL_SPROGRAM = 61,                  /* SPROGRAM  */
  YYSYMBOL_SPUNCH = 62,                    /* SPUNCH  */
  YYSYMBOL_SREAD = 63,                     /* SREAD  */
  YYSYMBOL_SREAL = 64,                     /* SREAL  */
  YYSYMBOL_SRETURN = 65,                   /* SRETURN  */
  YYSYMBOL_SREWIND = 66,                   /* SREWIND  */
  YYSYMBOL_SSAVE = 67,                     /* SSAVE  */
  YYSYMBOL_SSTATIC = 68,                   /* SSTATIC  */
  YYSYMBOL_SSTOP = 69,                     /* SSTOP  */
  YYSYMBOL_SSUBROUTINE = 70,               /* SSUBROUTINE  */
  YYSYMBOL_STHEN = 71,                     /* STHEN  */
  YYSYMBOL_STO = 72,                       /* STO  */
  YYSYMBOL_SUNDEFINED = 73,                /* SUNDEFINED  */
  YYSYMBOL_SWRITE = 74,                    /* SWRITE  */
  YYSYMBOL_SLPAR = 75,                     /* SLPAR  */
  YYSYMBOL_SRPAR = 76,                     /* SRPAR  */
  YYSYMBOL_SEQUALS = 77,                   /* SEQUALS  */
  YYSYMBOL_SCOLON = 78,                    /* SCOLON  */
  YYSYMBOL_SCOMMA = 79,                    /* SCOMMA  */
  YYSYMBOL_SCURRENCY = 80,                 /* SCURRENCY  */
  YYSYMBOL_SPLUS = 81,                     /* SPLUS  */
  YYSYMBOL_SMINUS = 82,                    /* SMINUS  */
  YYSYMBOL_SSTAR = 83,                     /* SSTAR  */
  YYSYMBOL_SSLASH = 84,                    /* SSLASH  */
  YYSYMBOL_SPOWER = 85,                    /* SPOWER  */
  YYSYMBOL_SCONCAT = 86,                   /* SCONCAT  */
  YYSYMBOL_SAND = 87,                      /* SAND  */
  YYSYMBOL_SOR = 88,                       /* SOR  */
  YYSYMBOL_SNEQV = 89,                     /* SNEQV  */
  YYSYMBOL_SEQV = 90,                      /* SEQV  */
  YYSYMBOL_SNOT = 91,                      /* SNOT  */
  YYSYMBOL_SEQ = 92,                       /* SEQ  */
  YYSYMBOL_SLT = 93,                       /* SLT  */
  YYSYMBOL_SGT = 94,                       /* SGT  */
  YYSYMBOL_SLE = 95,                       /* SLE  */
  YYSYMBOL_SGE = 96,                       /* SGE  */
  YYSYMBOL_SNE = 97,                       /* SNE  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_program = 99,                   /* program  */
  YYSYMBOL_stat = 100,                     /* stat  */
  YYSYMBOL_thislabel = 101,                /* thislabel  */
  YYSYMBOL_entry = 102,                    /* entry  */
  YYSYMBOL_new_proc = 103,                 /* new_proc  */
  YYSYMBOL_entryname = 104,                /* entryname  */
  YYSYMBOL_name = 105,                     /* name  */
  YYSYMBOL_progname = 106,                 /* progname  */
  YYSYMBOL_arglist = 107,                  /* arglist  */
  YYSYMBOL_args = 108,                     /* args  */
  YYSYMBOL_arg = 109,                      /* arg  */
  YYSYMBOL_filename = 110,                 /* filename  */
  YYSYMBOL_spec = 111,                     /* spec  */
  YYSYMBOL_dcl = 112,                      /* dcl  */
  YYSYMBOL_type = 113,                     /* type  */
  YYSYMBOL_typespec = 114,                 /* typespec  */
  YYSYMBOL_typename = 115,                 /* typename  */
  YYSYMBOL_lengspec = 116,                 /* lengspec  */
  YYSYMBOL_common = 117,                   /* common  */
  YYSYMBOL_comblock = 118,                 /* comblock  */
  YYSYMBOL_external = 119,                 /* external  */
  YYSYMBOL_intrinsic = 120,                /* intrinsic  */
  YYSYMBOL_equivalence = 121,              /* equivalence  */
  YYSYMBOL_equivset = 122,                 /* equivset  */
  YYSYMBOL_equivlist = 123,                /* equivlist  */
  YYSYMBOL_data = 124,                     /* data  */
  YYSYMBOL_in_data = 125,                  /* in_data  */
  YYSYMBOL_datalist = 126,                 /* datalist  */
  YYSYMBOL_vallist = 127,                  /* vallist  */
  YYSYMBOL_128_1 = 128,                    /* $@1  */
  YYSYMBOL_val = 129,                      /* val  */
  YYSYMBOL_value = 130,                    /* value  */
  YYSYMBOL_savelist = 131,                 /* savelist  */
  YYSYMBOL_saveitem = 132,                 /* saveitem  */
  YYSYMBOL_paramlist = 133,                /* paramlist  */
  YYSYMBOL_paramitem = 134,                /* paramitem  */
  YYSYMBOL_var = 135,                      /* var  */
  YYSYMBOL_datavar = 136,                  /* datavar  */
  YYSYMBOL_datavarlist = 137,              /* datavarlist  */
  YYSYMBOL_dims = 138,                     /* dims  */
  YYSYMBOL_dimlist = 139,                  /* dimlist  */
  YYSYMBOL_140_2 = 140,                    /* $@2  */
  YYSYMBOL_dim = 141,                      /* dim  */
  YYSYMBOL_ubound = 142,                   /* ubound  */
  YYSYMBOL_labellist = 143,                /* labellist  */
  YYSYMBOL_label = 144,                    /* label  */
  YYSYMBOL_labelval = 145,                 /* labelval  */
  YYSYMBOL_implicit = 146,                 /* implicit  */
  YYSYMBOL_implist = 147,                  /* implist  */
  YYSYMBOL_imptype = 148,                  /* imptype  */
  YYSYMBOL_149_3 = 149,                    /* $@3  */
  YYSYMBOL_letgroups = 150,                /* letgroups  */
  YYSYMBOL_letgroup = 151,                 /* letgroup  */
  YYSYMBOL_letter = 152,                   /* letter  */
  YYSYMBOL_in_dcl = 153,                   /* in_dcl  */
  YYSYMBOL_funarglist = 154,               /* funarglist  */
  YYSYMBOL_funargs = 155,                  /* funargs  */
  YYSYMBOL_expr = 156,                     /* expr  */
  YYSYMBOL_uexpr = 157,                    /* uexpr  */
  YYSYMBOL_addop = 158,                    /* addop  */
  YYSYMBOL_relop = 159,                    /* relop  */
  YYSYMBOL_lhs = 160,                      /* lhs  */
  YYSYMBOL_opt_expr = 161,                 /* opt_expr  */
  YYSYMBOL_simple = 162,                   /* simple  */
  YYSYMBOL_simple_const = 163,             /* simple_const  */
  YYSYMBOL_complex_const = 164,            /* complex_const  */
  YYSYMBOL_bit_const = 165,                /* bit_const  */
  YYSYMBOL_fexpr = 166,                    /* fexpr  */
  YYSYMBOL_unpar_fexpr = 167,              /* unpar_fexpr  */
  YYSYMBOL_exec = 168,                     /* exec  */
  YYSYMBOL_logif = 169,                    /* logif  */
  YYSYMBOL_dospec = 170,                   /* dospec  */
  YYSYMBOL_iffable = 171,                  /* iffable  */
  YYSYMBOL_let = 172,                      /* let  */
  YYSYMBOL_goto = 173,                     /* goto  */
  YYSYMBOL_opt_comma = 174,                /* opt_comma  */
  YYSYMBOL_call = 175,                     /* call  */
  YYSYMBOL_callarglist = 176,              /* callarglist  */
  YYSYMBOL_callarg = 177,                  /* callarg  */
  YYSYMBOL_stop = 178,                     /* stop  */
  YYSYMBOL_exprlist = 179,                 /* exprlist  */
  YYSYMBOL_end_spec = 180,                 /* end_spec  */
  YYSYMBOL_io = 181,                       /* io  */
  YYSYMBOL_io1 = 182,                      /* io1  */
  YYSYMBOL_iofmove = 183,                  /* iofmove  */
  YYSYMBOL_fmkwd = 184,                    /* fmkwd  */
  YYSYMBOL_iofctl = 185,                   /* iofctl  */
  YYSYMBOL_ctlkwd = 186,                   /* ctlkwd  */
  YYSYMBOL_infmt = 187,                    /* infmt  */
  YYSYMBOL_ioctl = 188,                    /* ioctl  */
  YYSYMBOL_ctllist = 189,                  /* ctllist  */
  YYSYMBOL_ioclause = 190,                 /* ioclause  */
  YYSYMBOL_nameeq = 191,                   /* nameeq  */
  YYSYMBOL_read = 192,                     /* read  */
  YYSYMBOL_write = 193,                    /* write  */
  YYSYMBOL_print = 194,                    /* print  */
  YYSYMBOL_inlist = 195,                   /* inlist  */
  YYSYMBOL_inelt = 196,                    /* inelt  */
  YYSYMBOL_outlist = 197,                  /* outlist  */
  YYSYMBOL_out2 = 198,                     /* out2  */
  YYSYMBOL_other = 199,                    /* other  */
  YYSYMBOL_in_ioctl = 200                  /* in_ioctl  */
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
#define YYLAST   1189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  497

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
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     2,     2,     2,     2,
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
       0,   138,   138,   139,   142,   144,   145,   153,   155,   157,
     159,   164,   189,   191,   193,   195,   197,   199,   208,   211,
     215,   219,   220,   224,   225,   227,   231,   233,   237,   239,
     245,   253,   254,   255,   256,   257,   258,   259,   260,   262,
     263,   265,   268,   272,   278,   282,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   300,   301,   310,
     314,   316,   318,   320,   324,   326,   330,   332,   336,   338,
     342,   343,   346,   359,   361,   365,   366,   370,   383,   395,
     395,   396,   399,   401,   405,   406,   411,   412,   415,   416,
     419,   426,   430,   431,   434,   443,   447,   460,   475,   477,
     482,   483,   486,   486,   487,   490,   495,   502,   504,   507,
     509,   513,   523,   527,   528,   531,   534,   534,   538,   539,
     542,   544,   548,   559,   572,   573,   576,   578,   583,   584,
     585,   588,   589,   590,   592,   594,   596,   598,   603,   605,
     607,   609,   611,   613,   615,   619,   620,   623,   624,   625,
     626,   627,   628,   631,   633,   635,   637,   642,   643,   646,
     650,   653,   654,   655,   656,   657,   658,   661,   665,   667,
     669,   673,   674,   678,   679,   680,   682,   684,   686,   688,
     693,   696,   697,   704,   706,   707,   709,   711,   715,   719,
     723,   725,   727,   728,   729,   731,   733,   735,   737,   743,
     745,   749,   758,   760,   762,   764,   772,   773,   776,   780,
     782,   789,   790,   794,   796,   800,   802,   807,   817,   821,
     822,   824,   825,   827,   829,   831,   833,   835,   837,   839,
     843,   846,   848,   850,   854,   857,   859,   861,   865,   871,
     879,   881,   885,   886,   889,   891,   893,   895,   899,   903,
     907,   911,   918,   927,   929,   933,   934,   938,   940,   942,
     945,   947,   949,   951,   953,   955,   959,   960,   962,   964,
     969
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
  "\"end of file\"", "error", "\"invalid token\"", "SEOS", "SCOMMENT",
  "SLABEL", "SUNKNOWN", "SHOLLERITH", "SICON", "SRCON", "SDCON", "SBITCON",
  "SOCTCON", "SHEXCON", "STRUE", "SFALSE", "SNAME", "SNAMEEQ", "SFIELD",
  "SSCALE", "SINCLUDE", "SLET", "SASSIGN", "SAUTOMATIC", "SBACKSPACE",
  "SBLOCK", "SCALL", "SCHARACTER", "SCLOSE", "SCOMMON", "SCOMPLEX",
  "SCONTINUE", "SDATA", "SDCOMPLEX", "SDIMENSION", "SDO", "SDOUBLE",
  "SELSE", "SELSEIF", "SEND", "SENDFILE", "SENDIF", "SENTRY", "SEQUIV",
  "SEXTERNAL", "SFORMAT", "SFUNCTION", "SGOTO", "SASGOTO", "SCOMPGOTO",
  "SARITHIF", "SLOGIF", "SIMPLICIT", "SINQUIRE", "SINTEGER", "SINTRINSIC",
  "SLOGICAL", "SOPEN", "SPARAM", "SPAUSE", "SPRINT", "SPROGRAM", "SPUNCH",
  "SREAD", "SREAL", "SRETURN", "SREWIND", "SSAVE", "SSTATIC", "SSTOP",
  "SSUBROUTINE", "STHEN", "STO", "SUNDEFINED", "SWRITE", "SLPAR", "SRPAR",
  "SEQUALS", "SCOLON", "SCOMMA", "SCURRENCY", "SPLUS", "SMINUS", "SSTAR",
  "SSLASH", "SPOWER", "SCONCAT", "SAND", "SOR", "SNEQV", "SEQV", "SNOT",
  "SEQ", "SLT", "SGT", "SLE", "SGE", "SNE", "$accept", "program", "stat",
  "thislabel", "entry", "new_proc", "entryname", "name", "progname",
  "arglist", "args", "arg", "filename", "spec", "dcl", "type", "typespec",
  "typename", "lengspec", "common", "comblock", "external", "intrinsic",
  "equivalence", "equivset", "equivlist", "data", "in_data", "datalist",
  "vallist", "$@1", "val", "value", "savelist", "saveitem", "paramlist",
  "paramitem", "var", "datavar", "datavarlist", "dims", "dimlist", "$@2",
  "dim", "ubound", "labellist", "label", "labelval", "implicit", "implist",
  "imptype", "$@3", "letgroups", "letgroup", "letter", "in_dcl",
  "funarglist", "funargs", "expr", "uexpr", "addop", "relop", "lhs",
  "opt_expr", "simple", "simple_const", "complex_const", "bit_const",
  "fexpr", "unpar_fexpr", "exec", "logif", "dospec", "iffable", "let",
  "goto", "opt_comma", "call", "callarglist", "callarg", "stop",
  "exprlist", "end_spec", "io", "io1", "iofmove", "fmkwd", "iofctl",
  "ctlkwd", "infmt", "ioctl", "ctllist", "ioclause", "nameeq", "read",
  "write", "print", "inlist", "inelt", "outlist", "out2", "other",
  "in_ioctl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-342)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-267)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -342,    54,  -342,  -342,  -342,    14,   882,  -342,  -342,    20,
    -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,
    -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,
    -342,    73,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,
    -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,  -342,
    -342,  -342,  -342,  -342,  -342,    42,  -342,  -342,  -342,  -342,
    -342,  -342,  -342,   -30,    18,    24,  -342,     2,   -26,    44,
      61,    15,    76,  -342,   936,  -342,    73,  -342,    91,  -342,
    -342,  -342,   336,  -342,   115,  -342,   689,   115,   112,  -342,
    -342,   111,    73,    73,    42,  -342,    -2,   111,  -342,   121,
    -342,  -342,  -342,   146,  -342,   167,    73,    73,   111,    73,
     168,   186,   190,  -342,    73,   192,   740,    73,  -342,   610,
     130,  -342,  -342,  -342,   193,  -342,    73,  -342,    73,  -342,
    -342,   637,  -342,    73,    46,    73,    73,   167,  -342,    -2,
    -342,  -342,  -342,   211,    81,   468,   610,  -342,  -342,  -342,
    -342,  -342,  -342,   724,  -342,  -342,   751,  -342,  -342,    67,
     286,  -342,  -342,   724,  -342,  -342,  -342,   219,   225,    12,
     662,   662,  -342,   218,  -342,  -342,  -342,   234,    73,  -342,
      -2,  -342,  -342,   -13,  -342,    73,  -342,   610,    -9,  -342,
      73,  -342,  -342,   146,  -342,   -33,   111,   610,   610,  -342,
     238,   964,  -342,    73,   751,  -342,    67,  -342,  -342,  -342,
     610,   610,  1058,  -342,   610,  -342,  -342,  -342,  -342,   230,
      42,   146,  -342,    24,    73,    24,   362,  1058,  -342,   237,
    -342,  -342,  -342,  -342,  -342,   210,   610,  -342,   111,  1058,
      60,  -342,  -342,  -342,  -342,   311,    66,   255,   480,   232,
     751,   751,   751,   751,   751,  -342,   373,  -342,    40,    40,
      40,  -342,   260,  -342,   662,  1058,    17,    32,  -342,   262,
     263,  -342,    73,  -342,  -342,  -342,   269,    -2,  -342,   261,
    -342,   797,  -342,  -342,  -342,   116,  -342,   151,  -342,  -342,
     274,   152,  -342,   957,   979,   337,  -342,   278,   157,  -342,
     416,  -342,  -342,  1001,   279,   930,   610,   610,   610,   610,
     610,   610,   610,   610,  -342,  -342,  -342,  -342,  -342,  -342,
     610,   610,   272,  -342,  -342,  -342,   234,   146,   234,   284,
      73,   287,   285,  1021,   288,  1058,  -342,  -342,   559,     5,
    -342,   724,   724,  -342,  1058,   232,   232,   232,    79,   124,
    -342,   260,   289,   260,    40,   295,   300,   307,   662,   662,
     662,  -342,   187,   573,    -2,  -342,    50,   766,   610,   296,
    -342,    -4,  -342,    73,   111,   237,   111,   111,  -342,  -342,
     204,  -342,   306,   610,  -342,    73,  -342,  -342,   610,   272,
     272,   272,   120,   930,   163,  1075,  1075,   223,  1092,  -342,
    -342,  -342,  -342,  -342,   315,   610,   610,  -342,    67,  -342,
    -342,    40,  -342,   662,   662,   662,    33,  -342,    34,  -342,
      37,  -342,  -342,   573,  -342,  -342,  -342,  1041,    96,   326,
     766,  -342,  -342,  -342,  -342,   610,  -342,  -342,  -342,   531,
     322,  -342,  -342,  -342,  1058,   327,  -342,  -342,  -342,   208,
     610,  -342,   328,  -342,   337,   337,  1058,  -342,   333,   610,
    1058,   334,   344,   221,   345,   347,   348,  -342,   573,  -342,
    -342,  -342,   766,   610,  -342,  1058,   111,  -342,  -342,  -342,
     351,  -342,  -342,  -342,  -342,  -342,  -342,  1058,  -342,  -342,
    1058,   346,   610,   111,   355,  -342,  -342
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,    10,    11,     0,     0,     3,     9,     0,
     201,   217,    55,   231,    18,   217,    52,   237,   123,    48,
     217,    77,    50,    54,   217,    49,   217,   217,   217,   233,
     217,     0,   123,   123,    40,    18,   217,   217,   217,   217,
     217,   123,   235,    46,   123,    51,   236,   123,   213,   217,
      18,   217,    47,   217,   232,    38,    56,   214,    18,    53,
     217,     4,     5,    31,     0,    57,    45,   206,    33,    34,
      35,   206,    37,     6,     0,   181,     0,   193,   196,   217,
     194,   218,     0,   217,     0,   217,     0,     0,   228,    30,
       7,     0,    21,     0,     0,   192,     0,     0,   186,     0,
       8,   187,    20,    23,    19,     0,     0,     0,     0,     0,
       0,     0,     0,   116,     0,     0,     0,    21,   270,   157,
       0,    64,    90,    91,    39,    88,     0,   270,     0,    18,
     123,     0,    44,   207,     0,     0,     0,     0,   207,     0,
     116,   184,   183,   153,     0,     0,   157,   163,   164,   165,
     166,   161,   162,     0,   145,   146,     0,   173,   174,     0,
     171,   219,   270,     0,   221,   270,   239,   171,     0,   222,
     226,     0,   112,     0,    22,    13,   208,   100,     0,    60,
       0,    75,    98,     0,    96,     0,   111,     0,     0,    17,
       0,    70,    66,    23,   202,   203,     0,     0,     0,   113,
       0,     0,    68,     0,     0,   270,   270,   171,    12,   249,
       0,     0,   158,   128,     0,   131,   199,   132,   130,     0,
       0,    23,   250,    57,     0,    57,     0,    58,    63,   206,
      67,    69,    71,    76,   114,   124,     0,   197,     0,   211,
       0,   209,   200,   248,   245,   244,     0,     0,     0,   179,
       0,     0,     0,     0,     0,   230,   244,   234,     0,     0,
       0,   255,   223,   253,     0,     0,   128,   130,   227,   259,
     258,   229,     0,   102,    95,    61,     0,     0,    79,     0,
     182,     0,    24,    29,    28,     0,    26,     0,    73,    15,
       0,     0,   109,     0,     0,     0,   117,     0,     0,    92,
       0,   252,   251,     0,   128,   143,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   149,   148,   151,   150,   152,
       0,     0,   137,    65,    89,    14,   100,    23,   100,     0,
       0,     0,   125,   126,     0,   190,   212,   198,     0,   172,
     241,     0,     0,   247,   246,   176,   177,   178,   180,   175,
     240,   224,     0,   225,     0,   128,     0,     0,     0,     0,
       0,   191,     0,     0,     0,    99,     0,     0,     0,     0,
      25,     0,    72,     0,     0,   206,     0,     0,   188,   122,
       0,   118,   120,     0,    41,     0,   172,   129,     0,   134,
     135,   136,   144,   142,   141,   140,   139,   133,   138,    43,
      16,    42,    59,    62,   155,     0,   157,   210,   244,   243,
     242,     0,   254,     0,     0,     0,   128,   261,   128,   265,
     128,   263,   101,     0,   107,   103,   105,   108,   153,     0,
       0,    78,   170,   169,   168,     0,   159,    80,    82,     0,
      84,   160,    86,    87,   215,   189,   185,    27,    74,     0,
       0,   110,     0,   115,     0,     0,    94,    93,   128,   157,
     127,     0,     0,   128,     0,     0,     0,   104,     0,    97,
      81,    85,     0,     0,   204,   205,     0,   119,   121,   167,
       0,   154,   256,   267,   269,   268,   106,   108,    83,    84,
     216,     0,   157,     0,     0,   195,   156
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -342,  -342,  -342,  -342,  -342,   -19,    -8,   -31,   318,  -189,
    -342,    65,  -342,  -342,  -342,   231,  -342,  -342,    87,  -342,
     -69,  -342,  -342,  -342,   302,  -342,  -342,  -342,   301,  -342,
    -342,    16,   -25,  -342,   240,  -342,    77,  -130,  -271,   270,
     -91,  -342,  -342,    38,    -1,    92,   -95,   374,  -342,   329,
    -342,  -342,  -342,    19,    26,    -3,  -342,  -342,   216,  -120,
     -71,  -342,   352,  -127,  -341,   -39,  -161,  -342,   259,   -14,
    -342,  -342,  -227,   396,  -342,  -342,   -70,  -342,  -342,   133,
    -342,  -342,   816,  -342,  -342,  -342,  -342,  -342,  -342,  -342,
      83,  -342,  -272,  -342,  -342,  -342,  -342,    71,  -302,   303,
     215,  -238,  -105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     5,     6,    61,    92,   174,   143,   175,   189,
     285,   286,    90,    62,    63,    64,    65,    66,   132,    67,
     123,    68,    69,    70,   191,   287,    71,    96,   181,   366,
     367,   437,   438,   124,   125,   298,   299,   179,   182,   183,
     274,   362,   363,   425,   426,   291,   292,   186,    72,   199,
     200,   201,   380,   381,   382,    94,   331,   332,   265,   213,
     214,   321,   215,   216,   440,   217,   218,   443,   159,   207,
      73,    74,   280,    75,    76,    77,   134,    78,   240,   241,
      79,   445,    91,    80,    81,    82,    83,    84,    85,   168,
     161,   246,   247,   248,    86,    87,    88,   262,   263,   268,
     269,   270,   209
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   139,   185,   228,   289,   -32,   365,   102,  -240,   267,
     267,   156,   102,   194,   102,   156,   107,     7,   -36,   242,
    -257,  -240,   222,   103,   122,   178,   357,    89,   102,   105,
     106,   117,   325,   130,   102,  -266,  -260,  -264,   113,   126,
    -262,   114,  -206,   158,   115,   156,   138,   158,   275,   128,
     266,   266,   412,   135,     2,     3,   102,   255,   102,     4,
     257,   104,   176,   177,   129,   229,   277,   282,   160,   409,
     410,   278,   167,   180,   283,   192,   104,   158,   195,   283,
    -240,   133,   156,   202,  -240,   156,   104,   259,   254,   102,
     304,   260,   156,   365,   138,   104,   358,   223,   471,   193,
     301,   302,   177,   267,   230,   231,   304,   131,   334,   412,
     224,  -266,  -260,  -264,   158,   259,  -262,   158,   221,   172,
     417,   419,   421,   136,   158,   290,   120,   225,   121,   430,
     120,   489,   121,   156,   431,   254,   337,   429,   400,   338,
     137,   320,   340,   336,   355,   341,   219,   177,   154,   155,
     250,   251,   252,   253,   279,   140,   320,   284,   236,   330,
     154,   155,   250,   251,   252,   158,   145,   164,   320,   169,
     170,   235,   297,   368,   254,   417,   419,   421,   254,   156,
     156,   156,   156,   156,   462,   254,   464,   465,   466,   122,
     163,   171,   370,   104,   320,   371,   187,   267,   267,   267,
     403,   154,   155,   306,   307,   308,   442,   250,   251,   252,
     320,   158,   158,   158,   158,   158,   327,   147,   148,   149,
     150,   188,   320,   320,   151,   152,   102,   372,   375,   254,
     373,   376,   320,   384,   320,   399,   385,   401,   416,   418,
     420,   361,   190,   196,   154,   155,   306,   307,   308,   309,
     310,   320,   267,   267,   267,   314,   315,   316,   317,   318,
     319,   197,   320,   422,   320,   198,   423,   203,   458,   442,
     156,   156,   220,   320,   254,   254,   254,   254,   254,   461,
     453,   451,   452,   454,   474,   210,   235,   376,  -157,  -220,
     272,   154,   155,   463,   418,   420,   439,   479,  -238,   177,
    -260,   211,   158,   158,   258,   450,   306,   307,   308,   273,
     326,   442,   328,   295,   323,   304,   138,   252,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   441,   351,
     352,   353,   480,   428,   342,   212,   436,   254,   368,   354,
     284,   359,   360,   147,   148,   149,   150,   227,   364,   374,
     151,   152,   102,   379,   297,   383,   320,   308,   388,   439,
     402,   239,   212,   404,   405,   494,   406,   446,   411,   147,
     148,   149,   150,   320,   413,   206,   151,   152,   102,   414,
     428,   491,   428,   428,   428,   320,   415,   339,   455,   320,
     459,   441,   154,   155,   250,   251,   252,   253,   495,   436,
     441,   439,   469,   281,   320,   472,   473,   476,   436,   479,
     481,   153,   245,   293,   294,   249,   320,   154,   155,   320,
     482,   483,   256,   484,   485,   493,   303,   305,   144,   492,
     322,   496,   296,   441,   157,   208,   447,   210,   157,   232,
     233,   436,   303,   154,   155,   329,   470,   488,   184,   350,
     276,   333,   335,   211,   154,   155,   250,   251,   252,   253,
     324,   467,   457,   300,   344,   173,   449,   486,   157,   234,
     142,   407,     0,   477,   271,   147,   148,   149,   150,   356,
     303,   478,   151,   152,   102,     0,     0,   147,   148,   149,
     150,   184,   386,     0,   151,   152,   102,   154,   155,   250,
     251,   252,   253,     0,     0,   157,     0,     0,   157,   345,
     346,   347,   348,   349,     0,   157,     0,     0,     0,     0,
       0,   261,   389,   390,   391,   392,   393,   394,   395,   396,
       0,     0,   184,     0,     0,     0,   397,   398,   147,   148,
     149,   150,   288,   210,   237,   151,   152,   102,     0,   154,
     155,   238,     0,     0,   239,   210,   157,     0,     0,   211,
       0,   154,   155,   343,     0,     0,   147,   148,   149,   150,
       0,   211,     0,   151,   152,   102,     0,     0,     0,   427,
     147,   148,   149,   150,   444,     0,     0,   151,   152,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   456,
     408,   408,   157,   157,   157,   157,   157,     0,     0,     0,
     261,   261,   261,     0,     0,     0,     0,   147,   148,   149,
     150,   460,   212,     0,   151,   152,   102,     0,     0,   184,
       0,     0,     0,     0,   210,     0,     0,     0,     0,   427,
     154,   155,   238,     0,   147,   148,   149,   150,   210,     0,
     211,   151,   152,   102,   154,   155,   424,     0,     0,     0,
       0,     0,     0,     0,   211,     0,   475,     0,     0,   147,
     148,   149,   150,     0,     0,   212,   151,   152,   102,     0,
       0,     0,     0,     0,   487,   210,     0,     0,     0,   490,
       0,   154,   155,   157,   157,     0,   147,   148,   149,   150,
       0,   211,     0,   151,   152,   102,   261,     0,   212,     0,
       0,     0,   226,     0,     0,     0,   184,     0,   154,   155,
       0,     0,     0,     0,     0,   448,     0,     0,   211,     0,
       0,   147,   148,   149,   150,     0,     0,   264,   151,   152,
     102,   243,     0,   154,   155,     0,     0,   147,   148,   149,
     150,     0,     0,   211,   151,   152,   102,     0,   147,   148,
     149,   150,     0,   261,   153,   151,   152,   102,     0,     0,
     154,   155,   166,   147,   148,   149,   150,   432,   433,   434,
     151,   152,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
       0,     0,     0,     0,     0,   154,   155,   244,     0,     0,
       0,     0,     0,     0,     0,   204,     0,     0,     0,     0,
       0,   154,   155,   205,     0,     0,   204,     0,     0,     0,
       0,    93,   154,   155,     0,     0,    95,     0,     0,     0,
      97,   435,    98,    99,   100,     0,   101,   154,   155,     0,
       0,     0,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,   116,     0,   118,     0,   119,
       0,     0,     0,   369,     0,     0,   127,     0,   154,   155,
     306,   307,   308,   309,   310,   311,   312,   313,     8,   314,
     315,   316,   317,   318,   319,   146,     0,     0,     0,   162,
       0,   165,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,     0,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,    59,    60,    10,    11,     0,
      13,     0,    15,     0,    17,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    39,    12,     0,    42,
       0,    16,     0,    46,    19,    48,    49,    22,    23,    51,
      25,    53,    54,     0,     0,    57,     0,   141,     0,     0,
      60,   154,   155,   306,   307,   308,   309,     0,    43,     0,
      45,     0,   314,   315,   316,   317,   318,   319,    52,     0,
       0,     0,    56,   377,     0,     0,     0,    59,   154,   155,
     306,   307,   308,   309,   310,   311,   312,   313,     0,   314,
     315,   316,   317,   318,   319,   378,     0,     0,     0,     0,
     154,   155,   306,   307,   308,   309,   310,   311,   312,   313,
       0,   314,   315,   316,   317,   318,   319,   387,     0,     0,
       0,     0,   154,   155,   306,   307,   308,   309,   310,   311,
     312,   313,     0,   314,   315,   316,   317,   318,   319,  -158,
       0,     0,   154,   155,   306,   307,   308,   309,   310,   311,
     312,   313,     0,   314,   315,   316,   317,   318,   319,   468,
       0,     0,   154,   155,   306,   307,   308,   309,   310,   311,
     312,   313,     0,   314,   315,   316,   317,   318,   319,   154,
     155,   306,   307,   308,   309,   310,   311,   312,   313,     0,
     314,   315,   316,   317,   318,   319,   154,   155,   306,   307,
     308,   309,   310,   311,     0,     0,     0,   314,   315,   316,
     317,   318,   319,   154,   155,   306,   307,   308,   309,     0,
       0,     0,     0,     0,  -267,  -267,  -267,  -267,  -267,  -267
};

static const yytype_int16 yycheck[] =
{
      31,    71,    97,   133,   193,     3,   277,    16,     3,   170,
     171,    82,    16,   108,    16,    86,    35,     3,     3,   146,
       3,    16,   127,    31,    55,    94,   264,     7,    16,    32,
      33,    50,   221,    64,    16,     3,     3,     3,    41,    58,
       3,    44,    75,    82,    47,   116,    79,    86,   178,    79,
     170,   171,   354,    79,     0,     1,    16,   162,    16,     5,
     165,    92,    93,    94,    46,   134,    79,    76,    82,   341,
     342,    84,    86,    75,    83,   106,   107,   116,   109,    83,
      75,    79,   153,   114,    79,   156,   117,    75,   159,    16,
     210,    79,   163,   364,    79,   126,    79,   128,   439,   107,
     205,   206,   133,   264,   135,   136,   226,    83,   235,   411,
     129,    79,    79,    79,   153,    75,    79,   156,   126,     8,
     358,   359,   360,    79,   163,   195,    84,   130,    86,    79,
      84,   472,    86,   204,    84,   206,    76,   364,   327,    79,
      79,   212,    76,   238,   264,    79,    16,   178,    81,    82,
      83,    84,    85,    86,   185,    79,   227,   188,    77,   229,
      81,    82,    83,    84,    85,   204,    75,    84,   239,    86,
      87,    75,   203,    77,   245,   413,   414,   415,   249,   250,
     251,   252,   253,   254,   411,   256,   413,   414,   415,   220,
      75,    79,    76,   224,   265,    79,    75,   358,   359,   360,
     330,    81,    82,    83,    84,    85,   367,    83,    84,    85,
     281,   250,   251,   252,   253,   254,   224,     7,     8,     9,
      10,    75,   293,   294,    14,    15,    16,    76,    76,   300,
      79,    79,   303,    76,   305,   326,    79,   328,   358,   359,
     360,   272,    75,    75,    81,    82,    83,    84,    85,    86,
      87,   322,   413,   414,   415,    92,    93,    94,    95,    96,
      97,    75,   333,    76,   335,    75,    79,    75,   388,   430,
     341,   342,    79,   344,   345,   346,   347,   348,   349,   406,
      76,   376,   377,    79,    76,    75,    75,    79,    78,     3,
      72,    81,    82,   413,   414,   415,   367,    76,    79,   330,
      79,    91,   341,   342,    79,   375,    83,    84,    85,    75,
     223,   472,   225,    75,    84,   435,    79,    85,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   367,   258,
     259,   260,   459,   364,    79,   119,   367,   408,    77,    79,
     371,    79,    79,     7,     8,     9,    10,   131,    79,    75,
      14,    15,    16,    16,   385,    77,   427,    85,    79,   430,
      76,   145,   146,    76,    79,   492,    78,    71,    79,     7,
       8,     9,    10,   444,    79,   116,    14,    15,    16,    79,
     411,   476,   413,   414,   415,   456,    79,    76,    82,   460,
      75,   430,    81,    82,    83,    84,    85,    86,   493,   430,
     439,   472,    76,   187,   475,    83,    79,    79,   439,    76,
      76,    75,   153,   197,   198,   156,   487,    81,    82,   490,
      76,    76,   163,    76,    76,    79,   210,   211,    76,    78,
     214,    76,   201,   472,    82,   117,   371,    75,    86,   137,
     139,   472,   226,    81,    82,    83,   430,   472,    96,    76,
     180,   235,   236,    91,    81,    82,    83,    84,    85,    86,
     220,   423,   385,   204,   248,    91,   374,   468,   116,   140,
      74,   338,    -1,   454,   171,     7,     8,     9,    10,   264,
     264,   455,    14,    15,    16,    -1,    -1,     7,     8,     9,
      10,   139,    76,    -1,    14,    15,    16,    81,    82,    83,
      84,    85,    86,    -1,    -1,   153,    -1,    -1,   156,   250,
     251,   252,   253,   254,    -1,   163,    -1,    -1,    -1,    -1,
      -1,   169,   306,   307,   308,   309,   310,   311,   312,   313,
      -1,    -1,   180,    -1,    -1,    -1,   320,   321,     7,     8,
       9,    10,   190,    75,    76,    14,    15,    16,    -1,    81,
      82,    83,    -1,    -1,   338,    75,   204,    -1,    -1,    91,
      -1,    81,    82,    83,    -1,    -1,     7,     8,     9,    10,
      -1,    91,    -1,    14,    15,    16,    -1,    -1,    -1,   363,
       7,     8,     9,    10,   368,    -1,    -1,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   383,
     341,   342,   250,   251,   252,   253,   254,    -1,    -1,    -1,
     258,   259,   260,    -1,    -1,    -1,    -1,     7,     8,     9,
      10,   405,   406,    -1,    14,    15,    16,    -1,    -1,   277,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,   423,
      81,    82,    83,    -1,     7,     8,     9,    10,    75,    -1,
      91,    14,    15,    16,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    -1,   450,    -1,    -1,     7,
       8,     9,    10,    -1,    -1,   459,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,   468,    75,    -1,    -1,    -1,   473,
      -1,    81,    82,   341,   342,    -1,     7,     8,     9,    10,
      -1,    91,    -1,    14,    15,    16,   354,    -1,   492,    -1,
      -1,    -1,    75,    -1,    -1,    -1,   364,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    91,    -1,
      -1,     7,     8,     9,    10,    -1,    -1,    75,    14,    15,
      16,    17,    -1,    81,    82,    -1,    -1,     7,     8,     9,
      10,    -1,    -1,    91,    14,    15,    16,    -1,     7,     8,
       9,    10,    -1,   411,    75,    14,    15,    16,    -1,    -1,
      81,    82,    83,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    15,    81,    82,    -1,    -1,    20,    -1,    -1,    -1,
      24,    75,    26,    27,    28,    -1,    30,    81,    82,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    -1,    53,
      -1,    -1,    -1,    76,    -1,    -1,    60,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     6,    92,
      93,    94,    95,    96,    97,    79,    -1,    -1,    -1,    83,
      -1,    85,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    73,    74,    21,    22,    -1,
      24,    -1,    26,    -1,    28,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    23,    -1,    53,
      -1,    27,    -1,    57,    30,    59,    60,    33,    34,    63,
      36,    65,    66,    -1,    -1,    69,    -1,    71,    -1,    -1,
      74,    81,    82,    83,    84,    85,    86,    -1,    54,    -1,
      56,    -1,    92,    93,    94,    95,    96,    97,    64,    -1,
      -1,    -1,    68,    76,    -1,    -1,    -1,    73,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      93,    94,    95,    96,    97,    76,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      -1,    92,    93,    94,    95,    96,    97,    76,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    -1,    92,    93,    94,    95,    96,    97,    78,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    -1,    92,    93,    94,    95,    96,    97,    78,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    -1,    92,    93,    94,    95,    96,    97,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    -1,
      92,    93,    94,    95,    96,    97,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    81,    82,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    99,     0,     1,     5,   100,   101,     3,     6,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    63,    64,    65,    66,    67,    68,    69,    70,    73,
      74,   102,   111,   112,   113,   114,   115,   117,   119,   120,
     121,   124,   146,   168,   169,   171,   172,   173,   175,   178,
     181,   182,   183,   184,   185,   186,   192,   193,   194,     7,
     110,   180,   103,   180,   153,   180,   125,   180,   180,   180,
     180,   180,    16,   104,   105,   153,   153,   103,   180,   180,
     180,   180,   180,   153,   153,   153,   180,   103,   180,   180,
      84,    86,   105,   118,   131,   132,   103,   180,    79,    46,
     105,    83,   116,    79,   174,    79,    79,    79,    79,   174,
      79,    71,   171,   105,   160,    75,   180,     7,     8,     9,
      10,    14,    15,    75,    81,    82,   158,   160,   163,   166,
     167,   188,   180,    75,   188,   180,    83,   167,   187,   188,
     188,    79,     8,   145,   104,   106,   105,   105,   118,   135,
      75,   126,   136,   137,   160,   144,   145,    75,    75,   107,
      75,   122,   105,   104,   144,   105,    75,    75,    75,   147,
     148,   149,   105,    75,    75,    83,   166,   167,   106,   200,
      75,    91,   156,   157,   158,   160,   161,   163,   164,    16,
      79,   104,   200,   105,   103,   153,    75,   156,   135,   118,
     105,   105,   122,   126,   147,    75,    77,    76,    83,   156,
     176,   177,   161,    17,    83,   166,   189,   190,   191,   166,
      83,    84,    85,    86,   158,   200,   166,   200,    79,    75,
      79,   160,   195,   196,    75,   156,   157,   164,   197,   198,
     199,   197,    72,    75,   138,   135,   137,    79,    84,   105,
     170,   156,    76,    83,   105,   108,   109,   123,   160,   107,
     174,   143,   144,   156,   156,    75,   113,   105,   133,   134,
     166,   200,   200,   156,   157,   156,    83,    84,    85,    86,
      87,    88,    89,    90,    92,    93,    94,    95,    96,    97,
     158,   159,   156,    84,   132,   107,   116,   104,   116,    83,
     174,   154,   155,   156,   161,   156,   144,    76,    79,    76,
      76,    79,    79,    83,   156,   166,   166,   166,   166,   166,
      76,   195,   195,   195,    79,   157,   198,   199,    79,    79,
      79,   105,   139,   140,    79,   136,   127,   128,    77,    76,
      76,    79,    76,    79,    75,    76,    79,    76,    76,    16,
     150,   151,   152,    77,    76,    79,    76,    76,    79,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   138,
     107,   138,    76,   135,    76,    79,    78,   177,   166,   190,
     190,    79,   196,    79,    79,    79,   157,   199,   157,   199,
     157,   199,    76,    79,    83,   141,   142,   156,   105,   170,
      79,    84,    11,    12,    13,    75,   105,   129,   130,   158,
     162,   163,   164,   165,   156,   179,    71,   109,   160,   143,
     174,   144,   144,    76,    79,    82,   156,   134,   157,    75,
     156,   161,   170,   157,   170,   170,   170,   141,    78,    76,
     129,   162,    83,    79,    76,   156,    79,   151,   152,    76,
     161,    76,    76,    76,    76,    76,   142,   156,   130,   162,
     156,   144,    78,    79,   161,   144,    76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   101,   102,   102,   102,   102,   102,   102,   103,   104,
     105,   106,   106,   107,   107,   107,   108,   108,   109,   109,
     110,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   113,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     117,   117,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   123,   123,   124,   124,   125,   126,   128,
     127,   127,   129,   129,   130,   130,   130,   130,   131,   131,
     132,   132,   133,   133,   134,   135,   136,   136,   137,   137,
     138,   138,   140,   139,   139,   141,   141,   142,   142,   143,
     143,   144,   145,   146,   146,   147,   149,   148,   150,   150,
     151,   151,   152,   153,   154,   154,   155,   155,   156,   156,
     156,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   158,   158,   159,   159,   159,
     159,   159,   159,   160,   160,   160,   160,   161,   161,   162,
     162,   163,   163,   163,   163,   163,   163,   164,   165,   165,
     165,   166,   166,   167,   167,   167,   167,   167,   167,   167,
     167,   168,   168,   168,   168,   168,   168,   168,   169,   170,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   172,   173,   173,   173,   173,   174,   174,   175,   176,
     176,   177,   177,   178,   178,   179,   179,   180,   181,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     183,   184,   184,   184,   185,   186,   186,   186,   187,   187,
     188,   188,   189,   189,   190,   190,   190,   190,   191,   192,
     193,   194,   194,   195,   195,   196,   196,   197,   197,   197,
     198,   198,   198,   198,   198,   198,   199,   199,   199,   199,
     200
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     2,     2,     3,     3,     2,
       1,     1,     3,     3,     4,     4,     5,     3,     0,     1,
       1,     0,     1,     0,     2,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     5,     5,     5,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     4,
       3,     4,     5,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     0,     4,     0,
       2,     3,     1,     3,     1,     2,     1,     1,     1,     3,
       1,     1,     1,     3,     3,     2,     1,     5,     1,     3,
       0,     3,     0,     2,     3,     1,     3,     1,     1,     1,
       3,     1,     1,     3,     3,     4,     0,     2,     1,     3,
       1,     3,     1,     0,     0,     1,     1,     3,     1,     3,
       1,     1,     1,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     4,     9,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     1,     1,
       1,     1,     3,     1,     1,     3,     3,     3,     3,     2,
       3,     1,     4,     2,     2,     6,     2,     2,     5,     3,
       4,     5,     2,     1,     1,    10,     1,     3,     4,     3,
       3,     1,     3,     3,     7,     7,     0,     1,     3,     1,
       3,     1,     2,     1,     1,     1,     3,     0,     1,     2,
       2,     2,     2,     3,     4,     4,     2,     3,     1,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     2,     2,     1,     3,
       3,     4,     4,     1,     3,     1,     5,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     5,     5,     5,
       0
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
  case 4: /* stat: thislabel entry  */
#line 143 "build/gen/f77/gram.in"
                { lastwasbranch = NO; }
#line 2013 "build/gen/f77/y.tab.c"
    break;

  case 6: /* stat: thislabel exec  */
#line 146 "build/gen/f77/gram.in"
                { if(yyvsp[-1] && (yyvsp[-1]->labelno==dorange))
			enddo(yyvsp[-1]->labelno);
		  if(lastwasbranch && thislabel==NULL)
			warn1("statement cannot be reached");
		  lastwasbranch = thiswasbranch;
		  thiswasbranch = NO;
		}
#line 2025 "build/gen/f77/y.tab.c"
    break;

  case 7: /* stat: thislabel SINCLUDE filename  */
#line 154 "build/gen/f77/gram.in"
                { doinclude( yyvsp[0] ); }
#line 2031 "build/gen/f77/y.tab.c"
    break;

  case 8: /* stat: thislabel SEND end_spec  */
#line 156 "build/gen/f77/gram.in"
                { lastwasbranch = NO;  endproc(); }
#line 2037 "build/gen/f77/y.tab.c"
    break;

  case 9: /* stat: thislabel SUNKNOWN  */
#line 158 "build/gen/f77/gram.in"
                { execerr("unclassifiable statement", 0);  flline(); }
#line 2043 "build/gen/f77/y.tab.c"
    break;

  case 10: /* stat: error  */
#line 160 "build/gen/f77/gram.in"
                { flline();  needkwd = NO;  inioctl = NO; 
		  yyerrok; yyclearin; }
#line 2050 "build/gen/f77/y.tab.c"
    break;

  case 11: /* thislabel: SLABEL  */
#line 165 "build/gen/f77/gram.in"
                {
		if(yystno != 0)
			{
			yyval = thislabel =  mklabel(yystno);
			if( ! headerdone )
				puthead(NULL, procclass);
			if(thislabel->labdefined)
				execerr("label %s already defined",
					convic(thislabel->stateno) );
			else	{
				if(thislabel->blklevel!=0 && thislabel->blklevel<blklevel
				    && thislabel->labtype!=LABFORMAT)
					warn1("there is a branch to label %s from outside block",
					      convic( (ftnint) (thislabel->stateno) ) );
				thislabel->blklevel = blklevel;
				thislabel->labdefined = YES;
				if(thislabel->labtype != LABFORMAT)
					putlabel(thislabel->labelno);
				}
			}
		else    yyval = thislabel = NULL;
		}
#line 2077 "build/gen/f77/y.tab.c"
    break;

  case 12: /* entry: SPROGRAM new_proc progname  */
#line 190 "build/gen/f77/gram.in"
                { startproc(yyvsp[0], CLMAIN); }
#line 2083 "build/gen/f77/y.tab.c"
    break;

  case 13: /* entry: SBLOCK new_proc progname  */
#line 192 "build/gen/f77/gram.in"
                { startproc(yyvsp[0], CLBLOCK); }
#line 2089 "build/gen/f77/y.tab.c"
    break;

  case 14: /* entry: SSUBROUTINE new_proc entryname arglist  */
#line 194 "build/gen/f77/gram.in"
                { entrypt(CLPROC, TYSUBR, (ftnint) 0,  yyvsp[-1], yyvsp[0]); }
#line 2095 "build/gen/f77/y.tab.c"
    break;

  case 15: /* entry: SFUNCTION new_proc entryname arglist  */
#line 196 "build/gen/f77/gram.in"
                { entrypt(CLPROC, TYUNKNOWN, (ftnint) 0, yyvsp[-1], yyvsp[0]); }
#line 2101 "build/gen/f77/y.tab.c"
    break;

  case 16: /* entry: type SFUNCTION new_proc entryname arglist  */
#line 198 "build/gen/f77/gram.in"
                { entrypt(CLPROC, yyvsp[-4], varleng, yyvsp[-1], yyvsp[0]); }
#line 2107 "build/gen/f77/y.tab.c"
    break;

  case 17: /* entry: SENTRY entryname arglist  */
#line 200 "build/gen/f77/gram.in"
                { if(parstate==OUTSIDE || procclass==CLMAIN
			|| procclass==CLBLOCK)
				execerr("misplaced entry statement", 0);
		  entrypt(CLENTRY, 0, (ftnint) 0, yyvsp[-1], yyvsp[0]);
		}
#line 2117 "build/gen/f77/y.tab.c"
    break;

  case 18: /* new_proc: %empty  */
#line 208 "build/gen/f77/gram.in"
                { newproc(); }
#line 2123 "build/gen/f77/y.tab.c"
    break;

  case 19: /* entryname: name  */
#line 212 "build/gen/f77/gram.in"
                { yyval = newentry(yyvsp[0]); }
#line 2129 "build/gen/f77/y.tab.c"
    break;

  case 20: /* name: SNAME  */
#line 216 "build/gen/f77/gram.in"
                { yyval = mkname(toklen, token); }
#line 2135 "build/gen/f77/y.tab.c"
    break;

  case 21: /* progname: %empty  */
#line 219 "build/gen/f77/gram.in"
                        { yyval = NULL; }
#line 2141 "build/gen/f77/y.tab.c"
    break;

  case 23: /* arglist: %empty  */
#line 224 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2147 "build/gen/f77/y.tab.c"
    break;

  case 24: /* arglist: SLPAR SRPAR  */
#line 226 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2153 "build/gen/f77/y.tab.c"
    break;

  case 25: /* arglist: SLPAR args SRPAR  */
#line 228 "build/gen/f77/gram.in"
                {yyval = yyvsp[-1]; }
#line 2159 "build/gen/f77/y.tab.c"
    break;

  case 26: /* args: arg  */
#line 232 "build/gen/f77/gram.in"
                { yyval = (yyvsp[0] ? mkchain(yyvsp[0],0) : 0 ); }
#line 2165 "build/gen/f77/y.tab.c"
    break;

  case 27: /* args: args SCOMMA arg  */
#line 234 "build/gen/f77/gram.in"
                { if(yyvsp[0]) yyvsp[-2] = yyval = hookup(yyvsp[-2], mkchain(yyvsp[0],0)); }
#line 2171 "build/gen/f77/y.tab.c"
    break;

  case 28: /* arg: name  */
#line 238 "build/gen/f77/gram.in"
                { yyvsp[0]->vstg = STGARG; }
#line 2177 "build/gen/f77/y.tab.c"
    break;

  case 29: /* arg: SSTAR  */
#line 240 "build/gen/f77/gram.in"
                { yyval = 0;  substars = YES; }
#line 2183 "build/gen/f77/y.tab.c"
    break;

  case 30: /* filename: SHOLLERITH  */
#line 246 "build/gen/f77/gram.in"
                {
		char *s;
		s = copyn(toklen+1, token);
		s[toklen] = '\0';
		yyval = s;
		}
#line 2194 "build/gen/f77/y.tab.c"
    break;

  case 38: /* spec: SSAVE  */
#line 261 "build/gen/f77/gram.in"
                { saveall = YES; }
#line 2200 "build/gen/f77/y.tab.c"
    break;

  case 40: /* spec: SFORMAT  */
#line 264 "build/gen/f77/gram.in"
                { fmtstmt(thislabel); setfmt(thislabel); }
#line 2206 "build/gen/f77/y.tab.c"
    break;

  case 42: /* dcl: type name in_dcl lengspec dims  */
#line 269 "build/gen/f77/gram.in"
                { settype(yyvsp[-3], yyvsp[-4], yyvsp[-1]);
		  if(ndim>0) setbound(yyvsp[-3],ndim,dims);
		}
#line 2214 "build/gen/f77/y.tab.c"
    break;

  case 43: /* dcl: dcl SCOMMA name lengspec dims  */
#line 273 "build/gen/f77/gram.in"
                { settype(yyvsp[-2], yyvsp[-4], yyvsp[-1]);
		  if(ndim>0) setbound(yyvsp[-2],ndim,dims);
		}
#line 2222 "build/gen/f77/y.tab.c"
    break;

  case 44: /* type: typespec lengspec  */
#line 279 "build/gen/f77/gram.in"
                { varleng = yyvsp[0]; }
#line 2228 "build/gen/f77/y.tab.c"
    break;

  case 45: /* typespec: typename  */
#line 283 "build/gen/f77/gram.in"
                { varleng = (yyvsp[0]<0 || yyvsp[0]==TYLONG ? 0 : typesize[(ftnint)yyvsp[0]]); }
#line 2234 "build/gen/f77/y.tab.c"
    break;

  case 46: /* typename: SINTEGER  */
#line 286 "build/gen/f77/gram.in"
                        { yyval = TYLONG; }
#line 2240 "build/gen/f77/y.tab.c"
    break;

  case 47: /* typename: SREAL  */
#line 287 "build/gen/f77/gram.in"
                        { yyval = TYREAL; }
#line 2246 "build/gen/f77/y.tab.c"
    break;

  case 48: /* typename: SCOMPLEX  */
#line 288 "build/gen/f77/gram.in"
                        { yyval = TYCOMPLEX; }
#line 2252 "build/gen/f77/y.tab.c"
    break;

  case 49: /* typename: SDOUBLE  */
#line 289 "build/gen/f77/gram.in"
                        { yyval = TYDREAL; }
#line 2258 "build/gen/f77/y.tab.c"
    break;

  case 50: /* typename: SDCOMPLEX  */
#line 290 "build/gen/f77/gram.in"
                        { yyval = TYDCOMPLEX; }
#line 2264 "build/gen/f77/y.tab.c"
    break;

  case 51: /* typename: SLOGICAL  */
#line 291 "build/gen/f77/gram.in"
                        { yyval = TYLOGICAL; }
#line 2270 "build/gen/f77/y.tab.c"
    break;

  case 52: /* typename: SCHARACTER  */
#line 292 "build/gen/f77/gram.in"
                        { yyval = TYCHAR; }
#line 2276 "build/gen/f77/y.tab.c"
    break;

  case 53: /* typename: SUNDEFINED  */
#line 293 "build/gen/f77/gram.in"
                        { yyval = TYUNKNOWN; }
#line 2282 "build/gen/f77/y.tab.c"
    break;

  case 54: /* typename: SDIMENSION  */
#line 294 "build/gen/f77/gram.in"
                        { yyval = TYUNKNOWN; }
#line 2288 "build/gen/f77/y.tab.c"
    break;

  case 55: /* typename: SAUTOMATIC  */
#line 295 "build/gen/f77/gram.in"
                        { yyval = - STGAUTO; }
#line 2294 "build/gen/f77/y.tab.c"
    break;

  case 56: /* typename: SSTATIC  */
#line 296 "build/gen/f77/gram.in"
                        { yyval = - STGBSS; }
#line 2300 "build/gen/f77/y.tab.c"
    break;

  case 57: /* lengspec: %empty  */
#line 300 "build/gen/f77/gram.in"
                { yyval = varleng; }
#line 2306 "build/gen/f77/y.tab.c"
    break;

  case 58: /* lengspec: SSTAR expr  */
#line 302 "build/gen/f77/gram.in"
                {
		  if( ! ISICON(yyvsp[0]) )
			{
			yyval = 0;
			dclerr("length must be an integer constant", 0);
			}
		  else yyval = yyvsp[0]->konst.ci;
		}
#line 2319 "build/gen/f77/y.tab.c"
    break;

  case 59: /* lengspec: SSTAR SLPAR SSTAR SRPAR  */
#line 311 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2325 "build/gen/f77/y.tab.c"
    break;

  case 60: /* common: SCOMMON in_dcl var  */
#line 315 "build/gen/f77/gram.in"
                { incomm( yyval = comblock(0, 0) , yyvsp[0] ); }
#line 2331 "build/gen/f77/y.tab.c"
    break;

  case 61: /* common: SCOMMON in_dcl comblock var  */
#line 317 "build/gen/f77/gram.in"
                { yyval = yyvsp[-1];  incomm(yyvsp[-1], yyvsp[0]); }
#line 2337 "build/gen/f77/y.tab.c"
    break;

  case 62: /* common: common opt_comma comblock opt_comma var  */
#line 319 "build/gen/f77/gram.in"
                { yyval = yyvsp[-2];  incomm(yyvsp[-2], yyvsp[0]); }
#line 2343 "build/gen/f77/y.tab.c"
    break;

  case 63: /* common: common SCOMMA var  */
#line 321 "build/gen/f77/gram.in"
                { incomm(yyvsp[-2], yyvsp[0]); }
#line 2349 "build/gen/f77/y.tab.c"
    break;

  case 64: /* comblock: SCONCAT  */
#line 325 "build/gen/f77/gram.in"
                { yyval = comblock(0, 0); }
#line 2355 "build/gen/f77/y.tab.c"
    break;

  case 65: /* comblock: SSLASH SNAME SSLASH  */
#line 327 "build/gen/f77/gram.in"
                { yyval = comblock(toklen, token); }
#line 2361 "build/gen/f77/y.tab.c"
    break;

  case 66: /* external: SEXTERNAL in_dcl name  */
#line 331 "build/gen/f77/gram.in"
                { setext(yyvsp[0]); }
#line 2367 "build/gen/f77/y.tab.c"
    break;

  case 67: /* external: external SCOMMA name  */
#line 333 "build/gen/f77/gram.in"
                { setext(yyvsp[0]); }
#line 2373 "build/gen/f77/y.tab.c"
    break;

  case 68: /* intrinsic: SINTRINSIC in_dcl name  */
#line 337 "build/gen/f77/gram.in"
                { setintr(yyvsp[0]); }
#line 2379 "build/gen/f77/y.tab.c"
    break;

  case 69: /* intrinsic: intrinsic SCOMMA name  */
#line 339 "build/gen/f77/gram.in"
                { setintr(yyvsp[0]); }
#line 2385 "build/gen/f77/y.tab.c"
    break;

  case 72: /* equivset: SLPAR equivlist SRPAR  */
#line 347 "build/gen/f77/gram.in"
                {
		struct equivblock *p;
		if(nequiv >= MAXEQUIV)
			fatal("too many equivalences");
		p  =  & eqvclass[nequiv++];
		p->eqvinit = 0;
		p->eqvbottom = 0;
		p->eqvtop = 0;
		p->equivs = yyvsp[-1];
		}
#line 2400 "build/gen/f77/y.tab.c"
    break;

  case 73: /* equivlist: lhs  */
#line 360 "build/gen/f77/gram.in"
                { yyval = ALLOC(eqvchain); yyval->eqvitem = yyvsp[0]; }
#line 2406 "build/gen/f77/y.tab.c"
    break;

  case 74: /* equivlist: equivlist SCOMMA lhs  */
#line 362 "build/gen/f77/gram.in"
                { yyval = ALLOC(eqvchain); yyval->eqvitem = yyvsp[0]; yyval->nextp = yyvsp[-2]; }
#line 2412 "build/gen/f77/y.tab.c"
    break;

  case 77: /* in_data: %empty  */
#line 370 "build/gen/f77/gram.in"
                { if(parstate == OUTSIDE)
			{
			newproc();
			startproc(0, CLMAIN);
			}
		  if(parstate < INDATA)
			{
			enddcl();
			parstate = INDATA;
			}
		}
#line 2428 "build/gen/f77/y.tab.c"
    break;

  case 78: /* datalist: datavarlist SSLASH vallist SSLASH  */
#line 384 "build/gen/f77/gram.in"
                { ftnint junk;
		  if(nextdata(&junk,&junk) != NULL)
			{
			err("too few initializers");
			curdtp = NULL;
			}
		  frdata(yyvsp[-3]);
		  frrpl();
		}
#line 2442 "build/gen/f77/y.tab.c"
    break;

  case 79: /* $@1: %empty  */
#line 395 "build/gen/f77/gram.in"
          { toomanyinit = NO; }
#line 2448 "build/gen/f77/y.tab.c"
    break;

  case 82: /* val: value  */
#line 400 "build/gen/f77/gram.in"
                { dataval(NULL, yyvsp[0]); }
#line 2454 "build/gen/f77/y.tab.c"
    break;

  case 83: /* val: simple SSTAR value  */
#line 402 "build/gen/f77/gram.in"
                { dataval(yyvsp[-2], yyvsp[0]); }
#line 2460 "build/gen/f77/y.tab.c"
    break;

  case 85: /* value: addop simple  */
#line 407 "build/gen/f77/gram.in"
                { if( yyvsp[-1]==OPMINUS && ISCONST(yyvsp[0]) )
			consnegop(yyvsp[0]);
		  yyval = yyvsp[0];
		}
#line 2469 "build/gen/f77/y.tab.c"
    break;

  case 90: /* saveitem: name  */
#line 420 "build/gen/f77/gram.in"
                { int k;
		  yyvsp[0]->vsave = 1;
		  k = yyvsp[0]->vstg;
		if( ! ONEOF(k, M(STGUNKNOWN)|M(STGBSS)|M(STGINIT)) )
			dclerr("can only save static variables", yyvsp[0]);
		}
#line 2480 "build/gen/f77/y.tab.c"
    break;

  case 91: /* saveitem: comblock  */
#line 427 "build/gen/f77/gram.in"
                { yyvsp[0]->extsave = 1; }
#line 2486 "build/gen/f77/y.tab.c"
    break;

  case 94: /* paramitem: name SEQUALS expr  */
#line 435 "build/gen/f77/gram.in"
                { if(yyvsp[-2]->vclass == CLUNKNOWN)
			{ yyvsp[-2]->vclass = CLPARAM;
			  yyvsp[-2]->paramval = yyvsp[0];
			}
		  else dclerr("cannot make %s parameter", yyvsp[-2]);
		}
#line 2497 "build/gen/f77/y.tab.c"
    break;

  case 95: /* var: name dims  */
#line 444 "build/gen/f77/gram.in"
                { if(ndim>0) setbounds(yyvsp[-1], ndim, dims); }
#line 2503 "build/gen/f77/y.tab.c"
    break;

  case 96: /* datavar: lhs  */
#line 448 "build/gen/f77/gram.in"
                { struct nameblock *np;
		  vardcl(np = yyvsp[0]->namep);
		  if(np->vstg == STGBSS)
			np->vstg = STGINIT;
		  else if(np->vstg == STGCOMMON)
			extsymtab[np->vardesc.varno].extinit = YES;
		  else if(np->vstg==STGEQUIV)
			eqvclass[np->vardesc.varno].eqvinit = YES;
		  else if(np->vstg != STGINIT)
			dclerr("inconsistent storage classes", np);
		  yyval = mkchain(yyvsp[0], 0);
		}
#line 2520 "build/gen/f77/y.tab.c"
    break;

  case 97: /* datavar: SLPAR datavarlist SCOMMA dospec SRPAR  */
#line 461 "build/gen/f77/gram.in"
                { chainp p; struct impldoblock *q;
		q = ALLOC(impldoblock);
		q->tag = TIMPLDO;
		q->varnp = yyvsp[-1]->datap;
		p = yyvsp[-1]->nextp;
		if(p)  { q->implb = p->datap; p = p->nextp; }
		if(p)  { q->impub = p->datap; p = p->nextp; }
		if(p)  { q->impstep = p->datap; p = p->nextp; }
		frchain( & (yyvsp[-1]) );
		yyval = mkchain(q, 0);
		q->datalist = hookup(yyvsp[-3], yyval);
		}
#line 2537 "build/gen/f77/y.tab.c"
    break;

  case 98: /* datavarlist: datavar  */
#line 476 "build/gen/f77/gram.in"
                { curdtp = yyvsp[0]; curdtelt = 0; }
#line 2543 "build/gen/f77/y.tab.c"
    break;

  case 99: /* datavarlist: datavarlist SCOMMA datavar  */
#line 478 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], yyvsp[0]); }
#line 2549 "build/gen/f77/y.tab.c"
    break;

  case 100: /* dims: %empty  */
#line 482 "build/gen/f77/gram.in"
                { ndim = 0; }
#line 2555 "build/gen/f77/y.tab.c"
    break;

  case 102: /* $@2: %empty  */
#line 486 "build/gen/f77/gram.in"
           { ndim = 0; }
#line 2561 "build/gen/f77/y.tab.c"
    break;

  case 105: /* dim: ubound  */
#line 491 "build/gen/f77/gram.in"
                { dims[ndim].lb = 0;
		  dims[ndim].ub = yyvsp[0];
		  ++ndim;
		}
#line 2570 "build/gen/f77/y.tab.c"
    break;

  case 106: /* dim: expr SCOLON ubound  */
#line 496 "build/gen/f77/gram.in"
                { dims[ndim].lb = yyvsp[-2];
		  dims[ndim].ub = yyvsp[0];
		  ++ndim;
		}
#line 2579 "build/gen/f77/y.tab.c"
    break;

  case 107: /* ubound: SSTAR  */
#line 503 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2585 "build/gen/f77/y.tab.c"
    break;

  case 109: /* labellist: label  */
#line 508 "build/gen/f77/gram.in"
                { nstars = 1; labarray[0] = yyvsp[0]; }
#line 2591 "build/gen/f77/y.tab.c"
    break;

  case 110: /* labellist: labellist SCOMMA label  */
#line 510 "build/gen/f77/gram.in"
                { if(nstars < MAXLABLIST)  labarray[nstars++] = yyvsp[0]; }
#line 2597 "build/gen/f77/y.tab.c"
    break;

  case 111: /* label: labelval  */
#line 514 "build/gen/f77/gram.in"
                { if(yyvsp[0]->labinacc)
			warn1("illegal branch to inner block, statement %s",
				convic( (ftnint) (yyvsp[0]->stateno) ));
		  else if(yyvsp[0]->labdefined == NO)
			yyvsp[0]->blklevel = blklevel;
		  yyvsp[0]->labused = YES;
		}
#line 2609 "build/gen/f77/y.tab.c"
    break;

  case 112: /* labelval: SICON  */
#line 524 "build/gen/f77/gram.in"
                { yyval = mklabel( convci(toklen, token) ); }
#line 2615 "build/gen/f77/y.tab.c"
    break;

  case 116: /* $@3: %empty  */
#line 534 "build/gen/f77/gram.in"
           { needkwd = 1; }
#line 2621 "build/gen/f77/y.tab.c"
    break;

  case 117: /* imptype: $@3 type  */
#line 535 "build/gen/f77/gram.in"
                { vartype = yyvsp[0]; }
#line 2627 "build/gen/f77/y.tab.c"
    break;

  case 120: /* letgroup: letter  */
#line 543 "build/gen/f77/gram.in"
                { setimpl(vartype, varleng, yyvsp[0], yyvsp[0]); }
#line 2633 "build/gen/f77/y.tab.c"
    break;

  case 121: /* letgroup: letter SMINUS letter  */
#line 545 "build/gen/f77/gram.in"
                { setimpl(vartype, varleng, yyvsp[-2], yyvsp[0]); }
#line 2639 "build/gen/f77/y.tab.c"
    break;

  case 122: /* letter: SNAME  */
#line 549 "build/gen/f77/gram.in"
                { if(toklen!=1 || token[0]<'a' || token[0]>'z')
			{
			dclerr("implicit item must be single letter", 0);
			yyval = 0;
			}
		  else yyval = token[0];
		}
#line 2651 "build/gen/f77/y.tab.c"
    break;

  case 123: /* in_dcl: %empty  */
#line 559 "build/gen/f77/gram.in"
                { switch(parstate)	
			{
			case OUTSIDE:	newproc();
					startproc(0, CLMAIN);
			case INSIDE:	parstate = INDCL;
			case INDCL:	break;

			default:
				dclerr("declaration among executables", 0);
			}
		}
#line 2667 "build/gen/f77/y.tab.c"
    break;

  case 124: /* funarglist: %empty  */
#line 572 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2673 "build/gen/f77/y.tab.c"
    break;

  case 126: /* funargs: expr  */
#line 577 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[0], 0); }
#line 2679 "build/gen/f77/y.tab.c"
    break;

  case 127: /* funargs: funargs SCOMMA expr  */
#line 579 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], mkchain(yyvsp[0],0) ); }
#line 2685 "build/gen/f77/y.tab.c"
    break;

  case 129: /* expr: SLPAR expr SRPAR  */
#line 584 "build/gen/f77/gram.in"
                                { yyval = yyvsp[-1]; }
#line 2691 "build/gen/f77/y.tab.c"
    break;

  case 133: /* uexpr: expr addop expr  */
#line 591 "build/gen/f77/gram.in"
                { yyval = mkexpr(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2697 "build/gen/f77/y.tab.c"
    break;

  case 134: /* uexpr: expr SSTAR expr  */
#line 593 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPSTAR, yyvsp[-2], yyvsp[0]); }
#line 2703 "build/gen/f77/y.tab.c"
    break;

  case 135: /* uexpr: expr SSLASH expr  */
#line 595 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPSLASH, yyvsp[-2], yyvsp[0]); }
#line 2709 "build/gen/f77/y.tab.c"
    break;

  case 136: /* uexpr: expr SPOWER expr  */
#line 597 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPPOWER, yyvsp[-2], yyvsp[0]); }
#line 2715 "build/gen/f77/y.tab.c"
    break;

  case 137: /* uexpr: addop expr  */
#line 599 "build/gen/f77/gram.in"
                { if(yyvsp[-1] == OPMINUS)
			yyval = mkexpr(OPNEG, yyvsp[0], 0);
		  else 	yyval = yyvsp[0];
		}
#line 2724 "build/gen/f77/y.tab.c"
    break;

  case 138: /* uexpr: expr relop expr  */
#line 604 "build/gen/f77/gram.in"
                { yyval = mkexpr(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2730 "build/gen/f77/y.tab.c"
    break;

  case 139: /* uexpr: expr SEQV expr  */
#line 606 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPEQV, yyvsp[-2],yyvsp[0]); }
#line 2736 "build/gen/f77/y.tab.c"
    break;

  case 140: /* uexpr: expr SNEQV expr  */
#line 608 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPNEQV, yyvsp[-2], yyvsp[0]); }
#line 2742 "build/gen/f77/y.tab.c"
    break;

  case 141: /* uexpr: expr SOR expr  */
#line 610 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPOR, yyvsp[-2], yyvsp[0]); }
#line 2748 "build/gen/f77/y.tab.c"
    break;

  case 142: /* uexpr: expr SAND expr  */
#line 612 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPAND, yyvsp[-2], yyvsp[0]); }
#line 2754 "build/gen/f77/y.tab.c"
    break;

  case 143: /* uexpr: SNOT expr  */
#line 614 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPNOT, yyvsp[0], 0); }
#line 2760 "build/gen/f77/y.tab.c"
    break;

  case 144: /* uexpr: expr SCONCAT expr  */
#line 616 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPCONCAT, yyvsp[-2], yyvsp[0]); }
#line 2766 "build/gen/f77/y.tab.c"
    break;

  case 145: /* addop: SPLUS  */
#line 619 "build/gen/f77/gram.in"
                        { yyval = OPPLUS; }
#line 2772 "build/gen/f77/y.tab.c"
    break;

  case 146: /* addop: SMINUS  */
#line 620 "build/gen/f77/gram.in"
                        { yyval = OPMINUS; }
#line 2778 "build/gen/f77/y.tab.c"
    break;

  case 147: /* relop: SEQ  */
#line 623 "build/gen/f77/gram.in"
                { yyval = OPEQ; }
#line 2784 "build/gen/f77/y.tab.c"
    break;

  case 148: /* relop: SGT  */
#line 624 "build/gen/f77/gram.in"
                { yyval = OPGT; }
#line 2790 "build/gen/f77/y.tab.c"
    break;

  case 149: /* relop: SLT  */
#line 625 "build/gen/f77/gram.in"
                { yyval = OPLT; }
#line 2796 "build/gen/f77/y.tab.c"
    break;

  case 150: /* relop: SGE  */
#line 626 "build/gen/f77/gram.in"
                { yyval = OPGE; }
#line 2802 "build/gen/f77/y.tab.c"
    break;

  case 151: /* relop: SLE  */
#line 627 "build/gen/f77/gram.in"
                { yyval = OPLE; }
#line 2808 "build/gen/f77/y.tab.c"
    break;

  case 152: /* relop: SNE  */
#line 628 "build/gen/f77/gram.in"
                { yyval = OPNE; }
#line 2814 "build/gen/f77/y.tab.c"
    break;

  case 153: /* lhs: name  */
#line 632 "build/gen/f77/gram.in"
                { yyval = mkprim(yyvsp[0], 0, 0, 0); }
#line 2820 "build/gen/f77/y.tab.c"
    break;

  case 154: /* lhs: name SLPAR opt_expr SCOLON opt_expr SRPAR  */
#line 634 "build/gen/f77/gram.in"
                { yyval = mkprim(yyvsp[-5], 0, yyvsp[-3], yyvsp[-1]); }
#line 2826 "build/gen/f77/y.tab.c"
    break;

  case 155: /* lhs: name SLPAR funarglist SRPAR  */
#line 636 "build/gen/f77/gram.in"
                { yyval = mkprim(yyvsp[-3], mklist(yyvsp[-1]), 0, 0); }
#line 2832 "build/gen/f77/y.tab.c"
    break;

  case 156: /* lhs: name SLPAR funarglist SRPAR SLPAR opt_expr SCOLON opt_expr SRPAR  */
#line 638 "build/gen/f77/gram.in"
                { yyval = mkprim(yyvsp[-8], mklist(yyvsp[-6]), yyvsp[-3], yyvsp[-1]); }
#line 2838 "build/gen/f77/y.tab.c"
    break;

  case 157: /* opt_expr: %empty  */
#line 642 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 2844 "build/gen/f77/y.tab.c"
    break;

  case 159: /* simple: name  */
#line 647 "build/gen/f77/gram.in"
                { if(yyvsp[0]->vclass == CLPARAM)
			yyval = cpexpr(yyvsp[0]->paramval);
		}
#line 2852 "build/gen/f77/y.tab.c"
    break;

  case 161: /* simple_const: STRUE  */
#line 653 "build/gen/f77/gram.in"
                        { yyval = mklogcon(1); }
#line 2858 "build/gen/f77/y.tab.c"
    break;

  case 162: /* simple_const: SFALSE  */
#line 654 "build/gen/f77/gram.in"
                        { yyval = mklogcon(0); }
#line 2864 "build/gen/f77/y.tab.c"
    break;

  case 163: /* simple_const: SHOLLERITH  */
#line 655 "build/gen/f77/gram.in"
                      { yyval = mkstrcon(toklen, token); }
#line 2870 "build/gen/f77/y.tab.c"
    break;

  case 164: /* simple_const: SICON  */
#line 656 "build/gen/f77/gram.in"
                { yyval = mkintcon( convci(toklen, token) ); }
#line 2876 "build/gen/f77/y.tab.c"
    break;

  case 165: /* simple_const: SRCON  */
#line 657 "build/gen/f77/gram.in"
                { yyval = mkrealcon(TYREAL, convcd(toklen, token)); }
#line 2882 "build/gen/f77/y.tab.c"
    break;

  case 166: /* simple_const: SDCON  */
#line 658 "build/gen/f77/gram.in"
                { yyval = mkrealcon(TYDREAL, convcd(toklen, token)); }
#line 2888 "build/gen/f77/y.tab.c"
    break;

  case 167: /* complex_const: SLPAR uexpr SCOMMA uexpr SRPAR  */
#line 662 "build/gen/f77/gram.in"
                { yyval = mkcxcon(yyvsp[-3],yyvsp[-1]); }
#line 2894 "build/gen/f77/y.tab.c"
    break;

  case 168: /* bit_const: SHEXCON  */
#line 666 "build/gen/f77/gram.in"
                { yyval = mkbitcon(4, toklen, token); }
#line 2900 "build/gen/f77/y.tab.c"
    break;

  case 169: /* bit_const: SOCTCON  */
#line 668 "build/gen/f77/gram.in"
                { yyval = mkbitcon(3, toklen, token); }
#line 2906 "build/gen/f77/y.tab.c"
    break;

  case 170: /* bit_const: SBITCON  */
#line 670 "build/gen/f77/gram.in"
                { yyval = mkbitcon(1, toklen, token); }
#line 2912 "build/gen/f77/y.tab.c"
    break;

  case 172: /* fexpr: SLPAR fexpr SRPAR  */
#line 675 "build/gen/f77/gram.in"
                { yyval = yyvsp[-1]; }
#line 2918 "build/gen/f77/y.tab.c"
    break;

  case 175: /* unpar_fexpr: fexpr addop fexpr  */
#line 681 "build/gen/f77/gram.in"
                { yyval = mkexpr(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 2924 "build/gen/f77/y.tab.c"
    break;

  case 176: /* unpar_fexpr: fexpr SSTAR fexpr  */
#line 683 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPSTAR, yyvsp[-2], yyvsp[0]); }
#line 2930 "build/gen/f77/y.tab.c"
    break;

  case 177: /* unpar_fexpr: fexpr SSLASH fexpr  */
#line 685 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPSLASH, yyvsp[-2], yyvsp[0]); }
#line 2936 "build/gen/f77/y.tab.c"
    break;

  case 178: /* unpar_fexpr: fexpr SPOWER fexpr  */
#line 687 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPPOWER, yyvsp[-2], yyvsp[0]); }
#line 2942 "build/gen/f77/y.tab.c"
    break;

  case 179: /* unpar_fexpr: addop fexpr  */
#line 689 "build/gen/f77/gram.in"
                { if(yyvsp[-1] == OPMINUS)
			yyval = mkexpr(OPNEG, yyvsp[0], 0);
		  else	yyval = yyvsp[0];
		}
#line 2951 "build/gen/f77/y.tab.c"
    break;

  case 180: /* unpar_fexpr: fexpr SCONCAT fexpr  */
#line 694 "build/gen/f77/gram.in"
                { yyval = mkexpr(OPCONCAT, yyvsp[-2], yyvsp[0]); }
#line 2957 "build/gen/f77/y.tab.c"
    break;

  case 182: /* exec: SDO end_spec label dospec  */
#line 698 "build/gen/f77/gram.in"
                {
		if(yyvsp[-1]->labdefined)
			execerr("no backward DO loops");
		yyvsp[-1]->blklevel = blklevel+1;
		exdo(yyvsp[-1]->labelno, yyvsp[0]);
		}
#line 2968 "build/gen/f77/y.tab.c"
    break;

  case 183: /* exec: logif iffable  */
#line 705 "build/gen/f77/gram.in"
                { exendif();  thiswasbranch = NO; }
#line 2974 "build/gen/f77/y.tab.c"
    break;

  case 185: /* exec: SELSEIF end_spec SLPAR expr SRPAR STHEN  */
#line 708 "build/gen/f77/gram.in"
                { exelif(yyvsp[-2]); }
#line 2980 "build/gen/f77/y.tab.c"
    break;

  case 186: /* exec: SELSE end_spec  */
#line 710 "build/gen/f77/gram.in"
                { exelse(); }
#line 2986 "build/gen/f77/y.tab.c"
    break;

  case 187: /* exec: SENDIF end_spec  */
#line 712 "build/gen/f77/gram.in"
                { exendif(); }
#line 2992 "build/gen/f77/y.tab.c"
    break;

  case 188: /* logif: SLOGIF end_spec SLPAR expr SRPAR  */
#line 716 "build/gen/f77/gram.in"
                { exif(yyvsp[-1]); }
#line 2998 "build/gen/f77/y.tab.c"
    break;

  case 189: /* dospec: name SEQUALS exprlist  */
#line 720 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[-2], yyvsp[0]); }
#line 3004 "build/gen/f77/y.tab.c"
    break;

  case 190: /* iffable: let lhs SEQUALS expr  */
#line 724 "build/gen/f77/gram.in"
                { exequals(yyvsp[-2], yyvsp[0]); }
#line 3010 "build/gen/f77/y.tab.c"
    break;

  case 191: /* iffable: SASSIGN end_spec labelval STO name  */
#line 726 "build/gen/f77/gram.in"
                { exassign(yyvsp[0], yyvsp[-2]); }
#line 3016 "build/gen/f77/y.tab.c"
    break;

  case 194: /* iffable: io  */
#line 730 "build/gen/f77/gram.in"
                { inioctl = NO; }
#line 3022 "build/gen/f77/y.tab.c"
    break;

  case 195: /* iffable: SARITHIF end_spec SLPAR expr SRPAR label SCOMMA label SCOMMA label  */
#line 732 "build/gen/f77/gram.in"
                { exarif(yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]);  thiswasbranch = YES; }
#line 3028 "build/gen/f77/y.tab.c"
    break;

  case 196: /* iffable: call  */
#line 734 "build/gen/f77/gram.in"
                { excall(yyvsp[0], 0, 0, labarray); }
#line 3034 "build/gen/f77/y.tab.c"
    break;

  case 197: /* iffable: call SLPAR SRPAR  */
#line 736 "build/gen/f77/gram.in"
                { excall(yyvsp[-2], 0, 0, labarray); }
#line 3040 "build/gen/f77/y.tab.c"
    break;

  case 198: /* iffable: call SLPAR callarglist SRPAR  */
#line 738 "build/gen/f77/gram.in"
                { if(nstars < MAXLABLIST)
			excall(yyvsp[-3], mklist(yyvsp[-1]), nstars, labarray);
		  else
			err("too many alternate returns");
		}
#line 3050 "build/gen/f77/y.tab.c"
    break;

  case 199: /* iffable: SRETURN end_spec opt_expr  */
#line 744 "build/gen/f77/gram.in"
                { exreturn(yyvsp[0]);  thiswasbranch = YES; }
#line 3056 "build/gen/f77/y.tab.c"
    break;

  case 200: /* iffable: stop end_spec opt_expr  */
#line 746 "build/gen/f77/gram.in"
                { exstop(yyvsp[-2], yyvsp[0]);  thiswasbranch = yyvsp[-2]; }
#line 3062 "build/gen/f77/y.tab.c"
    break;

  case 201: /* let: SLET  */
#line 750 "build/gen/f77/gram.in"
                { if(parstate == OUTSIDE)
			{
			newproc();
			startproc(0, CLMAIN);
			}
		}
#line 3073 "build/gen/f77/y.tab.c"
    break;

  case 202: /* goto: SGOTO end_spec label  */
#line 759 "build/gen/f77/gram.in"
                { exgoto(yyvsp[0]);  thiswasbranch = YES; }
#line 3079 "build/gen/f77/y.tab.c"
    break;

  case 203: /* goto: SASGOTO end_spec name  */
#line 761 "build/gen/f77/gram.in"
                { exasgoto(yyvsp[0]);  thiswasbranch = YES; }
#line 3085 "build/gen/f77/y.tab.c"
    break;

  case 204: /* goto: SASGOTO end_spec name opt_comma SLPAR labellist SRPAR  */
#line 763 "build/gen/f77/gram.in"
                { exasgoto(yyvsp[-4]);  thiswasbranch = YES; }
#line 3091 "build/gen/f77/y.tab.c"
    break;

  case 205: /* goto: SCOMPGOTO end_spec SLPAR labellist SRPAR opt_comma expr  */
#line 765 "build/gen/f77/gram.in"
                { if(nstars < MAXLABLIST)
			putcmgo(fixtype(yyvsp[0]), nstars, labarray);
		  else
			err("computed GOTO list too long");
		}
#line 3101 "build/gen/f77/y.tab.c"
    break;

  case 208: /* call: SCALL end_spec name  */
#line 777 "build/gen/f77/gram.in"
                { nstars = 0; yyval = yyvsp[0]; }
#line 3107 "build/gen/f77/y.tab.c"
    break;

  case 209: /* callarglist: callarg  */
#line 781 "build/gen/f77/gram.in"
                { yyval = (yyvsp[0] ? mkchain(yyvsp[0],0) : 0); }
#line 3113 "build/gen/f77/y.tab.c"
    break;

  case 210: /* callarglist: callarglist SCOMMA callarg  */
#line 783 "build/gen/f77/gram.in"
                { if(yyvsp[0])
			if(yyvsp[-2]) yyval = hookup(yyvsp[-2], mkchain(yyvsp[0],0));
			else yyval = mkchain(yyvsp[0],0);
		}
#line 3122 "build/gen/f77/y.tab.c"
    break;

  case 212: /* callarg: SSTAR label  */
#line 791 "build/gen/f77/gram.in"
                { if(nstars<MAXLABLIST) labarray[nstars++] = yyvsp[0]; yyval = 0; }
#line 3128 "build/gen/f77/y.tab.c"
    break;

  case 213: /* stop: SPAUSE  */
#line 795 "build/gen/f77/gram.in"
                { yyval = 0; }
#line 3134 "build/gen/f77/y.tab.c"
    break;

  case 214: /* stop: SSTOP  */
#line 797 "build/gen/f77/gram.in"
                { yyval = 1; }
#line 3140 "build/gen/f77/y.tab.c"
    break;

  case 215: /* exprlist: expr  */
#line 801 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[0], 0); }
#line 3146 "build/gen/f77/y.tab.c"
    break;

  case 216: /* exprlist: exprlist SCOMMA expr  */
#line 803 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], mkchain(yyvsp[0],0) ); }
#line 3152 "build/gen/f77/y.tab.c"
    break;

  case 217: /* end_spec: %empty  */
#line 807 "build/gen/f77/gram.in"
                { if(parstate == OUTSIDE)
			{
			newproc();
			startproc(0, CLMAIN);
			}
		  if(parstate < INDATA) enddcl();
		}
#line 3164 "build/gen/f77/y.tab.c"
    break;

  case 218: /* io: io1  */
#line 818 "build/gen/f77/gram.in"
                { endio(); }
#line 3170 "build/gen/f77/y.tab.c"
    break;

  case 220: /* io1: iofmove unpar_fexpr  */
#line 823 "build/gen/f77/gram.in"
                { ioclause(IOSUNIT, yyvsp[0]); endioctl(); }
#line 3176 "build/gen/f77/y.tab.c"
    break;

  case 222: /* io1: read ioctl  */
#line 826 "build/gen/f77/gram.in"
                { doio(NULL); }
#line 3182 "build/gen/f77/y.tab.c"
    break;

  case 223: /* io1: read ioctl inlist  */
#line 828 "build/gen/f77/gram.in"
                { doio(yyvsp[0]); }
#line 3188 "build/gen/f77/y.tab.c"
    break;

  case 224: /* io1: read infmt SCOMMA inlist  */
#line 830 "build/gen/f77/gram.in"
                { doio(yyvsp[0]); }
#line 3194 "build/gen/f77/y.tab.c"
    break;

  case 225: /* io1: read ioctl SCOMMA inlist  */
#line 832 "build/gen/f77/gram.in"
                { doio(yyvsp[0]); }
#line 3200 "build/gen/f77/y.tab.c"
    break;

  case 226: /* io1: write ioctl  */
#line 834 "build/gen/f77/gram.in"
                { doio(NULL); }
#line 3206 "build/gen/f77/y.tab.c"
    break;

  case 227: /* io1: write ioctl outlist  */
#line 836 "build/gen/f77/gram.in"
                { doio(yyvsp[0]); }
#line 3212 "build/gen/f77/y.tab.c"
    break;

  case 228: /* io1: print  */
#line 838 "build/gen/f77/gram.in"
                { doio(NULL); }
#line 3218 "build/gen/f77/y.tab.c"
    break;

  case 229: /* io1: print SCOMMA outlist  */
#line 840 "build/gen/f77/gram.in"
                { doio(yyvsp[0]); }
#line 3224 "build/gen/f77/y.tab.c"
    break;

  case 231: /* fmkwd: SBACKSPACE  */
#line 847 "build/gen/f77/gram.in"
                { iostmt = IOREWIND; }
#line 3230 "build/gen/f77/y.tab.c"
    break;

  case 232: /* fmkwd: SREWIND  */
#line 849 "build/gen/f77/gram.in"
                { iostmt = IOREWIND; }
#line 3236 "build/gen/f77/y.tab.c"
    break;

  case 233: /* fmkwd: SENDFILE  */
#line 851 "build/gen/f77/gram.in"
                { iostmt = IOENDFILE; }
#line 3242 "build/gen/f77/y.tab.c"
    break;

  case 235: /* ctlkwd: SINQUIRE  */
#line 858 "build/gen/f77/gram.in"
                { iostmt = IOINQUIRE; }
#line 3248 "build/gen/f77/y.tab.c"
    break;

  case 236: /* ctlkwd: SOPEN  */
#line 860 "build/gen/f77/gram.in"
                { iostmt = IOOPEN; }
#line 3254 "build/gen/f77/y.tab.c"
    break;

  case 237: /* ctlkwd: SCLOSE  */
#line 862 "build/gen/f77/gram.in"
                { iostmt = IOCLOSE; }
#line 3260 "build/gen/f77/y.tab.c"
    break;

  case 238: /* infmt: unpar_fexpr  */
#line 866 "build/gen/f77/gram.in"
                {
		ioclause(IOSUNIT, NULL);
		ioclause(IOSFMT, yyvsp[0]);
		endioctl();
		}
#line 3270 "build/gen/f77/y.tab.c"
    break;

  case 239: /* infmt: SSTAR  */
#line 872 "build/gen/f77/gram.in"
                {
		ioclause(IOSUNIT, NULL);
		ioclause(IOSFMT, NULL);
		endioctl();
		}
#line 3280 "build/gen/f77/y.tab.c"
    break;

  case 240: /* ioctl: SLPAR fexpr SRPAR  */
#line 880 "build/gen/f77/gram.in"
                { ioclause(IOSUNIT, yyvsp[-1]); endioctl(); }
#line 3286 "build/gen/f77/y.tab.c"
    break;

  case 241: /* ioctl: SLPAR ctllist SRPAR  */
#line 882 "build/gen/f77/gram.in"
                { endioctl(); }
#line 3292 "build/gen/f77/y.tab.c"
    break;

  case 244: /* ioclause: fexpr  */
#line 890 "build/gen/f77/gram.in"
                { ioclause(IOSPOSITIONAL, yyvsp[0]); }
#line 3298 "build/gen/f77/y.tab.c"
    break;

  case 245: /* ioclause: SSTAR  */
#line 892 "build/gen/f77/gram.in"
                { ioclause(IOSPOSITIONAL, NULL); }
#line 3304 "build/gen/f77/y.tab.c"
    break;

  case 246: /* ioclause: nameeq expr  */
#line 894 "build/gen/f77/gram.in"
                { ioclause(yyvsp[-1], yyvsp[0]); }
#line 3310 "build/gen/f77/y.tab.c"
    break;

  case 247: /* ioclause: nameeq SSTAR  */
#line 896 "build/gen/f77/gram.in"
                { ioclause(yyvsp[-1], NULL); }
#line 3316 "build/gen/f77/y.tab.c"
    break;

  case 248: /* nameeq: SNAMEEQ  */
#line 900 "build/gen/f77/gram.in"
                { yyval = iocname(); }
#line 3322 "build/gen/f77/y.tab.c"
    break;

  case 249: /* read: SREAD end_spec in_ioctl  */
#line 904 "build/gen/f77/gram.in"
                { iostmt = IOREAD; }
#line 3328 "build/gen/f77/y.tab.c"
    break;

  case 250: /* write: SWRITE end_spec in_ioctl  */
#line 908 "build/gen/f77/gram.in"
                { iostmt = IOWRITE; }
#line 3334 "build/gen/f77/y.tab.c"
    break;

  case 251: /* print: SPRINT end_spec fexpr in_ioctl  */
#line 912 "build/gen/f77/gram.in"
                {
		iostmt = IOWRITE;
		ioclause(IOSUNIT, NULL);
		ioclause(IOSFMT, yyvsp[-1]);
		endioctl();
		}
#line 3345 "build/gen/f77/y.tab.c"
    break;

  case 252: /* print: SPRINT end_spec SSTAR in_ioctl  */
#line 919 "build/gen/f77/gram.in"
                {
		iostmt = IOWRITE;
		ioclause(IOSUNIT, NULL);
		ioclause(IOSFMT, NULL);
		endioctl();
		}
#line 3356 "build/gen/f77/y.tab.c"
    break;

  case 253: /* inlist: inelt  */
#line 928 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[0],0); }
#line 3362 "build/gen/f77/y.tab.c"
    break;

  case 254: /* inlist: inlist SCOMMA inelt  */
#line 930 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], mkchain(yyvsp[0],0)); }
#line 3368 "build/gen/f77/y.tab.c"
    break;

  case 256: /* inelt: SLPAR inlist SCOMMA dospec SRPAR  */
#line 935 "build/gen/f77/gram.in"
                { yyval = mkiodo(yyvsp[-1],yyvsp[-3]); }
#line 3374 "build/gen/f77/y.tab.c"
    break;

  case 257: /* outlist: uexpr  */
#line 939 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[0], 0); }
#line 3380 "build/gen/f77/y.tab.c"
    break;

  case 258: /* outlist: other  */
#line 941 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[0], 0); }
#line 3386 "build/gen/f77/y.tab.c"
    break;

  case 260: /* out2: uexpr SCOMMA uexpr  */
#line 946 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3392 "build/gen/f77/y.tab.c"
    break;

  case 261: /* out2: uexpr SCOMMA other  */
#line 948 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3398 "build/gen/f77/y.tab.c"
    break;

  case 262: /* out2: other SCOMMA uexpr  */
#line 950 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3404 "build/gen/f77/y.tab.c"
    break;

  case 263: /* out2: other SCOMMA other  */
#line 952 "build/gen/f77/gram.in"
                { yyval = mkchain(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3410 "build/gen/f77/y.tab.c"
    break;

  case 264: /* out2: out2 SCOMMA uexpr  */
#line 954 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3416 "build/gen/f77/y.tab.c"
    break;

  case 265: /* out2: out2 SCOMMA other  */
#line 956 "build/gen/f77/gram.in"
                { yyval = hookup(yyvsp[-2], mkchain(yyvsp[0], 0) ); }
#line 3422 "build/gen/f77/y.tab.c"
    break;

  case 267: /* other: SLPAR uexpr SCOMMA dospec SRPAR  */
#line 961 "build/gen/f77/gram.in"
                { yyval = mkiodo(yyvsp[-1], mkchain(yyvsp[-3], 0) ); }
#line 3428 "build/gen/f77/y.tab.c"
    break;

  case 268: /* other: SLPAR other SCOMMA dospec SRPAR  */
#line 963 "build/gen/f77/gram.in"
                { yyval = mkiodo(yyvsp[-1], mkchain(yyvsp[-3], 0) ); }
#line 3434 "build/gen/f77/y.tab.c"
    break;

  case 269: /* other: SLPAR out2 SCOMMA dospec SRPAR  */
#line 965 "build/gen/f77/gram.in"
                { yyval = mkiodo(yyvsp[-1], yyvsp[-3]); }
#line 3440 "build/gen/f77/y.tab.c"
    break;

  case 270: /* in_ioctl: %empty  */
#line 969 "build/gen/f77/gram.in"
                { startioctl(); }
#line 3446 "build/gen/f77/y.tab.c"
    break;


#line 3450 "build/gen/f77/y.tab.c"

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

