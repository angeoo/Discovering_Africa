CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -rdynamic
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)


all: decode user image
.PHONY : decode user image

image:
	cd ../image && ${MAKE}

decode:
	cd ../src/decode  && ${MAKE}

user:
	cd ../user_test && ${MAKE}

SRC =  signals.c gui.c

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
	(cd ../src/decode; make clean)
	(cd ../user_test; make clean)
	(cd ../image; make clean)


