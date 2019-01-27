#include "stdio.h"

void yyparse();
int yylex();
int main()
{
        
	yyparse();
	printf("OK\n");
	return 0;
}
