all:

	flex lexanalyser.l
	bison -d parser.y
	gcc -c lex.yy.c parser.tab.c compiler.c main.c
	gcc -o compiler lex.yy.o parser.tab.o compiler.o main.o


clean:
	rm -f compiler lex.yy.c parser.tab.c parser.tab.h lex.yy.o parser.tab.o compiler.o
