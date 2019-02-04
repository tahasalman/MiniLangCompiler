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
extern int g_tokens;
%}



/* Scanner options, line number generation */
%option yylineno

/* Removes warnings about input/output functions */
%option noinput
%option nounput

%%
[ \r\n\t]+      ;      
 
":"			{if (g_tokens) printf("tCOLON\n"); return tCOLON;}
";"	    	{if (g_tokens) printf("tSEMICOLON\n");return tSEMICOLON;}
"+"         {if (g_tokens) printf("tPLUS\n");return tPLUS;}
"-"        	{if (g_tokens) printf("tMINUS\n");return tMINUS;}
"*"         {if (g_tokens) printf("tMULTIPLY\n");return tMULTIPLY;}
"/"         {if (g_tokens) printf("tDIVIDE\n");return tDIVIDE;}
"("         {if (g_tokens) printf("tLEFTPAREN\n");return tLEFTPAREN;}
")"         {if (g_tokens) printf("tRIGHTPAREN\n");return tRIGHTPAREN;}
"{"			{if (g_tokens) printf("tLEFTBRACE\n");return tLEFTBRACE;}
"}"			{if (g_tokens) printf("tRIGHTBRACE\n");return tRIGHTBRACE;}
"="			{if (g_tokens) printf("tASSIGN\n");return tASSIGN;}
"!"			{if (g_tokens) printf("tNEGATE\n");return tNEGATE;}
"=="		{if (g_tokens) printf("tEQUALS\n");return tEQUALS;}
"!="		{if (g_tokens) printf("tNOTEQUALS\n");return tNOTEQUALS;}
">="		{if (g_tokens) printf("tGREATEREQUALS\n");return tGREATEREQUALS;}
"<="		{if (g_tokens) printf("tLESSEQUALS\n");return tLESSEQUALS;}
">"			{if (g_tokens) printf("tGREATER\n");return tGREATER;}
"<"			{if (g_tokens) printf("tLESS\n");return tLESS;}
"&&"		{if (g_tokens) printf("tAND\n");return tAND;}
"||"		{if (g_tokens) printf("tOR\n");return tOR;}
"var"		{if (g_tokens) printf("tVAR\n");return tVAR;}
"float"		{if (g_tokens) printf("tFLOAT\n");return tFLOAT;}
"int"		{if (g_tokens) printf("tINT\n");return tINT;}
"string"	{if (g_tokens) printf("tSTRING\n");return tSTRING;}
"boolean"	{if (g_tokens) printf("tBOOLEAN\n");return tBOOLEAN;}
"if"		{if (g_tokens) printf("tIF\n");return tIF;}
"else"		{if (g_tokens) printf("tELSE\n");return tELSE;}
"while"		{if (g_tokens) printf("tWHILE\n"); return tWHILE;}
"read"		{if (g_tokens) printf("tREAD\n");return tREAD;}
"print"		{if (g_tokens) printf("tPRINT\n");return tPRINT;}
"true"		{if (g_tokens) printf("tTRUE\n");return tTRUE;}
"false"		{if (g_tokens) printf("tFALSE\n");return tFALSE;}

[/][/].*


\"([a-zA-Z0-9]|[~@#$%^&*\-+/`<>=_|'.,;:!?\{\}\[\]()]|(\\[abfnrtv\"\\])|[ \t\r\n])*\" {
	if (g_tokens) 
		printf("tSTRINGVAL(%s)\n", yytext);
	yylval.stringval = strdup(yytext);
	return tSTRINGVAL;
}

(0|([1-9][0-9]*))\.[0-9]+ {
	if (g_tokens) 	
		printf("tFLOATVAL(%s)\n", yytext);
	yylval.floatval = atof(yytext);
	return tFLOATVAL;
}

0|([1-9][0-9]*) {
	if (g_tokens) 	 
		printf ("tINTVAL(%s)\n", yytext);
	yylval.intval = atoi(yytext);
	return tINTVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
	if (g_tokens)	  
		printf ("tIDENTIFIER(%s)\n", yytext);
	yylval.identifier = strdup(yytext);
	return tIDENTIFIER;
}

. { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
