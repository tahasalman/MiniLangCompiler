%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

extern int yylineno;
extern STMT *root;

int yylex();
void yyerror(const char *s) {
	fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
	exit(1);
}
%}

%code requires{
	#include "tree.h"
}

%union {
	int intval;
	float floatval;
	char *stringval;
	int boolval;
	char *identifier;
	char *type;
	EXP *exp;
	STMT *stmt;
	PROGRAM *program;
}

%type <exp> exp
%type <type> type
%type <stmt> stmt stmts dcl ifstmt 
%type <program> program

%token tUMINUS
%token tUNEGATE
%token tCOLON tSEMICOLON tPLUS tMINUS tMULTIPLY tDIVIDE;
%token tLEFTPAREN;
%token tRIGHTPAREN;
%token  tRIGHTBRACE;
%token  tLEFTBRACE;
%token  tASSIGN;
%token  tNEGATE;
%token  tEQUALS;
%token  tNOTEQUALS;
%token  tGREATEREQUALS;
%token  tLESSEQUALS;
%token  tGREATER;
%token  tLESS;
%token  tAND;
%token  tOR;
%token  tVAR;
%token  tFLOAT;
%token  tINT;
%token  tSTRING;
%token  tBOOLEAN;
%token  tIF;
%token  tELSE;
%token  tWHILE;
%token  tREAD;
%token  tPRINT;
%token  <boolval> tTRUE;
%token  <boolval> tFALSE;
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <stringval> tSTRINGVAL
%token <identifier> tIDENTIFIER 

%left tPLUS tMINUS
%left tMULTIPLY tDIVIDE
%left tUMINUS tUNEGATE

%start program
%locations
%error-verbose
%% 

program:  stmts {root = $1;};

stmts: %empty  {$$ = NULL;}| 
	stmt stmts {$$=$1, $$->next=$2;};

type: tINT {$$="int";}| 
	tFLOAT {$$="float";}| 
	tSTRING {$$="string";}| 
	tBOOLEAN {$$="boolean";};

stmt: dcl {$$=$1;}| 
	tREAD tLEFTPAREN tIDENTIFIER tRIGHTPAREN tSEMICOLON {$$=makeStmtRead($3,NULL);}|
	tPRINT tLEFTPAREN exp tRIGHTPAREN tSEMICOLON {$$=makeStmtPrint($3,NULL);} |
	tIDENTIFIER tASSIGN exp tSEMICOLON {$$=makeStmtAssign($1,$3,NULL);} |
	tWHILE tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE {$$=makeStmtLoop($3,$6,NULL);} |
	ifstmt {$$=$1;};

dcl: tVAR tIDENTIFIER tCOLON type tASSIGN exp tSEMICOLON {$$=makeStmtInit($2,$4,$6,NULL);}|
	tVAR tIDENTIFIER tCOLON type tSEMICOLON {$$=makeStmtDecl($2,$4,NULL);};

ifstmt: tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE {$$=makeStmtIf($3,$6,NULL);}|
	tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE tELSE tLEFTBRACE stmts tRIGHTBRACE {$$=makeStmtIfElse($3,$6,$10,NULL);}|
	tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE tELSE ifstmt {$$=makeStmtIfElif($3,$6,$9,NULL);};

exp: tIDENTIFIER {$$=makeExpIdentifier($1);} |
	tINTVAL {$$=makeExpInt($1);} | 
	tFLOATVAL {$$=makeExpFloat($1);} | 
	tSTRINGVAL {$$=makeExpString($1);} | 
	tTRUE {$$=makeExpBool(1);} | 
	tFALSE {$$=makeExpBool(0);} |
	tMINUS exp %prec tUMINUS {$$=makeExpUnary(eUnaryMinus,$2);} | 
	tNEGATE exp %prec tUNEGATE {$$=makeExpUnary(eNegate,$2);} |
	exp tMULTIPLY exp {$$=makeExpBinary(eMultiplication,$1,$3);} | 
	exp tDIVIDE exp {$$=makeExpBinary(eDivision,$1,$3);} | 
	exp tPLUS exp {$$=makeExpBinary(eAddition,$1,$3);} | 
	exp tMINUS exp {$$=makeExpBinary(eSubtraction,$1,$3);} |
	tLEFTPAREN exp tRIGHTPAREN {$$=makeExpIdentity($2);} |
	exp tGREATEREQUALS exp {$$=makeExpBinary(eGreaterEqual,$1,$3); } | 
	exp tLESSEQUALS exp {$$=makeExpBinary(eLessEqual,$1,$3);} | 
	exp tGREATER exp {$$=makeExpBinary(eGreater,$1,$3);} | 
	exp tLESS exp {$$=makeExpBinary(eLess,$1,$3);} |
	exp tEQUALS exp {$$=makeExpBinary(eEqual,$1,$3);} | 
	exp tNOTEQUALS exp {$$=makeExpBinary(eNotEqual,$1,$3);} |
	exp tAND exp {$$=makeExpBinary(eLAnd,$1,$3);} | 
	exp tOR exp {$$=makeExpBinary(eLOr,$1,$3);} 
	;


%%

