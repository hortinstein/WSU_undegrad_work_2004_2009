#
# Makefile for implementing_the_dictionary_adt
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: implementingthedictionaryadt

test: implementingthedictionaryadt #clean implementingthedictionaryadt
	./implementingthedictionaryadt pics
	
implementingthedictionaryadt: implementing_the_dictionary_adt.o DatabaseWindow.o
	g++ implementing_the_dictionary_adt.o DatabaseWindow.o -o implementingthedictionaryadt $(LDFLAGS)


clean:
	- rm *.o implementingthedictionaryadt
	- rm core*