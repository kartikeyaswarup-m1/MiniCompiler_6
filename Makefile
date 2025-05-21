all: compiler

lex.yy.c: lexanalyser.l parser.tab.h
	flex lexanalyser.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

compiler.o: compiler.c compiler.h
	gcc -Wall -g -c compiler.c

lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c

parser.tab.o: parser.tab.c
	gcc -Wall -g -c parser.tab.c

main.o: main.c compiler.h
	gcc -Wall -g -c main.c

compiler: lex.yy.o parser.tab.o compiler.o main.o
	gcc -Wall -g -o compiler lex.yy.o parser.tab.o compiler.o main.o

clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h *.o compiler

