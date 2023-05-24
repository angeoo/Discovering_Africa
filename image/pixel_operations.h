#ifndef PIXEL_OPERATIONS_H_
#define PIXEL_OPERATIONS_H_

#include <stdlib.h>
#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "pixel_operations.h"




SDL_Surface* digitToSdl(char *str,SDL_Color c);
void fillgrid(int *res, int size);

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen, SDL_Surface* image);
void draw_module(SDL_Surface *output, int i, int j, Uint32 pixel, int m);
void new_image(int* mat, int size, char* filename, int m);
#endif
