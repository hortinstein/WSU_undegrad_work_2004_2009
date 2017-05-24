#
# Makefile for Implementing Lab1
#
# Compiler: gcc
# Linker: gcc
# #All
all: clean lab3

#Test
test: all
	clear
	./lab3

#References
lab3: lab3.o 
	cc lab3.o -o lab3

#Clean
clean:
	- rm *.o lab3
	
	- rm *~
	clear
rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f lab3.tar.gz Lab3; \
