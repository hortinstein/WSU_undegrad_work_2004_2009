#
# Makefile for Implementing a Soundfile Class
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS =  -L/usr/X11R6/lib -L/usr/X11R6/lib -lXft -lX11 -lfreetype -lXrender \
  -lfontconfig -lfltk_images -lpng -lz -ljpeg -lfltk -lXft -lpthread \
  -lm -lXext -lX11 -lsupc++

#All
all: handofcards mywindow

#Tests
test: handofcards mywindow
	./handofcards
	./mywindow
#References

handofcards: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o HandOfCards.h hand_of_cards.o
	g++ Card.o HandOfCards.o hand_of_cards.o -o handofcards $(LDFLAGS)
	
mywindow: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o HandOfCards.h MyWindow.o MyWindow.h mywindow_test.o
	g++ Card.o HandOfCards.o MyWindow.o mywindow_test.o -o mywindow $(LDFLAGS)
#Clean

clean:
	- rm -f *.o handofcards
	- rm -f *.o mywindow
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f hw5.tar.gz hw5; \


    