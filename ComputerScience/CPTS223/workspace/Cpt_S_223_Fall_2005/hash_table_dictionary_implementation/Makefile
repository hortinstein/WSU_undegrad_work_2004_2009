#
# Makefile for Hash Table Dictionary Implementation
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: hashtabledictionaryimplementation

test: hashtabledictionaryimplementation
	./hashtabledictionaryimplementation 
	
hashtabledictionaryimplementation: hash_table_dictionary_implementation.o DatabaseWindow.o
	g++ hash_table_dictionary_implementation.o DatabaseWindow.o -o hashtabledictionaryimplementation $(LDFLAGS) 

clean:
	- rm *.o hashtabledictionaryimplementation
	- rm core*