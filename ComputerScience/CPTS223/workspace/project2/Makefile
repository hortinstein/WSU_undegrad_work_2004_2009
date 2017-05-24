#
# Makefile for Implementing a Scorch
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/X11R6/lib -lXft -lX11 -lfreetype -lXrender -lfontconfig -lfltk_images -lpng -lz -ljpeg -lfltk_gl -lGLU -lGL -lfltk -lXft -lpthread -lm -lXext -lX11 -lsupc++

SCORCH = Scorch.o Player.o
CONNECTION = Socket.o Connection.o ServerConnection.o ClientConnection.o ConnectionWindow.o

#All
all: asciiscorch windowscorch server client client2 connectionwindow

#Tests
test: asciiscorch windowscorch server client client2 connectionwindow
	./Scorch
	./Server&
	./Client&
	./Client2
	./WindowScorch
	./ConnectionWindow
	
window: windowscorch
	./WindowScorch
	
#References

asciiscorch: $(SCORCH) asciiscorch.o 
	g++ $(SCORCH) asciiscorch.o -o Scorch $(LDFLAGS)

windowscorch: $(SCORCH) MyWindow.o test_main.o 
	g++ $(SCORCH) MyWindow.o test_main.o -o WindowScorch $(LDFLAGS)
	
server: $(CONNECTION) ServerTest.o
	g++ $(CONNECTION) ServerTest.o -o Server $(LDFLAGS)
	
client: $(CONNECTION) ClientTest.o
	g++ Socket.o Connection.o ClientConnection.o ClientTest.o -o Client $(LDFLAGS)
	
client2: $(CONNECTION) Client2Test.o
	g++ $(CONNECTION) Client2Test.o -o Client2 $(LDFLAGS)
	
connectionwindow: $(CONNECTION) ConnectionWindowTest.o
	g++ $(CONNECTION) ConnectionWindowTest.o -o ConnectionWindow $(LDFLAGS)
	
#Clean
clean:
	
	- rm -f *.o Scorch
	- rm -f *.o WindowScorch
	- rm -f *.o Server
	- rm -f *.o Client
	- rm -f *.o Client2
	- rm -f *.o ConnectionWindow
	- rm -f core*
	- rm -f *~

rar: 
	make clean; \
	cd ..; \
	tar -c -v -z -f project2.tar.gz project2; \
	
lines:
	wc *.h *.cc Makefile | sort -n;

Terrain.o: Terrain.cc Terrain.h
Player.o: Player.cc Player.h
MyWindow.o: MyWindow.cc MyWindow.h
Socket.o: Socket.cc Socket.h
Connection.o: Connection.cc Connection.h
ServerConnection.o: ServerConnection.cc ServerConnection.h
ClientConnection.o: ClientConnection.cc ClientConnection.h
ConnectionWindow.o: ConnectionWindow.cc ConnectionWindow.h