#
# Makefile for Vector Iterators
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: vectoriterators

test: vectoriterators
	./vectoriterators
	
vectoriterators: vector_iterators.o #Vec.o 
	g++ vector_iterators.o -o vectoriterators $(LDFLAGS) #Vec.o -o vectoriterators $(LDFLAGS)


clean:
	- rm *.o vectoriterators
	- rm core*