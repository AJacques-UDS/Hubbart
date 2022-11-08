INC = -I ./

executable: sym.o symtable.o
	gcc sym.o symtable.o -o sym.exe

sym.o: sym.c symtable.h
	gcc $(INC) -c sym.c

symtable.o: symtable.c symtable.h
	gcc $(INC) -c symtable.c

clean:
	rm *.o sym.exe