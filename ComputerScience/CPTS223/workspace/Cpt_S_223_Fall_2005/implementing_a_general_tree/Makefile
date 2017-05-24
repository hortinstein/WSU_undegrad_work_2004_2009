#
# Makefile for Implementing a General Tree
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: implementingageneraltree

test: implementingageneraltree #clean implementingageneraltree
	./implementingageneraltree
	
implementingageneraltree: implementing_a_general_tree.o Tree.o 
	g++ implementing_a_general_tree.o Tree.o -o implementingageneraltree $(LDFLAGS)


clean:
	- rm *.o implementingageneraltree
	- rm core*