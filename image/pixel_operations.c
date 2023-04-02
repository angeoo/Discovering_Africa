// Simple get/put pixel for SDL
// Inspired by code from SDL documentation
// (http://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html)

#include <err.h>
#include "pixel_operations.h"

static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void draw_module(SDL_Suface *output, int i, int j, Uint32 pixel, int m){

	for(int x=i;x<m;x++){
		for(int y=j;y<m;y++){
			put_pixel(output,x,y,pixel);
		}
	}

}

// mat[i*size+j] matrice de 0 et de 1 a tranformee en qr code
// 1 : noir | 0 : blanc
// size : nb cols
// filename : nom du fichier image .bmp 
// m : version du qr code
void new_image(int* mat, int size, char* filename, int m){

	SDL_Surface *output = SDL_CreateRGBSurface(0,size,size,32,0,0,0,0);

	Uint32 black,white;
	black = SDL_MapRGB(output->format,0,0,0);
	white = SDL_MapRGB(output->format,255,255,255);

	int ox = 0;
	int oy = 0;

	for(int u=0;u<size;u++){
		for(int v=0;v<size;v++){
			if(mat[u*size+v]==1){
				draw_module(output,u*m,v*m,black,m);
			}

			draw_module(out,u*m,v*m,white,m);

		}
	}

	SDL_SaveBMP(output,filename);
}
