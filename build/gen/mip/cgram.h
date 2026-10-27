/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_GEN_MIP_Y_TAB_H_INCLUDED
# define YY_YY_BUILD_GEN_MIP_Y_TAB_H_INCLUDED
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
    NAME = 2,                      /* NAME  */
    STRING = 3,                    /* STRING  */
    ICON = 4,                      /* ICON  */
    FCON = 5,                      /* FCON  */
    PLUS = 6,                      /* PLUS  */
    MINUS = 8,                     /* MINUS  */
    MUL = 11,                      /* MUL  */
    AND = 14,                      /* AND  */
    OR = 17,                       /* OR  */
    ER = 19,                       /* ER  */
    QUEST = 21,                    /* QUEST  */
    COLON = 22,                    /* COLON  */
    ANDAND = 23,                   /* ANDAND  */
    OROR = 24,                     /* OROR  */
    ASOP = 25,                     /* ASOP  */
    RELOP = 26,                    /* RELOP  */
    EQUOP = 27,                    /* EQUOP  */
    DIVOP = 28,                    /* DIVOP  */
    SHIFTOP = 29,                  /* SHIFTOP  */
    INCOP = 30,                    /* INCOP  */
    UNOP = 31,                     /* UNOP  */
    STROP = 32,                    /* STROP  */
    TYPE = 33,                     /* TYPE  */
    CLASS = 34,                    /* CLASS  */
    STRUCT = 35,                   /* STRUCT  */
    RETURN = 36,                   /* RETURN  */
    GOTO = 37,                     /* GOTO  */
    IF = 38,                       /* IF  */
    ELSE = 39,                     /* ELSE  */
    SWITCH = 40,                   /* SWITCH  */
    BREAK = 41,                    /* BREAK  */
    CONTINUE = 42,                 /* CONTINUE  */
    WHILE = 43,                    /* WHILE  */
    DO = 44,                       /* DO  */
    FOR = 45,                      /* FOR  */
    DEFAULT = 46,                  /* DEFAULT  */
    CASE = 47,                     /* CASE  */
    SIZEOF = 48,                   /* SIZEOF  */
    ENUM = 49,                     /* ENUM  */
    LP = 50,                       /* LP  */
    RP = 51,                       /* RP  */
    LC = 52,                       /* LC  */
    RC = 53,                       /* RC  */
    LB = 54,                       /* LB  */
    RB = 55,                       /* RB  */
    CM = 56,                       /* CM  */
    SM = 57,                       /* SM  */
    ASSIGN = 58                    /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
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


#endif /* !YY_YY_BUILD_GEN_MIP_Y_TAB_H_INCLUDED  */
