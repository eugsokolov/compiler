escc: parser.tab.o lex.yy.o hash.o sym_table.o ast.o quads.o target.o
	gcc -o escc parser.tab.o lex.yy.o sym_table.o ast.o hash.o quads.o target.o -lm

lex.yy.o: eslex.l tokens-manual.h yylval.h
	flex eslex.l
	gcc -c lex.yy.c

parser.tab.o: parser.y tokens-manual.h
	bison -vd parser.y
	gcc -c parser.tab.c

target.o: target.c target.h
	gcc -c target.c

quads.o: quads.c quads.h
	gcc -c quads.c

ast.o: ast.c ast.h
	gcc -c ast.c

sym_table.o: sym_table.c sym_table.h
	gcc -c sym_table.c

hash.o: hash.c hash.h
	gcc -c hash.c

cn: 
	rm *.o parser.tab.* lex.yy.* *.output escc *~
