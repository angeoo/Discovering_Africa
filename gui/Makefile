CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -Wall -Wextra -rdynamic
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = gui.c signals.c

OBJS = $(SRC:.c=.o)

all: exampleapp

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

exampleapp: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS) -rdynamic
	./exampleapp
	make clean

clean:
	rm -f $(OBJS)
	rm -f exampleapp
