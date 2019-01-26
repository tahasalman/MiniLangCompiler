/* The first section of a flex file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the scanner verbatim
 *    2. Helper definitions for regexes
 *    3. Scanner options
 */

/* Code section */
%{
#include <stdio.h>
%}

/* Scanner options, line number generation */
%option yylineno

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 */

/* Note the use of 3 keywords:
 *    - yyleng: Length of the scanned token
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 */
%%
[\r\n]+
[ \t]+      
":"			{;}
";"			{;}
"+"         {;}
"-"         {;}
"*"         {;}
"/"         {;}
"("         {;}
")"         {;}
"{"			{;}
"}"			{;}
"="			{;}
"!"			{;}
"=="		{;}
"!="		{;}
">="		{;}
"<="		{;}
">"			{;}
"<"			{;}
"&&"		{;}
"||"		{;}


"var"		{;}
"float"		{;}
"int"		{;}
"string"	{;}
"boolean"	{;}
"if"		{;}
"else"		{;}
"while"		{;}
"read"		{;}
"print"		{;}
"true"		{;}
"false"		{;}

[/][/].*

\"[^"\\]*(?s:\\.[^"\\]*)*\" {;}

(0|([1-9][0-9]))*\.[0-9][0-9]* {;}

0|([1-9][0-9]*) {;}

[a-zA-Z_][a-zA-Z0-9_]* {;}



. 	    { fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%

// The final section of a flex file contains the user code
int main()
{
	// Invoke the scanner using yylex(). Since there is no parser, this will execute until
	// the end of file
	yylex();
        printf("OK\n");
	return 0;
}

