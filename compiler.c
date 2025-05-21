#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

typedef struct Symbol {
    char *name;
    int initialized;
    struct Symbol *next;
} Symbol;

static Symbol *symbolTable = NULL;
static int tempVarCount = 0;

typedef struct ICNode {
    char *code;
    struct ICNode *next;
} ICNode;

static ICNode *icHead = NULL, *icTail = NULL;

static void appendIC(const char *line) {
    ICNode *node = malloc(sizeof(ICNode));
    node->code = strdup(line);
    node->next = NULL;
    if (!icHead) {
        icHead = icTail = node;
    } else {
        icTail->next = node;
        icTail = node;
    }
}

void insertSymbol(const char *name, int initialized) {
    Symbol *sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->initialized = initialized;
    sym->next = symbolTable;
    symbolTable = sym;
}

void checkInitialization(const char *name) {
    Symbol *sym = symbolTable;
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            if (!sym->initialized) {
                fprintf(stderr, "Warning: Variable '%s' used before initialization\n", name);
            }
            return;
        }
        sym = sym->next;
    }
    fprintf(stderr, "Warning: Variable '%s' not declared\n", name);
}

void initializeSymbol(const char *name) {
    Symbol *sym = symbolTable;
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            sym->initialized = 1;
            return;
        }
        sym = sym->next;
    }
}

char* newTempVar() {
    char buffer[20];
    sprintf(buffer, "t%d", tempVarCount++);
    return strdup(buffer);
}

void generateIC(const char *op, const char *arg1, const char *arg2, const char *result) {
    char line[100];
    if (strcmp(op, "=") == 0) {
        snprintf(line, sizeof(line), "= %s, %s", result, arg1);
        appendIC(line);
    }
    // You can extend for other ops if needed
}

char* generateArithmeticIC(const char *op, const char *arg1, const char *arg2) {
    char *temp = newTempVar();
    char line[100];
    snprintf(line, sizeof(line), "%s := %s %s %s", temp, arg1, op, arg2);
    appendIC(line);
    return temp;
}

void printIC() {
    printf("Intermediate Code:\n");
    ICNode *cur = icHead;
    while (cur) {
        printf("%s\n", cur->code);
        cur = cur->next;
    }
}

void printAssembly() {
    printf("\nAssembly Code:\n");
    ICNode *cur = icHead;
    while (cur) {
        printf("%s\n", cur->code);
        cur = cur->next;
    }
}
