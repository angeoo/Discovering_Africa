#ifndef FILLGRID_H_
#define FILLGRID_H_

#include <SDL/SDL_ttf.h>
#include <stdio.h>

void writeOnSdl(char str[]);
Uint32 ColourToUint(int r,int g,int b);
SDL_Colour UintToColour(Uint32 colour);
SDL_Surface* recreate();
void loadarray(char* filename,int grid[]);
SDL_Surface* digitToSdl(char* str,SDL_Color c);
void fillgrid(SDL_Surface* out,int grid[], int res[]);

#endif
