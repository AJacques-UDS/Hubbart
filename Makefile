CC = clang++-12
CFLAGS = -Iinclude/ -std=c++14 -o build/pyllvmfe
CPPFILES = src/pyllvmfe.cpp src/python_token.cpp

pyllvmfe:
	$(CC) $(CPPFILES) $(CFLAGS)

clean:
	rm -f build/*