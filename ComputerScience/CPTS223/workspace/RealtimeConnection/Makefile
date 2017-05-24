#
#
# Makefile for Implementing a my Realtime Connection
# Makefile for Implementing a my Realtime Connection
# Makefile for Implementing a my Realtime Connection
#
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/X11R6/lib -lXft -lX11 -lfreetype -lXrender -lfontconfig -lfltk_images -lpng -lz -ljpeg -lfltk_gl -lGLU -lGL -lfltk -lXft -lpthread -lm -lXext -lX11 -lsupc++

CONNECTION = Socket.o Connection.o ServerConnection.o ClientConnection.o ConnectionWindow.o

#All
all: connectionwindow

#Tests
test: connectionwindow
	./ConnectionWindow
	
#References

connectionwindow: $(CONNECTION) ConnectionWindowTest.o SquaresWin.o
	g++ $(CONNECTION) ConnectionWindowTest.o SquaresWin.o -o ConnectionWindow $(LDFLAGS)

	
#Clean
clean:
	
	- rm -f *.o Server
	- rm -f *.o Client
	- rm -f *.o Client2
	- rm -f *.o ConnectionWindow
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f RealtimeConnection.tar.gz RealtimeConnection; \
	
lines:
	wc *.h *.cc Makefile | sort -n;

Connection.o: Connection.cc Connection.h
ServerConnection.o: ServerConnection.cc ServerConnection.h
ClientConnection.o: ClientConnection.cc ClientConnection.h
ConnectionWindow.o: ConnectionWindow.cc ConnectionWindow.h
SquaresWin.o: SquaresWin.cc SquaresWin.h