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

all: playlisteditor list

test: list playlisteditor
	./list
	./playlisteditor
	
homo_test: list test1
	./test1
	
playlisteditor: $(EDITOR_OBJ) ListNode.h ListIterator.h List.h  Soundfile.o Soundfile.h
	$(CXX) -o playlisteditor $(EDITOR_OBJ) Soundfile.o $(LDFLAGS)

test1: test1.o
	g++ test1.o -o test1	
	
list: ListNode.h ListIterator.h List.h template_list_with_iterators.o Soundfile.o Soundfile.h
	$(CXX) template_list_with_iterators.o Soundfile.o -o list $(LDFLAGS)
	
clean:
	- rm -f *.o playlisteditor 
	- rm -f *.o list
	- rm -f *.o test1
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f hw4.tar.gz hw4; \

	 
PlaylistEditorWindow.o: PlaylistEditorWindow.cc PlaylistEditorWindow.h
playlisteditor.o: playlisteditor.cc PlaylistEditorWindow.h

    