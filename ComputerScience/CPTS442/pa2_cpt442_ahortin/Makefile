PROG = maze

LIBS = \
	-lglut

CC = cc

CFLAGS = -g -Wall -Wstrict-prototypes

EXPORTABLES = Makefile $(HDRS) $(SRCS)

SRCS = \
	main.c 

OBJS = $(SRCS:.c=.o)

all: $(PROG)


clean:
	rm -f $(PROG) a.out core $(OBJS) *~ *.bak

tarball: $(PROG).tgz

$(PROG).tgz: $(EXPORTABLES)
	cd ..; tar -cvzf $(PROG)/$(PROG).tgz $(EXPORTABLES:%=$(PROG)/%)

$(OBJS): $(HDRS)

$(PROG): $(OBJS)
	cc $(CFLAGS) -o $@ $^ $(LIBS)

rcsupdate:
	ci -l Makefile $(MANHDRS) $(MANSRCS) $(FDFILES)
