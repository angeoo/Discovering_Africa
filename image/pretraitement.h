#include "pixel_operations.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


void init_sdl();
SDL_Surface* load_image(char*path);
SDL_Surface* grayscale(SDL_Surface* img);
void image(SDL_Surface * img);


