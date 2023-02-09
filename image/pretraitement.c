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

size_t image(SDL_Surface * img){
	
	img = grayscale(img);

	SDL_SaveBMP("gray.bmp",img);
	int w = img->w;
	int h = img->h;


	printf("img->w : %d\nimg->h : %d\n\n\n\n\n",w,h);

	Uint32 pixel;
	Uint8 r,g,b;

	int coordh=0;
	int coordw=0;
	int i=0;
	int j=0;
	int on =1;
	while(i<w && on==1){
		while(j<h && on==1){
			pixel = get_pixel(img,i,j);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			if(r==0 && g==0 && b==0){
				coordw=i;
				coordh=j;
				on = 0;
			}
			j+=1;
		}
		i+=1;
	}

	printf("\ncoordw : %d\ncoordh : %d\n",coordw, coordh);


	int new_w = w-2*coordw;
	int new_h = h-2*coordh;

	SDL_Surface *output = SDL_CreateRGBSurface(0,new_w,new_h,32,0,0,0,0);
	SDL_SaveBMP(output,"blank.bmp");
	for(int u=coordw;u<new_w;u++){
		for(int v=coordh;v<new_h;v++){
			pixel = get_pixel(img,u,v);

			put_pixel(output,u-coordw,v-coordh,pixel);

		}
	}

	SDL_SaveBMP(output,"out.bmp");

	return 0;


}
