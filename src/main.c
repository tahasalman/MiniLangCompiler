#include "stdio.h"
#include "string.h"
#include "tree.h"

int g_tokens = 0;
STMT *root;

void yyparse();
int yylex();
int main(int argc, char **argv)
{
	if (argc !=2){
		fprintf(stderr,"Invalid number of arguments!");
		return 1;
	}
	
    if(strcmp(argv[1], "tokens") == 0){
		g_tokens = 1;
		while(yylex());
	}
	else if (strcmp(argv[1], "scan") == 0){
		while(yylex());
		printf("OK\n");
	}
	else if (strcmp(argv[1], "parse") == 0){
		yyparse();
		printf("OK\n");
	}
	else{
		fprintf(stderr, "Invalid compiler mode entered!");
		return 1;
	}
	return 0;

}