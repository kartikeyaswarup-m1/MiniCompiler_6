%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;
%}

%union {
    int num;
    char *str;
}

%token <str> ID
%token <num> NUMBER
%token INT IF ELSE WHILE
%token EQ NEQ GT LT PLUS MINUS MULT DIV ASSIGN SEMI LBRACE RBRACE

%type <str> expression condition

%left PLUS MINUS
%left MULT DIV

%%

program: 
    program statement 
    | statement
    ;

statement: 
    INT ID SEMI                         { insertSymbol($2, 0); }
    | ID ASSIGN expression SEMI         { checkInitialization($1); initializeSymbol($1); generateIC("=", $3, NULL, $1); }
    | IF LBRACE condition RBRACE LBRACE program RBRACE ELSE LBRACE program RBRACE
    | WHILE LBRACE condition RBRACE LBRACE program RBRACE
    ;

condition: 
    expression GT expression
    | expression LT expression
    | expression EQ expression
    | expression NEQ expression
    ;

expression:
    expression PLUS expression          { $$ = generateArithmeticIC("+", $1, $3); }
    | expression MINUS expression       { $$ = generateArithmeticIC("-", $1, $3); }
    | expression MULT expression        { $$ = generateArithmeticIC("*", $1, $3); }
    | expression DIV expression         { $$ = generateArithmeticIC("/", $1, $3); }
    | ID                                { checkInitialization($1); $$ = $1; }
    | NUMBER {
        char temp[10];
        sprintf(temp, "%d", $1);
        char *val = strdup(temp);
        $$ = newTempVar();
        generateIC("=", val, NULL, $$);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
