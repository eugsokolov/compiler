escc: esparser.tab.o lex.yy.o hash.o sym_table.o
	gcc -o escc esparser.tab.o lex.yy.o sym_table.o hash.o -lm

lex.yy.o: eslex.l tokens-manual.h yylval.h
	flex eslex.l
	gcc -c lex.yy.c

esparser.tab.o: esparser.y tokens-manual.h
	bison -vd esparser.y
	gcc -c esparser.tab.c

sym_table.o: sym_table.c sym_table.h
	gcc -c sym_table.c

hash.o: hash.c hash.h
	gcc -c hash.c

clean: rm *.o esparser.tab.* lex.yy.* *.output
