#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"

extern char *root;
extern int print_symbol;

int Hash(char *str)
{ unsigned int hash = 0;
  while (*str) hash = (hash << 1) + *str++; 
  return hash % HashSize;
}

SymbolTable *initSymbolTable()
{ SymbolTable *t;
  int i;
  t = malloc(sizeof(SymbolTable));
  for (i=0; i < HashSize; i++) t->table[i] = NULL;
  t->next = NULL;
  return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{ SymbolTable *t;
  t = initSymbolTable();
  t->next = s;
  return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, char *type)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  s = malloc(sizeof(SYMBOL));
  s->name = name;
  s->type = type;
  s->next = t->table[i];
  t->table[i] = s;
  return s;
}
 
SYMBOL *getSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  if (t->next==NULL) return NULL;
  return getSymbol(t->next,name);
}

SYMBOL *getSymbolScope(SymbolTable *t, char *name){
	int i = Hash(name);
	SYMBOL *s;
	for (s = t->table[i]; s; s = s->next) {
		if (strcmp(s->name,name)==0) return s;
	}
	return NULL;
}


void buildSymEXP(SymbolTable *t, EXP *e){
	switch (e->type) {
		case eIdentifier:
			if (getSymbol(t,e->val.identifier) == NULL){
				fprintf(stderr,"Error! %s is not defined",e->val.identifier);
					exit(1);
			}
			break;
		case eInt:
			break;
		case eFloat:
			break;
		case eBool:
			break;
		case eString:
			break;
		case eIdentity:
			buildSymEXP(t,e->val.exp);
			break;
		case eUnaryMinus:
			buildSymEXP(t,e->val.unary.exp);
			break;
		case eNegate:
			buildSymEXP(t,e->val.unary.exp);
			break;
		case eAddition:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;
		case eSubtraction:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;
		case eMultiplication:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;
		case eDivision:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eEqual:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;
		case eNotEqual:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eGreater:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eLess:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eGreaterEqual:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eLessEqual:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eLAnd:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;	
		case eLOr:
			buildSymEXP(t,e->val.binary.lhs);
			buildSymEXP(t,e->val.binary.rhs);
			break;
	}
}

 
void buildSymSTMT(SymbolTable *t, STMT *s){
	if (s != NULL){
		switch (s->type){
			case sRead:
				if(getSymbol(t,s->val.read.identifier) == NULL){
					fprintf(stderr,"Error! %s is not defined",s->val.read.identifier);
					exit(1);
				}
				break;
			case sPrint:
				buildSymEXP(t,s->val.print.exp);
				break;
			case sAssign:
				if(getSymbol(t,s->val.assign.identifier) == NULL){
					fprintf(stderr,"Error! %s is not defined", s->val.assign.identifier);
					exit(1);
				}
				buildSymEXP(t,s->val.assign.val);
				break;
			case sWhile:
				buildSymEXP(t, s->val.loop.condition);
				if (print_symbol) printf("{\n\t");
				SymbolTable *whileTable = scopeSymbolTable(t);
				buildSymSTMT(whileTable,s->val.loop.body);
				if (print_symbol) printf("}\n");
				break;
			case sIfStmt:
				buildSymEXP(t,s->val.ifstmt.condition);
				if (print_symbol) printf("{\n\t");
				SymbolTable *ifTable = scopeSymbolTable(t);
				buildSymSTMT(ifTable, s->val.ifstmt.body);
				if (print_symbol) printf("}\n");
				break;
			case sIfElseStmt:
				buildSymEXP(t,s->val.ifelsestmt.condition);
				if (print_symbol) printf("{\n\t");
				SymbolTable *ifElseTable1 = scopeSymbolTable(t);
				buildSymSTMT(ifElseTable1, s->val.ifelsestmt.body);
				if (print_symbol) printf("}\n");
				if (print_symbol) printf("{\n\t");
				SymbolTable *ifElseTable2 = scopeSymbolTable(t);
				buildSymSTMT(ifElseTable2, s->val.ifelsestmt.elsebody);
				if (print_symbol) printf("}\n");
				break;
			case sIfElifStmt:
				buildSymEXP(t,s->val.ifelifstmt.condition);
				if (print_symbol) printf("{\n\t");
				SymbolTable *ifElifTable1 = scopeSymbolTable(t);
				buildSymSTMT(ifElifTable1, s->val.ifelifstmt.body);
				if (print_symbol) printf("}\n");
				if (print_symbol) printf("{\n\t");
				SymbolTable *ifElifTable2 = scopeSymbolTable(t);
				buildSymSTMT(ifElifTable2, s->val.ifelifstmt.elifbody);
				if (print_symbol) printf("}\n");
				break;
			case sDeclare:
				if (getSymbolScope(t,s->val.declaration.identifier) == NULL)
					putSymbol(t, s->val.declaration.identifier, s->val.declaration.type);
				else{
					fprintf(stderr,"Error! %s already exists in this scope!",s->val.declaration.identifier);
					exit(1);
				}
				if (print_symbol){
					printf("%s: %s\n",s->val.declaration.identifier, s->val.declaration.type);
				}
				break;
			case sInit:
				if (getSymbolScope(t,s->val.initialization.identifier) == NULL){
					putSymbol(t, s->val.initialization.identifier, s->val.declaration.type);
					buildSymEXP(t,s->val.initialization.exp);
				}
				else{
					fprintf(stderr,"Error! %s already exists in this scope!",s->val.declaration.identifier);
					exit(1);
				}
				if (print_symbol){
					printf("%s: %s\n",s->val.initialization.identifier, s->val.initialization.type);
				}
				break;
		}
		if (s->next != NULL)
			buildSymSTMT(t,s->next);
	}
}



 