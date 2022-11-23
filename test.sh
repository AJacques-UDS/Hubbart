gcc -g -c ast.c -I ./include -o ./build/ast.o
gcc -g ./test/ast_test.c ./build/ast.o -I ./include -o ./build/AstTest