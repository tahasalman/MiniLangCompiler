/* The first section of a flex file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the scanner verbatim
 *    2. Helper definitions for regexes
 *    3. Scanner options
 */

/* Code section */
%{
#include "parser.tab.h" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>

// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}



/* Scanner options, line number generation */
%option yylineno

/* Removes warnings about input/output functions */
%option noinput
%option nounput

%%
[ \r\n\t]+      ;      
 
":"		return tCOLON;
";"	    	return tSEMICOLON;
"+"         	return tPLUS;
"-"        	return tMINUS;
"*"         	return tMULTIPLY;
"/"         	return tDIVIDE;
"("         	return tLEFTPAREN;
")"         	return tRIGHTPAREN;
"{"		return tLEFTBRACE;
"}"		return tRIGHTBRACE;
"="		return tASSIGN;
"!"		return tNEGATE;
"=="		return tEQUALS;
"!="		return tNOTEQUALS;
">="		return tGREATEREQUALS;
"<="		return tLESSEQUALS;
">"		return tGREATER;
"<"		return tLESS;
"&&"		return tAND;
"||"		return tOR;
"var"		return tVAR;
"float"		return tFLOAT;
"int"		return tINT;
"string"	return tSTRING;
"boolean"	return tBOOLEAN;
"if"		return tIF;
"else"		return tELSE;
"while"		return tWHILE;
"read"		return tREAD;
"print"		return tPRINT;
"true"		return tTRUE;
"false"		return tFALSE;

[/][/].*


\"([a-zA-Z0-9]|[~@#$%^&*\-+/`<>=_|'.,;:!?\{\}\[\]()]|(\\[abfnrtv\"\\])|[ \t\r\n])*\" {
	yylval.stringval = strdup(yytext);
	return tSTRINGVAL;
}

(0|([1-9][0-9]*))\.[0-9]+ {
	yylval.floatval = atof(yytext);
	return tFLOATVAL;
}

0|([1-9][0-9]*) {
		yylval.intval = atoi(yytext);
	    return tINTVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
		yylval.identifier = strdup(yytext);
	    return tIDENTIFIER;
}



. { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
