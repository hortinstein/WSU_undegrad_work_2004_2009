#
# Makefile for Photo Database Browser
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`

all: photodatabasebrowser

test: photodatabasebrowser
	./photodatabasebrowser ./pics
	
photodatabasebrowser: photo_database_browser.o DatabaseWindow.o
	g++ photo_database_browser.o DatabaseWindow.o -o photodatabasebrowser $(LDFLAGS) 

clean:
	- rm *.o photodatabasebrowser
	- rm core*