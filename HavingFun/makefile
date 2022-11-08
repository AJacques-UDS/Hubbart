INC = -I ./

executable: testast.o ast.o
	gcc testast.o ast.o -o ast

testast.o: testast.c ast.h
	gcc $(INC) -c testast.c

ast.o: ast.c ast.h
	gcc $(INC) -c ast.c

clean:
	rm *.o ast.exe