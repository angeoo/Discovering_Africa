CC = gcc
CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS=-lm -lSDL_ttf -lSDL_gfx `pkg-config --libs sdl SDL_image`

utils:utils.o

utils.o:utils.c utils.h masking.c masking.h


clean:
	${RM} *.o
	${RM} *.d
	${RM} utils

#END

