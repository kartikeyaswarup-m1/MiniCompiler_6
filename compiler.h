// compiler.h

#ifndef COMPILER_H
#define COMPILER_H

char* newTempVar();
int lookup(char *name);
void insertSymbol(char *name, int type);
void initializeSymbol(char *name);
void checkInitialization(char *name);
char* generateArithmeticIC(char *op, char *arg1, char *arg2);
void generateIC(char *operation, char *arg1, char *arg2, char *result);
void printIntermediateCode();
void generateAssembly();
void finalizeCompilation();

#endif
