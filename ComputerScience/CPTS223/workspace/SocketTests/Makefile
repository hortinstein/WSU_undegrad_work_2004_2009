#
# Makefile for Network Tests
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/X11R6/lib -lXft -lX11 -lfreetype -lXrender -lfontconfig -lfltk_images -lpng -lz -ljpeg -lfltk_gl -lGLU -lGL -lfltk -lXft -lpthread -lm -lXext -lX11 -lsupc++


#All
all: servertest clienttest

#Tests
test:servertest clienttest
	./ServerTests
	./ClientTests
#References

servertest: Socket.o server.o 
	g++  Socket.o server.o -o ServerTests $(LDFLAGS)

clienttest: Socket.o client.o 
	g++  Socket.o client.o -o ClientTests $(LDFLAGS)

#Clean
clean:
	
	- rm -f *.o ServerTests
	- rm -f *.o ClientTests
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f SocketTests.tar.gz SocketTests; \
	
lines:
	wc *.h *.cc Makefile | sort -n;

Socket.o: Socket.cc Socket.h
