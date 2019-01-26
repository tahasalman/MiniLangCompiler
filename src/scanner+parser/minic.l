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

/* Helper definitions */

/* Scanner options, line number generation */
%option yylineno

/* Removes warnings about input/output functions */
%option noinput
%option nounput

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 *
 * When building a scanner+parser combo, the parser is responsible for fetching the next token
 * from the scanner, which returns scans and returns a single token at a time. As part of the
 * action, we thus return the next token. Tokens can either be (a) a character; or (b) a token
 * defined in bison (included in y.tab.h).
 */

/* Note the use of 3 keywords:
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 *    - yylval: Scanners transform input text into tokens (internally stored as an int) and pass
 *              them to the parser. For some the tokens (identifiers, constants), the original
 *              text is required in later phases. bison provides a variable yylval for each token
 *              to store this extra data. The definition of the yylval struct is provided as
 *              part of the bison grammar file.
 */
%%
%%
[\r\n]+
[ \t]+      
":"			return tCOLON;
";"			return tSEMICOLON;
"+"         return tPLUS;
"-"         return tMINUS;
"*"         return tMULTIPLY;
"/"         return tDIVIDE;
"("         return tLEFTPAREN;
")"         return tRIGHTPAREN;
"{"			return tLEFTBRACE;
"}"			return tRIGHTBRACE;
"="			return tASSIGN;
"!"			return tNEGATE;
"=="		return tEQUALS;
"!="		return tNOTEQUALS;
">="		return tGREATEREQUALS;
"<="		return tLESSEQUALS;
">"			return tGREATER;
"<"			return tLESS;
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

\"[^"\\]*(?s:\\.[^"\\]*)*\" {
	yylval.stringval = strdup(yytext);
	return tSTRINGVAL
}

(0|([1-9][0-9]*))\.[0-9]+ {
	yylval.floatval = atof(yytext);
	return tFLOATVAL
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
