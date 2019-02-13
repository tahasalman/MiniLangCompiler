#include "stdio.h"
#include "string.h"
#include "tree.h"
#include "pretty.h"
#include "symbol_type.h"

int g_tokens = 0;
int print_symbol = 0;
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
	else if (strcmp(argv[1],"pretty") == 0){
		yyparse();
		prettySTMT(root);
	}
	else if (strcmp(argv[1],"symbol") == 0){
		yyparse();
		print_symbol=1;
		SymbolTable *t =initSymbolTable();
		buildSymSTMT(t,root);
	}
	else if (strcmp(argv[1],"typecheck") == 0){
		yyparse();
		SymbolTable *t = initSymbolTable();
		checkSTMTType(t,root);
		printf("OK\n");
	}
	else{
		fprintf(stderr, "Invalid compiler mode entered!");
		return 1;
	}
	return 0;

}
