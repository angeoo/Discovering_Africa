#include "pixel_operations.h"
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <err.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>

SDL_Surface* digitToSdl(char *str,SDL_Color c);
void fillgrid(SDL_Surface* output,int *res, int size);

