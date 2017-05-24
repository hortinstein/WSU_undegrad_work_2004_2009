# this should be the name of the assignment
PROG = drawcells

# Change this to the operating system you develop on (if it's not
# Linux), and then back to "LINUX" when you port, test(!!!), and
# submit your final result.
OSNAME = LINUX

# The following should be either "PULLMAN" or "TRICITIES"
LOCATION = PULLMAN

# adding a level of indirection here allows you to create one makefile
# that works on several different operating systems
CC = $(CC_$(OSNAME))
CFLAGS = $(CFLAGS_$(OSNAME))
LDFLAGS = $(LDFLAGS_$(OSNAME))
LIBS = $(LIBS_$(OSNAME))

CC_LINUX = cc
# good practice for GCC...
CFLAGS_LINUX = -g -Wall -Wstrict-prototypes -I/usr/X11R6/include
LDFLAGS_LINUX = -g
LIBS_LINUX = $(LIBS_LINUX_$(LOCATION))
LIBS_LINUX_TRICITIES = \
	-L/usr/X11R6/lib \
	-lglut \
	-lGLU -lGL \
	-lpthread \
	-lm
LIBS_LINUX_PULLMAN = \
	-L/usr/X11R6/lib \
	-lglut \
	-lGLU -lGL \
	-lXext -lXmu -lXi -lX11 \
	-lpthread \
	-lm

LD = $(CC)

# ------

SRCS = \
	$(wildcard *.c)

OBJS = $(SRCS:.c=.o)

default: $(PROG)

clean:
	rm -f $(PROG) a.out core core.* $(OBJS) *~ *.bak

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG) $(LIBS)
