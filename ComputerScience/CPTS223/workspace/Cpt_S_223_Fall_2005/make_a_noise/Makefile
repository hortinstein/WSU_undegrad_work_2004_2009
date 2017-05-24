#
# Makefile for Make A Noise
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`  -lm -L/usr/local/lib -lsndfile -L/usr/local/lib -lportaudio -lpthread

all: makeanoise

test: makeanoise
	./makeanoise
	
makeanoise: make_a_noise.o PlaybackWindow.o SamplePlayer.o SamplePlayer.o
	g++ make_a_noise.o PlaybackWindow.o SamplePlayer.o -o makeanoise $(LDFLAGS)


clean:
	- rm *.o makeanoise
	- rm core*