#
# Makefile for Vector Implimentation
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: vectorimplementation

test: vectorimplementation
	./vectorimplementation
	
vectorimplementation: vector_implementation.o Vec.o 
	g++ vector_implementation.o Vec.o -o vectorimplementation $(LDFLAGS)


clean:
	- rm *.o vectorimplementation
	- rm core*