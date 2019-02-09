
typedef enum{
	eIdentifier,
	eInt,
	eFloat,
	eBool,
	eString,
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
	dDeclaration,
	dInitialization
}DeclarationType;


typedef enum{
	sRead,
	sPrint,
	sAssignment,
	sWhile,
	sIf,
}StatementType

typedef struct EXP{
	ExpressionType type;
	union {
		char *identifier;
		int intLiteral;
		float floatLiteral;
		bool boolLiteral;
		char *stringLiteral;
		struct {EXP *exp} unary;
		struct {EXP *lhs, EXP *rhs} binary;
	}val
} EXP;

typedef struct DCL{
	DeclarationType type;
	
}

typedef struct STMT{
	StatementType type;
	union {
		struct {EXP *val} read;
		struct {EXP *val} print;
		struct {char *identifier, EXP *val} assign,
		struct {EXP *condi
		
	}
}

EXP *makeExpIdentifier(char *identifier);
EXP *makeExpInt(int intLiteral);
EXP *makeExpFloat(float floatLiteral);
EXP *makeExpBool(bool boolLiteral);
EXP *makeExpString(char *stringLiteral);
EXP *makeExpUnary(ExpressionType op, EXP *exp);
EXP *makeExpBinary(ExpressionType op, EXP *lhs, EXP *rhs);