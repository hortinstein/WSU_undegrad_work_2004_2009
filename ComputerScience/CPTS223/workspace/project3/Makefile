#
# Makefile for Implementing a Scorch
#
# Compiler: Eclipse
# Linker: Eclipse
# 
CXXFLAGS = -O0 -g3 -Wall -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/X11R6/lib -lXft -lX11 -lfreetype -lXrender -lfontconfig -lfltk_images -lpng -lz -ljpeg -lfltk_gl -lGLU -lGL -lfltk -lXft -lpthread -lm -lXext -lX11 -lsupc++

SCORCH = Scorch.o Player.o MyWindow.o
CONNECTION = Socket.o Connection.o ServerConnection.o ClientConnection.o ConnectionWindow.o

#All
all: server client client2 connectionwindow asciiscorch windowscorch 

#Tests
test: server client client2 connectionwindow asciiscorch windowscorch
	./Scorch
	./Server&
	./Client&
	./Client2
	./ConnectionWindow
	
window: windowscorch
	./WindowScorch
	
#References

asciiscorch: $(SCORCH) $(CONNECTION) asciiscorch.o 
	g++ $(SCORCH) $(CONNECTION) asciiscorch.o -o Scorch $(LDFLAGS)

windowscorch: $(SCORCH) $(CONNECTION) test_main.o 
	g++ $(SCORCH) $(CONNECTION) test_main.o -o WindowScorch $(LDFLAGS)
	
server: $(SCORCH) $(CONNECTION) ServerTest.o
	g++ $(SCORCH) $(CONNECTION) ServerTest.o -o Server $(LDFLAGS)
	
client: $(SCORCH) $(CONNECTION) ClientTest.o
	g++ $(SCORCH) $(CONNECTION) ClientTest.o -o Client $(LDFLAGS)
	
client2: $(SCORCH) $(CONNECTION) Client2Test.o
	g++ $(SCORCH) $(CONNECTION) Client2Test.o -o Client2 $(LDFLAGS)
	
connectionwindow: $(SCORCH) $(CONNECTION)  ConnectionWindowTest.o
	g++ $(SCORCH) $(CONNECTION)  ConnectionWindowTest.o -o ConnectionWindow $(LDFLAGS)
	
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
	tar -c -v -z -f project3.tar.gz project3; \
	
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