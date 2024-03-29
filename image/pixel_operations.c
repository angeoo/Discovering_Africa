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

SDL_Surface* digitToSdl(char *str,SDL_Color c){
	TTF_Init();
	TTF_Font* police = NULL;
	police = TTF_OpenFont("fonts/Inter-Medium.ttf",40);

	//SDL_Color noir = {255,255,255,255};
	SDL_Surface *texte = TTF_RenderText_Blended(police,str,c);

	texte = zoomSurface(texte,1,1,0);

	TTF_CloseFont(police);
	TTF_Quit();

	return texte;
}


void fillgrid(int *res, int size){
	
	SDL_Surface *output = SDL_CreateRGBSurface(0,400,400,32,0,0,0,0);

	SDL_Color c= {0,0,0,0};
	char s[] = "x";
	int tmp;

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			tmp = res[i*size+j];
			s[0] = '0'+tmp;
			
			SDL_Rect cube = {5+j*54,15+i*54,54, 54};
			SDL_Surface* outcube = digitToSdl(s,c);
			cube.w = outcube->w;
			cube.h = outcube->h;
			int test = SDL_BlitSurface(outcube,NULL,output,
					&cube);
			if(test==1){
				printf("%d",cube.x);
				printf("error\n");
			}
		}
	}

	SDL_SaveBMP(output,"sdl_encode.bmp");
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

void draw_module(SDL_Surface *output, int i, int j, Uint32 pixel, int m){

	for(int x=i;x<i+m;x++){
		for(int y=j;y<j+m;y++){
			put_pixel(output,y,x,pixel);
		}
	}

}

// mat[i*size+j] matrice de 0 et de 1 a tranformee en qr code
// 1 : noir | 0 : blanc
// size : nb cols
// filename : nom du fichier image .bmp 
// m : version du qr code
void new_image(int* mat, int size, char* filename, int m){

	SDL_Surface *output = SDL_CreateRGBSurface(0,size*m,size*m,32,0,0,0,0);

	Uint32 black,white;
	black = SDL_MapRGB(output->format,0,0,0);
	white = SDL_MapRGB(output->format,255,255,255);


	for(int u=0;u<size;u++){
		for(int v=0;v<size;v++){
			if(mat[u*size+v]==1){
				draw_module(output,u*m,v*m,black,m);
			}
			else
				draw_module(output,u*m,v*m,white,m);

		}
	}

	SDL_SaveBMP(output,filename);
}
