CC = gcc
CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -w -Wall -Wextra -std=c99 -O3 -g 
LDFLAGS=
LDLIBS=-lm -lSDL_ttf -lSDL_gfx `pkg-config --libs sdl SDL_image`

utils:utils.h ../../image/pixel_operations.o utils.o masking.o parse.o prints.o data_encodation.o qr.o 
initQR:image/pixel_operations.o initQR.o 


../../image/pixel_operations.o: ../../image/pixel_operations.h
utils.o:utils.h masking.h parse.h prints.h data_encodation.h qr.h 
initQR.o: image/pixel_operations.o initQR.h 


clean:
	${RM} *.o
	${RM} *.d
	${RM} utils
	${RM} nomask.bmp

	#${RM} mask.bmp
#END

