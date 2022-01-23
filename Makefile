CC = clang++
CFLAGS = -Iinclude/ -Isrc -std=c++11 -o build/pyllvmfe.exe
CPPFILES = pyllvmfe.cpp PythonToken.cpp

pyllvmfe:
	$(CC) $(CPPFILES) $(CFLAGS)

clean
	rm -f build/*