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
};

EXP *makeExpFloat(float floatLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eFloat;
	e->val.floatLiteral = floatLiteral;
	return e;
};

EXP *makeExpBool(bool boolLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eBool;
	e->val.boolLiteral = boolLiteral;
	return e;
};

EXP *makeExpString(char *stringLiteral){
	EXP *e = malloc(sizeof(EXP));
	e->type = eString;
	e->val.stringLiteral = stringLiteral;
	return e;
};

EXP *makeExpUnary(ExpressionType op, EXP *exp);{
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
};