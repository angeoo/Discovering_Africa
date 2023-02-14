CC = gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Werror -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS=-lm -lSDL_ttf -lSDL_gfx `pkg-config --libs sdl SDL_image` -export-dynamic

all: decode user image
.PHONY : decode user image

decode:
	cd src/decode  && ${MAKE}

user:
	cd user_test && ${MAKE}

image:
	cd image && ${MAKE}

clean:
	(cd src/decode; make clean)
	(cd user_test; make clean)
	(cd image; make clean)

re: clean all

.PHONY: all clean re
