%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>


%}

%%
"return"        { return RETURN; }
","             { return COMMA; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"int"           { return INT; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"=="            { return EQ; }
"!="            { return NEQ; }
">"             { return GT; }
"<"             { return LT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"="             { return ASSIGN; }
";"             { return SEMI; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

[0-9]+          {
                    yylval.num = atoi(yytext);
                    return NUMBER;
                }

[a-zA-Z_][a-zA-Z0-9_]* {
                    yylval.str = strdup(yytext);
                    return ID;
                }

[ \t\n\r]+      { /* skip whitespace */ }

.               { /* skip unknown characters or throw error */ }

%%

int yywrap() {
    return 1;
}
