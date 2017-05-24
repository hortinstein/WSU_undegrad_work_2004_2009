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
all: handofcards testwhist testasciiwhist mywindow

#Tests
test: handofcards testwhist testasciiwhist mywindow
	./handofcards
	./testwhist
	./mywindow
	./testasciiwhist

#References

handofcards: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o HandOfCards.h hand_of_cards.o
	g++ Card.o HandOfCards.o hand_of_cards.o -o handofcards $(LDFLAGS)

testwhist: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o DeckofCards.o Whist.o test_whist.o
	g++ Card.o HandOfCards.o test_whist.o DeckofCards.o Whist.o -o testwhist $(LDFLAGS)

testasciiwhist: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o DeckofCards.o Whist.o asciiwhist.o
	g++ Card.o HandOfCards.o DeckofCards.o Whist.o asciiwhist.o -o testasciiwhist $(LDFLAGS)		
	
mywindow: ListNode.h ListIterator.h List.h Card.o Card.h HandOfCards.o DeckofCards.o Whist.o MyWindow.o mywindow_test.o
	g++ Card.o HandOfCards.o DeckofCards.o Whist.o MyWindow.o mywindow_test.o -o mywindow $(LDFLAGS)

#Clean
clean:
	- rm -f *.o handofcards
	- rm -f *.o mywindow
	- rm -f *.o testwhist
	- rm -f *.o testasciiwhist
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f hw6.tar.gz hw6; \
	
lines:
	wc *.h *.cc Makefile | sort -n;

Card.o: Card.cc Card.h
HandOfCards.o: HandOfCards.cc HandOfCards.h
DeckofCards.o: DeckofCards.cc DeckofCards.h
Whist.o: Whist.cc Whist.h
asciiwhist.o: asciiwhist.cc
MyWindow.o: MyWindow.cc MyWindow.h 
