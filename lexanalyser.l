%{
#include "parser.tab.h"
%}

%%

"int"       { return INT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }
"=="        { return EQ; }
"!="        { return NEQ; }
">"         { return GT; }
"<"         { return LT; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"="         { return ASSIGN; }
";"         { return SEMI; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
[ \t\n]     { /* Ignore whitespace */ }
.           { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() { return 1; }
