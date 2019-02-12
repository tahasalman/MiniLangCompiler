#ifndef TREE_H
#define TREE_H

typedef enum{
	eIdentifier,
	eInt,
	eFloat,
	eBool,
	eString,
	eIdentity,
	eUnaryMinus,
	eNegate,
	eAddition,
	eSubtraction,
	eMultiplication,
	eDivision,
	eGreater,
	eLess,
	eGreaterEqual,
	eLessEqual,
	eEqual,
	eNotEqual,
	eLAnd,
	eLOr
}ExpressionType;


typedef enum{
	sRead,
	sPrint,
	sAssign,
	sWhile,
	sIfStmt,
	sIfElseStmt,
	sIfElifStmt,
	sDeclare,
	sInit
}StatementType;

typedef struct EXP EXP;
struct EXP{
	ExpressionType type;
	union {
		char *identifier;
		int intLiteral;
		float floatLiteral;
		int boolLiteral;
		char *stringLiteral;
		EXP *exp;
		struct {EXP *exp;} unary;
		struct {EXP *lhs; EXP *rhs;} binary;
	}val;
};

typedef struct STMT STMT;
struct STMT{
	StatementType type;
	union {
		struct {char *identifier;} read;
		struct {EXP *exp;} print;
		struct {char *identifier; EXP *val;} assign;
		struct {char *identifier; char *type;} declaration;
		struct {char *identifier; char *type; EXP *exp;} initialization;
		struct {EXP *condition; STMT *body;} loop;
		struct {EXP *condition; STMT *body;} ifstmt;
		struct {EXP *condition; STMT *body; STMT *elsebody;} ifelsestmt;
		struct {EXP *condition; STMT *body; STMT *elifbody;} ifelifstmt;
	}val;
	STMT *next;
};

typedef struct PROGRAM PROGRAM;
struct PROGRAM{
	STMT *next;
};


EXP *makeExpIdentifier(char *identifier);
EXP *makeExpInt(int intLiteral);
EXP *makeExpFloat(float floatLiteral);
EXP *makeExpBool(int boolLiteral);
EXP *makeExpString(char *stringLiteral);
EXP *makeExpIdentity(EXP *exp);
EXP *makeExpUnary(ExpressionType op, EXP *exp);
EXP *makeExpBinary(ExpressionType op, EXP *lhs, EXP *rhs);



STMT *makeStmtRead(char *identifier, STMT *next);
STMT *makeStmtPrint(EXP *identifier, STMT *next);
STMT *makeStmtAssign(char *identifier, EXP *val, STMT *next);
STMT *makeStmtDecl(char *identifier, char *type, STMT *next);
STMT *makeStmtInit(char *identifier, char *type, EXP *exp, STMT *next);
STMT *makeStmtLoop(EXP *condition, STMT *body, STMT *next);
STMT *makeStmtIf(EXP *condition, STMT *body, STMT *next);
STMT *makeStmtIfElse(EXP *condition, STMT *body, STMT *elsebody, STMT *next);
STMT *makeStmtIfElif(EXP *condition, STMT *body, STMT *elifbody, STMT *next);

PROGRAM *makeProgram(STMT *next);
#endif /* !TREE_H */