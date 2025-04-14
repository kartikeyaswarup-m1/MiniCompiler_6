#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "parser.tab.h"

#define MAX_SYMBOLS 100
#define MAX_CODE 100

typedef struct {
    char name[20];
    int type;
    int initialized;
} Symbol;

Symbol symTable[MAX_SYMBOLS];
int symCount = 0;

typedef struct {
    char code[50];
} IntermediateCode;

IntermediateCode icTable[MAX_CODE];
int icCount = 0;
int tempVarCount = 0;

char* newTempVar() {
    static char temp[10];
    sprintf(temp, "t%d", tempVarCount++);
    return strdup(temp);
}

int lookup(char *name) {
    for (int i = 0; i < symCount; i++) {
        if (strcmp(symTable[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void insertSymbol(char *name, int type) {
    if (lookup(name) == -1) {
        strcpy(symTable[symCount].name, name);
        symTable[symCount].type = type;
        symTable[symCount].initialized = 0;
        symCount++;
    } else {
        printf("Error: Variable %s already declared!\n", name);
    }
}

void initializeSymbol(char *name) {
    int idx = lookup(name);
    if (idx != -1) symTable[idx].initialized = 1;
}

void checkInitialization(char *name) {
    int idx = lookup(name);
    if (idx != -1 && symTable[idx].initialized == 0) {
        printf("Warning: Variable %s used before initialization!\n", name);
    }
}

char* generateArithmeticIC(char *op, char *arg1, char *arg2) {
    char *result = newTempVar();
    sprintf(icTable[icCount++].code, "%s := %s %s %s", result, arg1, op, arg2);
    return result;
}

void generateIC(char *operation, char *arg1, char *arg2, char *result) {
    if (arg2 == NULL) {
        sprintf(icTable[icCount].code, "%s %s, %s", operation, result, arg1);
    } else {
        sprintf(icTable[icCount].code, "%s %s, %s, %s", operation, result, arg1, arg2);
    }
    icCount++;
}

void printIntermediateCode() {
    printf("\nIntermediate Code:\n");
    for (int i = 0; i < icCount; i++) {
        printf("%s\n", icTable[i].code);
    }
}

void generateAssembly() {
    printf("\nAssembly Code:\n");
    for (int i = 0; i < icCount; i++) {
        printf("%s\n", icTable[i].code);
    }
}

void finalizeCompilation() {
    printIntermediateCode();
    generateAssembly();
}
