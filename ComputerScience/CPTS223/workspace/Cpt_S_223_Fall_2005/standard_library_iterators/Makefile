#
# Makefile for Standard Library Iterators
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: standardlibraryiterators

test: clean standardlibraryiterators
	./standardlibraryiterators
	
standardlibraryiterators: standard_library_iterators.o #Vec.o 
	g++ standard_library_iterators.o -o standardlibraryiterators $(LDFLAGS) #Vec.o -o standardlibraryiterators $(LDFLAGS)


clean:
	- rm *.o standardlibraryiterators
	- rm core*