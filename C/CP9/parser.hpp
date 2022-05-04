/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TDOUBLE = 260,
    TCEQ = 261,
    TCNE = 262,
    TCLT = 263,
    TCLE = 264,
    TCGT = 265,
    TCGE = 266,
    TLPAREN = 267,
    TRPAREN = 268,
    TLBRACE = 269,
    TRBRACE = 270,
    TCOMMA = 271,
    TDOT = 272,
    TPLUS = 273,
    TMINUS = 274,
    TMUL = 275,
    TDIV = 276,
    TCOLON = 277,
    TSEMIC = 278,
    TASSIG = 279,
    RPROGRAM = 280,
    RIS = 281,
    RBEGIN = 282,
    RENDPROGRAM = 283,
    RVAR = 284,
    RINTEGER = 285,
    RFLOAT = 286,
    RENDPROCEDURE = 287,
    RPROCEDURE = 288,
    RIN = 289,
    ROUT = 290,
    RIF = 291,
    RTHEN = 292,
    RELSE = 293,
    RENDIF = 294,
    RGET = 295,
    RPUT_LINE = 296,
    RWHILE = 297,
    RDO = 298,
    RENDWHILE = 299,
    REXIT = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "parser.y"

    string *str ; 
    vector<string> *list ;
    expresionstruct *expr ;
    int number ;
    vector<int> *numlist;

#line 111 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
