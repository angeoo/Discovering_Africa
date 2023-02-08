#include "pixel_operations.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>




size_t image(SDL_Surface * img){
	
	int w = img->w;
	int h = img->h;

	Uint32 pixel;
	Uint8 r,g,b;

	int coordx,coordy;

	for(int i=0;i<w;i++){
		for(int j =0;j<h;j++){
			pixel = get_pixel(img,i,j);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			if(r==0 && g==0&&b==0){
				coordx=i;
				coordy=j;
				break;
			}
		}
	}

	int new_w = w-coordx;
	int new_h = h-coordy;

	SDL_Surface *output = SDL_CreateRGBSurface(0,new_w,new_h,32,0,0,0,0);

	for(int i=0;i<new_w;i++){
		for(int j=0;j<h;j++){
			pixel = get_pixel(img,i+coordx,j+coordy);

			put_pixel(output,i,j,pixel);

		}
	}

	SDL_SaveBMP(output,"out.bmp");

	return 0;


}
