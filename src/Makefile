CC = gcc

CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o
	$(CC) lex.yy.o parser.tab.o tree.o pretty.o main.o -o minic -lfl

parser.tab.c parser.tab.h: minic.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h minic.y

lex.yy.c: minic.l parser.tab.h
	flex minic.l
clean:
	rm parser.tab.* lex.yy.*; rm *.o
