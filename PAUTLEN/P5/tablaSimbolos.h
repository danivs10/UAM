#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "alfa.h"
#include "hashTable.h"

/* Declaration of functions */
int declare(char *lexema, Simbol *s);
int localDeclaration(char *lexema, Simbol *s);
int globalDeclaration(char*lexema, Simbol *s);
Simbol *isLocal(char *lexema);
Simbol *isGlobal(char *lexema);
int functionDeclaration(char *lexema, Simbol* s);
int endFunction(void);
void finish(void);
void *searchSimbolInTables(Hash_Table *local, Hash_Table *global, char *key);

#endif