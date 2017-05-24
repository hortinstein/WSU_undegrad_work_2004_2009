#
# Makefile for Playlist with Iterators
#
# Compiler: Eclipse
# Linker: Eclipse
# 

CXX = g++

# magic for adding flags needed by the FLTK library
FLTK_COMPILE_FLAGS_MAGIC = `fltk-config --cxxflags`
FLTK_LINKER_FLAGS_MAGIC = `fltk-config --ldflags` -lm -L/usr/local/lib -lsndfile

CXXFLAGS = -g3 -O0 -Wall 
LDFLAGS =  $(FLTK_LINKER_FLAGS_MAGIC) 

EDITOR_OBJ = PlaylistEditorWindow.o playlisteditor.o

all: playlisteditor playlist

test: playlist playlisteditor
	./playlist
	./playlisteditor

playlisteditor: $(EDITOR_OBJ) PlaylistNode.h PlaylistIterator.o PlaylistIterator.h Playlist.o Playlist.h  Soundfile.o Soundfile.h
	$(CXX) -o playlisteditor $(EDITOR_OBJ) PlaylistIterator.o Playlist.o Soundfile.o $(LDFLAGS)

playlist: playlist_with_iterators.o PlaylistNode.h PlaylistIterator.o PlaylistIterator.h Playlist.o Playlist.h  Soundfile.o Soundfile.h
	$(CXX) playlist_with_iterators.o PlaylistIterator.o Playlist.o Soundfile.o -o playlist $(LDFLAGS)
	
clean:
	- rm -f *.o playlisteditor 
	- rm -f *.o playlist
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f hw3.tar.gz hw3; \

	 
PlaylistEditorWindow.o: PlaylistEditorWindow.cc PlaylistEditorWindow.h
playlisteditor.o: playlisteditor.cc PlaylistEditorWindow.h

    