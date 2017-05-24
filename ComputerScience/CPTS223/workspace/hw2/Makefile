#
# Makefile for Implementing a Soundfile Class
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS =  -lm -L/usr/local/lib -lsndfile

#All
all: playonce test_soundfile

#Tests
test: test_soundfile playonce
	./test_soundfile
	./playonce test_mono_boom.wav
	./playonce test_stereo_moo.wav
#References
playonce: playonce.o Soundfile.o Soundfile.h 
	g++ playonce.o Soundfile.o -o playonce $(LDFLAGS)
	
test_soundfile: implementing_a_soundfile_class.o Soundfile.o Soundfile.h
	g++ implementing_a_soundfile_class.o Soundfile.o -o test_soundfile $(LDFLAGS)

#Clean
clean:
	- rm *.o playonce
	- rm *.o test_soundfile
	- rm core*
	- rm *~
