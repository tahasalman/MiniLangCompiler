#include <stdlib.h>
#include "tree.h"


EXP *makeExpIdentifier(char *identifier){
	EXP *e = malloc(sizeof(EXP));
	e->type = eIdentifier;
	e->val.identifier = identifier;
	return e;
}

EXP *makeExpInt(int intLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eInt;
	e->val.intLiteral = intLiteral;
	return e;
}

EXP *makeExpFloat(float floatLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eFloat;
	e->val.floatLiteral = floatLiteral;
	return e;
}

EXP *makeExpBool(int boolLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eBool;
	e->val.boolLiteral = boolLiteral;
	return e;
}

EXP *makeExpString(char *stringLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eString;
	e->val.stringLiteral = stringLiteral;
	return e;
}

EXP *makeExpIdentity(EXP *exp){
	EXP *e = malloc(sizeof(EXP));
	e->type = eIdentity;
	e->val.exp = exp;
	return e;
}

EXP *makeExpUnary(ExpressionType op, EXP *exp){
	EXP *e = malloc(sizeof(EXP));
	e->type = op;
	e->val.unary.exp = exp;
	return e;
}

EXP *makeExpBinary(ExpressionType op, EXP *lhs, EXP *rhs){
	EXP *e = malloc(sizeof(EXP));
	e->type = op;
	e->val.binary.lhs = lhs;
	e->val.binary.rhs = rhs;
	return e;
}

STMT *makeStmtRead(char *identifier, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sRead;
	s->val.read.identifier = identifier;
	s->next = next;
	return s;
}


STMT *makeStmtPrint(EXP *exp, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sPrint;
	s->val.print.exp = exp;
	s->next = next;
	return s;
}

STMT *makeStmtAssign(char *identifier, EXP *val, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sAssign;
	s->val.assign.identifier = identifier;
	s->val.assign.val = val;
	s->next = next;
	return s;
}


STMT *makeStmtDecl(char *identifier, char *type, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sDeclare;
	s->val.declaration.identifier = identifier;
	s->val.declaration.type = type;
	s->next = next;
	return s;
}


STMT *makeStmtInit(char *identifier, char *type, EXP *exp, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sInit;
	s->val.initialization.identifier = identifier;
	s->val.initialization.type = type;
	s->val.initialization.exp = exp;
	s->next = next;
	return s;
}


STMT *makeStmtLoop(EXP *condition, STMT *body, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sWhile;
	s->val.loop.condition = condition;
	s->val.loop.body = body;
	s->next = next;
	return s;
}

STMT *makeStmtIf(EXP *condition, STMT *body, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sIfStmt;
	s->val.ifstmt.condition = condition;
	s->val.ifstmt.body = body;
	s->next = next;
	return s;
}

STMT *makeStmtIfElse(EXP *condition, STMT *body, STMT *elsebody, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sIfElseStmt;
	s->val.ifelsestmt.condition = condition;
	s->val.ifelsestmt.body = body;
	s->val.ifelsestmt.elsebody = elsebody;
	s->next = next;
	return s;
}

STMT *makeStmtIfElif(EXP *condition, STMT *body, STMT *elifbody, STMT *next){
	STMT *s = malloc(sizeof(STMT));
	s->type = sIfElifStmt;
	s->val.ifelifstmt.condition = condition;
	s->val.ifelifstmt.body = body;
	s->val.ifelifstmt.elifbody = elifbody;
	s->next = next;
	return s;
}

PROGRAM *makeProgram(STMT *next){
	PROGRAM *p = malloc(sizeof(PROGRAM));
	p->next = next;
	return p;
}
