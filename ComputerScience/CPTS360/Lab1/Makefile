#
# Makefile for Implementing Lab1
#
# Compiler: gcc
# Linker: gcc
# #All
all: clean lab1

#Test
test: all
	clear
	./lab1 floppyImage

#References
lab1: lab1.o 
	cc lab1.o -o lab1

#Clean
clean:
	- rm *.o lab1
	
	- rm *~
