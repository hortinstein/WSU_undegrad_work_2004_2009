#
# Makefile for A Hierarchy of Filesystem Classes
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = `fltk-config --ldflags --use-images`  -lm -L/usr/local/lib -lsndfile -L/usr/local/lib -lportaudio -lpthread 

ahierarchyoffilesystemclasses: a_hierarchy_of_filesystem_classes.o File.o FileDir.o FileJpeg.o FileWav.o PlaybackWindow.o SamplePlayer.o
	g++ a_hierarchy_of_filesystem_classes.o File.o FileDir.o FileJpeg.o FileWav.o PlaybackWindow.o SamplePlayer.o -o ahierarchyoffilesystemclasses $(LDFLAGS) 

preview: preview.o File.o FileDir.o FileJpeg.o FileWav.o PlaybackWindow.o SamplePlayer.o
	g++ preview.o File.o FileDir.o FileJpeg.o FileWav.o PlaybackWindow.o SamplePlayer.o -o preview $(LDFLAGS) 

all: preview
	 
test: ahierarchyoffilesystemclasses
	./ahierarchyoffilesystemclasses 
	
clean:
	- rm *.o ahierarchyoffilesystemclasses
	- rm *.0 preview
	- rm core*

a_hierarchy_of_filesystem_classes.o: File.o a_hierarchy_of_filesystem_classes.cc
