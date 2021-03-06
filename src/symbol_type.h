#include "tree.h"


#define HashSize 317



typedef struct SYMBOL {
    char *name;
    char *type;
    struct SYMBOL *next;
} SYMBOL; 

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *next;
} SymbolTable;


SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, char *type);
SYMBOL *getSymbol(SymbolTable *t, char *name);
SYMBOL *getSymbolScope(SymbolTable *t, char *name);	//returns symbol if it exists in current scope

char *getType(SymbolTable *t, char *name);


void buildSymEXP(SymbolTable *t, EXP *e);
void buildSymSTMT(SymbolTable *t, STMT *s);

char *getEXPType(SymbolTable *t, EXP *e);
void checkSTMTType(SymbolTable *t, STMT *s);

void evalEXP(SymbolTable *t, EXP *e);
void evalSTMT(SymbolTable *t, STMT *s);

