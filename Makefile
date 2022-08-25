build: pythonlex

pythonlex: lex.yy.c
	gcc -o pythonlex lex.yy.c -lfl -DDEBUG

lex.yy.c: python.l
	flex python.l

clean:
	rm lex.yy.c pythonlex