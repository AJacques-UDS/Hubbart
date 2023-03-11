parser:
	bison -d --debug py.y -o ./build/py.tab.c
	flex py.l
	mv ./lex.yy.c ./build/lex.yy.c
	gcc ./build/lex.yy.c ./build/py.tab.c -I ./include -I ./build -lfl -o ./build/PythonParser

clean:
	rm -f ./build/*
