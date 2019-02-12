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

void buildSymEXP(SymbolTable *t, EXP *e);
void buildSymSTMT(SymbolTable *t, STMT *s);

void printTable(SymbolTable *t);
