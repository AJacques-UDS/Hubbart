CC = clang++
CFLAGS = -Wall -Iinclude/ -Ilibs/ -std=c++11 -O0
CPPFILES = main.cpp src/python_token.cpp src/python_lexer.cpp src/lexer_exception.cpp
TESTFILES = test/test_python_lexer.cpp test/test_python_lexeme.cpp src/python_token.cpp src/python_lexer.cpp src/lexer_exception.cpp

pyllvm:
	mkdir -p ./build/
	$(CC) $(CPPFILES) $(CFLAGS) -o ./build/lexer

.PHONY: test
test:
	mkdir -p ./build/
	$(CC) $(TESTFILES) $(CFLAGS) -o ./build/testing

.PHONY: clean
clean:
	rm -rf build/
