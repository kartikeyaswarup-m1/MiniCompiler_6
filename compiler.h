#ifndef COMPILER_H
#define COMPILER_H

void insertSymbol(const char *name, int initialized);
void checkInitialization(const char *name);
void initializeSymbol(const char *name);

char* newTempVar();

void generateIC(const char *op, const char *arg1, const char *arg2, const char *result);
char* generateArithmeticIC(const char *op, const char *arg1, const char *arg2);

void printIC();
void printAssembly();

#endif
