#include <stdio.h>

extern int yyparse();
extern FILE *yyin;
void finalizeCompilation();  

int main() {
    yyin = stdin;
    yyparse();
    finalizeCompilation(); 
    return 0;
}
