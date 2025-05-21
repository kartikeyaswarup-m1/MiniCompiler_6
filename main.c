#include <stdio.h>

extern int yyparse();
extern void printIC();
extern void printAssembly();
extern FILE *yyin;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("File open error");
            return 1;
        }
    }

    int parseResult = yyparse();

    if (parseResult == 0) {
        printIC();
        printAssembly();
    } else {
        fprintf(stderr, "Parsing failed.\n");
    }

    return 0;
}
