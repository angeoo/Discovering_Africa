#include "pretraitement.h"
#include "pixel_operations.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <err.h>
#include <SDL/SDL_image.h>

void init_sdl(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		err(EXIT_FAILURE,"Could not initialize SDL    : %s»···.\n",
				SDL_GetError());
}


SDL_Surface* load_image(char *path)
{
	SDL_Surface *img;
	img = IMG_Load(path);
	if (!img)
		errx(3, "can't load %s: %s", path, IMG_GetError());
	return img;
}

SDL_Surface* grayscale(SDL_Surface* img){
	
	Uint32 pixel,new_pixel;
	Uint8 r,g,b,av;
	Uint8 av_moy=127;

	for(int i=0;i<img->w;i++){
		for(int j=0;j<img->h;j++){
			pixel = get_pixel(img,i,j);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			av = 0.3*r+0.59*g+0.11*b;
		
			if(av<=av_moy){
				av=0;
			}
			else{
				av=255;
			}
			new_pixel = SDL_MapRGB(img->format,av,av,av);

			put_pixel(img,i,j,new_pixel);
		}
	}

	return img;
}

void image(SDL_Surface * img){
	
	img = grayscale(img);

	int w = img->w;
	int h = img->h;



	Uint32 pixel;
	Uint8 r,g,b;

	int coordh=0;
	int coordw=0;
	int i=0;
	int j=0;
	int on =1;
	while(i<w && on==1){
		j=0;
		while(j<h && on==1){
			pixel = get_pixel(img,i,j);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			if(r==0){
				coordw=i;
				coordh=j;
				on = 0;
			}
			j+=1;
		}
		i+=1;
	}

	int new_w = w-2*coordw;
	int new_h = h-2*coordh;

	printf("w : %d et h : %d\nnew_w : %d et new_h : %d\n",w,h,new_w,new_h);
	SDL_Surface *output = SDL_CreateRGBSurface(0,new_w,new_h,32,0,0,0,0);

	Uint32 black = SDL_MapRGB(img->format,0,0,0);
	Uint32 white = SDL_MapRGB(img->format,255,255,255);
	
	for(int u=coordw;u<new_w+coordw-1;u++){
		for(int v=coordh;v<new_h+coordh-1;v++){
			pixel = get_pixel(img,u,v);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			if(r==0){
				put_pixel(output,u-coordw,v-coordh,black);
			}
			else{
				put_pixel(output,u-coordw,v-coordh,white);
			}
		}
	}

	SDL_SaveBMP(output,"output.bmp");
	free(output);

}
