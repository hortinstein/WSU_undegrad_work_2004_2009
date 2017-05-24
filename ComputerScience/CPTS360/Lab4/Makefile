#
# Makefile for Implementing Lab4
#
# Compiler: gcc
# Linker: gcc
# #All
all: clean lab4

#Test
test: all
	
#References

lab4: client server

client: client.o 
	cc client.o -o client

server: server.o
	cc server.o -o server

#Clean
clean:
	- rm *.o lab4
	
	- rm *~
