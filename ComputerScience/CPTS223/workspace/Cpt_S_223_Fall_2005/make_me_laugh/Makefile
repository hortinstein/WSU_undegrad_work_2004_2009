#
# Makefile for Make Me Laugh
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFlags = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`
test: make_me_laugh.o RiddleWindow.o 
	g++ make_me_laugh.o RiddleWindow.o -o makemelaugh $(LDFLAGS)
	./makemelaugh
all: make_me_laugh.o RiddleWindow.o 
	g++ make_me_laugh.o RiddleWindow.o -o makemelaugh $(LDFLAGS)


clean:
	- rm *.o makemelaugh
	- rm core*