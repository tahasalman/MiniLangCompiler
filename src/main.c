#include "stdio.h"
#include "string.h"
#include "tree.h"
#include "pretty.h"
#include "symbol_type.h"

int g_tokens = 0;
int print_symbol = 0;
STMT *root;
FILE *outFile;


void yyparse();
int yylex();
int main(int argc, char **argv)
{
		
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
	else if (strcmp(argv[1],"codegen") == 0) {	
		if (argc != 3){
			fprintf(stderr,"Please enter a .min file as an argument to run codegen on!");
			return 1;
		}
		char *filename = argv[2];
		yyparse();
		SymbolTable *t = initSymbolTable();
		checkSTMTType(t,root); 

		
		filename[strlen(filename)-4] =0;
		filename = strcat(filename,".c");
		
		outFile = fopen(filename,"w");
		
		fprintf(outFile,"#include <stdio.h>\n#include<stdlib.h>\n\nint main(){\n");
		SymbolTable *t2 = initSymbolTable();
		evalSTMT(t2,root);
		
		fprintf(outFile,"}");
		fclose(outFile);
		printf("OK\n");
		
	}
	else{
		fprintf(stderr, "Invalid compiler mode entered!");
		return 1;
	}
	return 0;

}
