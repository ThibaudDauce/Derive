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

#ifndef YY_YY_INCLUDE_Y_TAB_H_INCLUDED
# define YY_YY_INCLUDE_Y_TAB_H_INCLUDED
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
    NB = 258,
    VAR = 259,
    EXIT = 260,
    VIRGULE = 261,
    PAR_G = 262,
    PAR_D = 263,
    FIN = 264,
    OP_SIN = 265,
    OP_COS = 266,
    OP_TAN = 267,
    OP_EXP = 268,
    OP_LOG = 269,
    OP_ADD = 270,
    OP_SOUS = 271,
    OP_DIV = 272,
    OP_MUL = 273,
    OP_POW = 274
  };
#endif
/* Tokens.  */
#define NB 258
#define VAR 259
#define EXIT 260
#define VIRGULE 261
#define PAR_G 262
#define PAR_D 263
#define FIN 264
#define OP_SIN 265
#define OP_COS 266
#define OP_TAN 267
#define OP_EXP 268
#define OP_LOG 269
#define OP_ADD 270
#define OP_SOUS 271
#define OP_DIV 272
#define OP_MUL 273
#define OP_POW 274

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 15 "src/derive.y" /* yacc.c:1909  */
float val;char *ch;EM_ExpressionMathematique expr;

#line 95 "include/y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (EM_ExpressionMathematique* pResultat, char** pVariable, int* pCommande);

#endif /* !YY_YY_INCLUDE_Y_TAB_H_INCLUDED  */
