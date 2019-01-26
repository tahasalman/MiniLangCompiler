/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_PARSER_TAB_C_INCLUDED
# define YY_YY_PARSER_TAB_C_INCLUDED
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
    tUMINUS = 258,
    tUNEGATE = 259,
    tCOLON = 260,
    tSEMICOLON = 261,
    tPLUS = 262,
    tMINUS = 263,
    tMULTIPLY = 264,
    tDIVIDE = 265,
    tLEFTPAREN = 266,
    tRIGHTPAREN = 267,
    tRIGHTBRACE = 268,
    tLEFTBRACE = 269,
    tASSIGN = 270,
    tNEGATE = 271,
    tEQUALS = 272,
    tNOTEQUALS = 273,
    tGREATEREQUALS = 274,
    tLESSEQUALS = 275,
    tGREATER = 276,
    tLESS = 277,
    tAND = 278,
    tOR = 279,
    tVAR = 280,
    tFLOAT = 281,
    tINT = 282,
    tSTRING = 283,
    tBOOLEAN = 284,
    tIF = 285,
    tELSE = 286,
    tWHILE = 287,
    tREAD = 288,
    tPRINT = 289,
    tTRUE = 290,
    tFALSE = 291,
    tINTVAL = 292,
    tFLOATVAL = 293,
    tSTRINGVAL = 294,
    tIDENTIFIER = 295
  };
#endif
/* Tokens.  */
#define tUMINUS 258
#define tUNEGATE 259
#define tCOLON 260
#define tSEMICOLON 261
#define tPLUS 262
#define tMINUS 263
#define tMULTIPLY 264
#define tDIVIDE 265
#define tLEFTPAREN 266
#define tRIGHTPAREN 267
#define tRIGHTBRACE 268
#define tLEFTBRACE 269
#define tASSIGN 270
#define tNEGATE 271
#define tEQUALS 272
#define tNOTEQUALS 273
#define tGREATEREQUALS 274
#define tLESSEQUALS 275
#define tGREATER 276
#define tLESS 277
#define tAND 278
#define tOR 279
#define tVAR 280
#define tFLOAT 281
#define tINT 282
#define tSTRING 283
#define tBOOLEAN 284
#define tIF 285
#define tELSE 286
#define tWHILE 287
#define tREAD 288
#define tPRINT 289
#define tTRUE 290
#define tFALSE 291
#define tINTVAL 292
#define tFLOATVAL 293
#define tSTRINGVAL 294
#define tIDENTIFIER 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "minic.y" /* yacc.c:1909  */

	int intval;
	float floatval;
	char *stringval;
	char *identifier;

#line 141 "parser.tab.c" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_C_INCLUDED  */
