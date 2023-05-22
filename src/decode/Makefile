CC = gcc
CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -w -Wall -Wextra -std=c99 -O3 -g 
LDFLAGS=
LDLIBS=-lm -lSDL_ttf -lSDL_gfx `pkg-config --libs sdl SDL_image`

utils:utils.o
initQR:../../image/pixel_operations.o initQR.o 

utils.o:utils.c masking.c parse.c prints.c data_encodation.c qr.c 
../../image/pixel_operations.o: ../../image/pixel_operations.h
initQR.o: ../../image/pixel_operations.o initQR.h 


clean:
	${RM} *.o
	${RM} *.d
	${RM} utils

#END

