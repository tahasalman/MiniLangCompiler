#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_type.h"

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


char *getType(SymbolTable *t, char *name){
	SYMBOL *s = getSymbol(t,name);
	if (s!=NULL)
		return s->type;
	return NULL;
}


void buildSymEXP(SymbolTable *t, EXP *e){
	switch (e->type) {
		case eIdentifier:
			if (getSymbol(t,e->val.identifier) == NULL){
				fprintf(stderr,"Error (Line %i)! %s is not defined",e->lineno,e->val.identifier);
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
					fprintf(stderr,"Error (Line %i)! %s is not defined",s->lineno,s->val.read.identifier);
					exit(1);
				}
				break;
			case sPrint:
				buildSymEXP(t,s->val.print.exp);
				break;
			case sAssign:
				if(getSymbol(t,s->val.assign.identifier) == NULL){
					fprintf(stderr,"Error (Line %i)! %s is not defined",s->lineno, s->val.assign.identifier);
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
					fprintf(stderr,"Error (Line %i)! %s already exists in this scope!",s->lineno,s->val.declaration.identifier);
					exit(1);
				}
				if (print_symbol){
					printf("%s: %s\n",s->val.declaration.identifier, s->val.declaration.type);
				}
				break;
			case sInit:
				if (getSymbolScope(t,s->val.initialization.identifier) == NULL){
					putSymbol(t, s->val.initialization.identifier, s->val.initialization.type);
					buildSymEXP(t,s->val.initialization.exp);
				}
				else{
					fprintf(stderr,"Error (Line %i)! %s already exists in this scope!",s->lineno,s->val.initialization.identifier);
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


char *getEXPType(SymbolTable *t, EXP *e){
	char *type;
	char *type1;
	char *type2;
	switch (e->type) {
		case eIdentifier:
			type = getType(t,e->val.identifier);
			if (type == NULL){
				fprintf(stderr,"Error (Line %i)! %s is not defined",e->lineno,e->val.identifier);
				exit(1);
			}
			break;
		case eInt:
			type = "int";
			break;
		case eFloat:
			type = "float";
			break;
		case eBool:
			type= "boolean";
			break;
		case eString:
			type = "string";
			break;
		case eIdentity:
			type = getEXPType(t,e->val.exp);
			break;
		case eUnaryMinus:
			type = getEXPType(t,e->val.unary.exp);
			if (strcmp(type,"float") != 0 || strcmp(type,"int") != 0){
				fprintf(stderr,
				"Error (Line %i)! This expression is of type %s. Unary Minus can only be of type int or float",
				e->lineno,type);
				exit(1);
			}
			break;
		case eNegate:
			type = getEXPType(t,e->val.unary.exp);
			if (strcmp(type,"boolean") != 0){
				fprintf(stderr,
				"Error (Line %i)! This expression is of type %s. Negation can only be of type boolean",
				e->lineno,type);
				exit(1);
			}
			break;
		case eAddition:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if (!(
				((strcmp(type1,type2) == 0) && (strcmp(type1,"boolean") != 0)) ||
				((strcmp(type1,"int") == 0) && (strcmp(type2,"float") == 0)) ||
				((strcmp(type1,"float") == 0) && (strcmp(type2,"int") == 0))
				)){
					fprintf(stderr,
					"Error (Line %i) ! This expression is attempting an illegal addition between %s and %s",e->lineno,type1,type2);
					exit(1);
				}
			if (strcmp(type1,type2) != 0)
				type = "float";
			else
				type = type1;
			break;
		case eSubtraction:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if (!(
				((strcmp(type1,type2) == 0) && (strcmp(type1,"boolean") != 0)) ||
				((strcmp(type1,"int") == 0) && (strcmp(type2,"float") == 0)) ||
				((strcmp(type1,"float") == 0) && (strcmp(type2,"int") == 0))
				)){
					fprintf(stderr,
					"Error (Line %i)! This expression is attempting an illegal subtraction between %s and %s",
					e->lineno,type1,type2
					);
					exit(1);
				}			
			if (strcmp(type1,type2) != 0)
				type = "float";
			else
				type = type1;
			break;
		case eMultiplication:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if (!(
				((strcmp(type1,type2) == 0) && (strcmp(type1,"boolean") != 0)) ||
				((strcmp(type1,"int") == 0) && (strcmp(type2,"float") == 0)) ||
				((strcmp(type1,"float") == 0) && (strcmp(type2,"int") == 0))
				)){
					fprintf(stderr,
					"Error (Line %i)! This expression is attempting an illegal addition between %s and %s",
					e->lineno,type1,type2
					);
					exit(1);
				}
			if (strcmp(type1,type2) != 0)
				type = "float";
			else
				type = type1;
		break;
		case eDivision:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if (!(
				((strcmp(type1,type2) == 0) && (strcmp(type1,"boolean") != 0)) ||
				((strcmp(type1,"int") == 0) && (strcmp(type2,"float") == 0)) ||
				((strcmp(type1,"float") == 0) && (strcmp(type2,"int") == 0))
				)){
					fprintf(stderr,
					"Error (Line %i)! This expression is attempting an illegal addition between %s and %s",
					e->lineno,type1,type2
					);
					exit(1);
				}
			if (strcmp(type1,type2) != 0)
				type = "float";
			else
				type = type1;
			break;	
		case eEqual:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '==' but got %s and %s",
				e->lineno,type1, type2
				);
				exit(1);
				}
			type = "boolean";
			break;
		case eNotEqual:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '!=' but got %s and %s!",
				e->lineno,type1,type2
				);
				exit(1);
				}
			type = "boolean";
			break;	
		case eGreater:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '>' but got %s and %s!",
				e->lineno,type1,type2
				);
				exit(1);
				}
			type = "boolean";
			break;	
		case eLess:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '<' but got %s and %s!",
				e->lineno, type1,type2
				);
				exit(1);
				}
			type = "boolean";
			break;	
		case eGreaterEqual:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '>=' but got %s and %s!",
				e->lineno,type1,type2
				);
				exit(1);
				}
			type = "boolean";
			break;	
		case eLessEqual:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0)){
				fprintf(stderr,
				"Error (Line %i)! The expressions must be of the same type on both sides of '<=' but got %s and %s!",
				e->lineno,type1,type2
				);
				exit(1);
				}
			type = "boolean";
			break;	
		case eLAnd:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0) || (strcmp(type1,"boolean") !=0)) {
				fprintf(stderr,"Error (Line %i)! The expressions on either side of '&&' must both be of type boolean!", e->lineno);
				exit(1);
				}
			type = "boolean";
			break;	
		case eLOr:
			type1 = getEXPType(t,e->val.binary.lhs);
			type2 = getEXPType(t,e->val.binary.rhs);
			if ((strcmp(type1,type2) !=0) || (strcmp(type1,"boolean") !=0)) {
				fprintf(stderr,
				"Error (Line %i)! The expressions on either side of '||' must both be of type boolean!", e->lineno
				);
				exit(1);
				}
			type = "boolean";
			break;
	}
	return type;
}

 
void checkSTMTType(SymbolTable *t, STMT *s){
	if (s != NULL){
		char *type;
		char *type2;
		switch (s->type){
			case sRead:
				type = getType(t,s->val.read.identifier);
				if (type == NULL){
					fprintf(stderr,"Error (Line %i)! %s is not defined",s->lineno,s->val.read.identifier);
					exit(1);
				}					
				break;
			case sPrint:
				getEXPType(t,s->val.print.exp);
				break;
			case sAssign:
				type = getType(t,s->val.assign.identifier);
				if(type == NULL){
					fprintf(stderr,"Error (Line %i)! %s is not defined", s->lineno,s->val.assign.identifier);
					exit(1);
				}
				type2 = getEXPType(t,s->val.assign.val);
				if(strcmp(type, type2) != 0){
					fprintf(stderr,"Error (Line %i)! '%s' type expected for '%s' but got %s",s->lineno, type, s->val.assign.identifier,type2);
					exit(1);
				}
				break;
			case sWhile:
				type2 = getEXPType(t, s->val.loop.condition);
				if (strcmp(type2, "boolean") != 0){
					fprintf(stderr,"Error (Line %i)! 'boolean' type expected for while condition but got %s", s->lineno, type2);
					exit(1);
				}
				SymbolTable *whileTable = scopeSymbolTable(t);
				checkSTMTType(whileTable,s->val.loop.body);
				break;
			case sIfStmt:
				type2 = getEXPType(t, s->val.ifstmt.condition);
				if (strcmp(type2, "boolean") != 0){
					fprintf(stderr,"Error (Line %i)! 'boolean' type expected for if condition but got %s", s->lineno,type2);
					exit(1);
				}
				SymbolTable *ifTable = scopeSymbolTable(t);
				checkSTMTType(ifTable, s->val.ifstmt.body);
				break;
			case sIfElseStmt:
				type2 = getEXPType(t, s->val.ifelsestmt.condition);
				if (strcmp(type2, "boolean") != 0){
					fprintf(stderr,"Error (Line %i)! 'boolean' type expected for if condition but got %s", s->lineno,type2);
					exit(1);
				}
				SymbolTable *ifElseTable1 = scopeSymbolTable(t);
				checkSTMTType(ifElseTable1, s->val.ifelsestmt.body);
				SymbolTable *ifElseTable2 = scopeSymbolTable(t);
				checkSTMTType(ifElseTable2, s->val.ifelsestmt.elsebody);
				break;
			case sIfElifStmt:
				type2 = getEXPType(t, s->val.ifelifstmt.condition);
				if (strcmp(type2, "boolean") != 0){
					fprintf(stderr,"Error (Line %i)! 'boolean' type expected for if condition but got %s", s->lineno,type2);
					exit(1);
				}
				SymbolTable *ifElifTable1 = scopeSymbolTable(t);
				checkSTMTType(ifElifTable1, s->val.ifelifstmt.body);
				SymbolTable *ifElifTable2 = scopeSymbolTable(t);
				checkSTMTType(ifElifTable2, s->val.ifelifstmt.elifbody);
				break;
			case sDeclare:
				if (getSymbolScope(t,s->val.declaration.identifier) == NULL)
					putSymbol(t, s->val.declaration.identifier, s->val.declaration.type);
				else{
					fprintf(stderr,"Error (Line %i)! %s already exists in this scope!",s->lineno,s->val.declaration.identifier);
					exit(1);
				}
				break;
			case sInit:
				if (getSymbolScope(t,s->val.initialization.identifier) == NULL){
					putSymbol(t, s->val.initialization.identifier, s->val.initialization.type);
					type = getEXPType(t,s->val.initialization.exp);
					if (strcmp(type,s->val.declaration.type) != 0){
						fprintf(stderr,"Error (Line %i)! '%s' type expected for '%s' but got %s",s->lineno,s->val.initialization.type, s->val.initialization.identifier,type);
						exit(1);
					}
				}
				else{
					fprintf(stderr,"Error (Line %i)! %s already exists in this scope!",s->lineno,s->val.initialization.identifier);
					exit(1);
				}
				break;
		}
		if (s->next != NULL)
			checkSTMTType(t,s->next);
	}
}



 
