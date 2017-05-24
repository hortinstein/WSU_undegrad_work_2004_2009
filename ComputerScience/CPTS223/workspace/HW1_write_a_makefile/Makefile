#
# Makefile for Make A Noise
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags`  -lm -L/usr/local/lib -lsndfile -L/usr/local/lib -lportaudio -lpthread

#All
all: playonce test_plysmps test_sndfl

#Tests
test: test_soundfile test_playsamps test_playonce

test_soundfile: test_sndfl
	./test_sndfl test_mono_boom.wav
	
test_playsamps: test_plysmps 
	./test_plysmps test_stereo_moo.wav
	
test_playonce: playonce
	./playonce test_stereo_moo.wav
	
#References
playonce: playonce.o Soundfile.o playsamps.o 
	g++ playonce.o Soundfile.o playsamps.o -o playonce $(LDFLAGS)
	
test_plysmps: test_play.o Soundfile.o playsamps.o 
	g++ test_play.o Soundfile.o playsamps.o -o test_plysmps $(LDFLAGS)

test_sndfl: test_soundfile.o Soundfile.o
	g++ test_soundfile.o Soundfile.o -o test_sndfl $(LDFLAGS)

#Clean
clean:
	- rm *.o playonce
	- rm *.o test_plysmps
	- rm *.o test_sndfl
	- rm core*