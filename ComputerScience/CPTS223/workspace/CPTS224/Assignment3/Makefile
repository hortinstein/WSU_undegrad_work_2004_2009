#
# Makefile for Connect4
#

 
CXXFLAGS = 
LDFLAGS = 

#All
all: Connect4

#Tests
test: Connect4
	./Connect4 
	
#References
Connect4: connect_four.o main.o board.o
	g++ connect_four.o main.o board.o -o My_Game

connect_four.o: connect_four.cc connect_four.h
	g++ connect_four.cc connect_four.h -o connect_four

main.o: connect_four.o board.o main.cc
	g++ main.cc -o main
	
board.o: board.h board.cc
	g++ board.h board.cc -o board

#Clean
clean:
	- rm *.o Connect4
	- rm *.o main
	- rm *.o connect_four
	- rm *.o board
	- rm core*