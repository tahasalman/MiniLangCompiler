#include <stdio.h>
#include "pretty.h"

void prettyEXP(EXP *e){
	switch (e->type) {
		case eIdentifier:
			printf("%s", e->val.identifier);
			break;
		case eInt:
			printf("%i", e->val.intLiteral);
			break;
		case eFloat:
			printf("%f", e->val.floatLiteral);
			break;
		case eBool:
			if (e->val.boolLiteral == 0)
				printf("false");
			else
				printf("true");
			break;
		case eString:
			printf("%s",e->val.stringLiteral);
			break;
		case eIdentity:
			printf("(");
			prettyEXP(e->val.exp);
			printf(")");
			break;
		case eUnaryMinus:
			printf("(-");
			prettyEXP(e->val.unary.exp);
			printf(")");
			break;
		case eNegate:
			printf("(!");
			prettyEXP(e->val.unary.exp);
			printf(")");
			break;
		case eAddition:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("+");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case eSubtraction:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("-");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case eMultiplication:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("*");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case eDivision:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("/");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eEqual:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("==");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case eNotEqual:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("!=");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		
		case eGreater:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(">");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eLess:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("<");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eGreaterEqual:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(">=");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eLessEqual:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("<=");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eLAnd:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("&&");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;	
		case eLOr:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("||");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	}
}

void prettySTMT(STMT *s){
	if (s != NULL){
		switch (s->type){
			case sRead:
				printf("read(%s);\n",s->val.read.identifier);
				break;
			case sPrint:
				printf("print(");
				prettyEXP(s->val.print.exp);
				printf(")\n;");
				break;
			case sAssign:
				printf("%s = ",s->val.assign.identifier);
				prettyEXP(s->val.assign.val);
				printf(";\n");
				break;
			case sWhile:
				printf("while (");
				prettyEXP(s->val.loop.condition);
				printf("){\n\t");
				prettySTMT(s->val.loop.body);
				printf("}\n");
				break;
			case sIfStmt:
				printf("if (");
				prettyEXP(s->val.ifstmt.condition);
				printf("){\n\t");
				prettySTMT(s->val.ifstmt.body);
				printf("}\n");
				break;
			case sIfElseStmt:
				printf("if (");
				prettyEXP(s->val.ifelsestmt.condition);
				printf("){\n\t");
				prettySTMT(s->val.ifelsestmt.body);
				printf("}\nelse{");
				prettySTMT(s->val.ifelsestmt.elsebody);
				printf("}\n");
				break;
			case sIfElifStmt:
				printf("if (");
				prettyEXP(s->val.ifelifstmt.condition);
				printf("){\n");
				prettySTMT(s->val.ifelifstmt.body);
				printf("}\nelse");
				prettySTMT(s->val.ifelifstmt.elifbody);
				break;
			case sDeclare:
				printf("var %s : %s ;\n",
				s->val.declaration.identifier,
				s->val.declaration.type);
				break;
			case sInit:
				printf("var %s : %s = ",
				s->val.initialization.identifier,
				s->val.initialization.type);
				prettyEXP(s->val.initialization.exp);
				printf(";\n");
				break;
			default:
				printf("\n");
		}
		if (s->next !=NULL)
			prettySTMT(s->next);
	}
}