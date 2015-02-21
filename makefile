escc: esparser.tab.o lex.yy.o hash.o sym_table.o
	gcc -o escc esparser.tab.o lex.yy.o sym_table.o hash.o -lm

hash.o: hash.c hash.h
	gcc -c hash.c

esparser.tab.o: esparser.y tokens-manual.h
	bison -vd esparser.y
	gcc -c esparser.tab.c

lex.yy.o: eslex.l tokens-manual.h yylval.h
	flex eslex.l
	gcc -c lex.yy.c

clean: rm *.o parser.tab.* lex.yy.* parser.output
