#include <stdio.h>

extern int yyparse();
extern FILE *yyin;
void finalizeCompilation();  // 👈 Add this line

int main() {
    yyin = stdin;
    yyparse();
    finalizeCompilation(); // Optional: To print IC and assembly
    return 0;
}
