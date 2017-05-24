CXX = g++
CXXFLAGS = -O0 -g3 -Wall

TARGET = test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 test20 test21 test22 test23 test24 test25 test26 Vec.*

all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test21 test22 test16 test17 test18 test19 test23 test24 test25 test26 test20

test: basic const except general

basic: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test21 test22
	- ./test1
	- ./test2
	- ./test3
	- ./test4
	- ./test5
	- ./test6
	- ./test7
	- ./test8
	- ./test9
	- ./test10
	- ./test11
	- ./test12
	- ./test13
	- ./test14
	- ./test15
	- ./test21
	- ./test22


const: test16 test17 test18 test19 test20
	- ./test16
	- ./test17
	- ./test18
	- ./test19
	- ./test20


except: test23 test24 test25
	- ./test23
	- ./test24
	- ./test25

general: test26
	- ./test26

test1: test1.o ../Vec.o
	$(CXX) -o test1 test1.o ../Vec.o

test2: test2.o ../Vec.o
	$(CXX) -o test2 test2.o ../Vec.o

test3: test3.o ../Vec.o
	$(CXX) -o test3 test3.o ../Vec.o

test4: test4.o ../Vec.o
	$(CXX) -o test4 test4.o ../Vec.o

test5: test5.o ../Vec.o
	$(CXX) -o test5 test5.o ../Vec.o

test6: test6.o ../Vec.o
	$(CXX) -o test6 test6.o ../Vec.o

test7: test7.o ../Vec.o
	$(CXX) -o test7 test7.o ../Vec.o

test8: test8.o ../Vec.o
	$(CXX) -o test8 test8.o ../Vec.o

test9: test9.o ../Vec.o
	$(CXX) -o test9 test9.o ../Vec.o

test10: test10.o ../Vec.o
	$(CXX) -o test10 test10.o ../Vec.o

test11: test11.o ../Vec.o
	$(CXX) -o test11 test11.o ../Vec.o

test12: test12.o ../Vec.o
	$(CXX) -o test12 test12.o ../Vec.o

test13: test13.o ../Vec.o
	$(CXX) -o test13 test13.o ../Vec.o

test14: test14.o ../Vec.o
	$(CXX) -o test14 test14.o ../Vec.o

test15: test15.o ../Vec.o
	$(CXX) -o test15 test15.o ../Vec.o

test16: test16.o ../Vec.o
	$(CXX) -o test16 test16.o ../Vec.o

test17: test17.o ../Vec.o
	$(CXX) -o test17 test17.o ../Vec.o

test18: test18.o ../Vec.o
	$(CXX) -o test18 test18.o ../Vec.o

test19: test19.o ../Vec.o
	$(CXX) -o test19 test19.o ../Vec.o

test20: test20.o ../Vec.o
	$(CXX) -o test20 test20.o ../Vec.o

test21: test21.o ../Vec.o
	$(CXX) -o test21 test21.o ../Vec.o

test22: test22.o ../Vec.o
	$(CXX) -o test22 test22.o ../Vec.o

test23: test23.o ../Vec.o
	$(CXX) -o test23 test23.o ../Vec.o

test24: test24.o ../Vec.o
	$(CXX) -o test24 test24.o ../Vec.o

test25: test25.o ../Vec.o
	$(CXX) -o test25 test25.o ../Vec.o

test26: 
	cp ../Vec.c* ../Vec.h . 
	g++ -D ELEMENT_TYPE=float -Wall -g3 -O0 -c -o Vec.o Vec.cc
	g++ -D ELEMENT_TYPE=float -Wall -g3 -O0 -c -o test26.o test26.cc	
	$(CXX) -o test26 test26.o Vec.o

clean:
	rm -rf *.o $(TARGET)
