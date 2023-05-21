CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MD
CFLAGS= -Wall -Wextra
LDLIBS= -lm -lSDL_ttf -lSDL_gfx `pkg-config --libs sdl SDL_image` -export-dynamic

all:main
main : main.o pixel_operations.o pretraitement.o

display : pixel_operations.o

pixel_operations.o : pixel_operations.h
pretraitement.o: pixel_operations.o pretraitement.h 

display.o:pixel_operations.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} main
	${RM} display
	${RM} output.bmp

#END
