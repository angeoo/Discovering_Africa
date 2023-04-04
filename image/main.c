#include "pixel_operations.h"
#include "pretraitement.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <err.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	if(argc!=2){
		err(EXIT_FAILURE,"main : wrong argument");
	}

	init_sdl();
	SDL_Surface *img = load_image(argv[1]);

	image(img);
	return 0;
}
