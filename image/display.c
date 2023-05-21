#include "display.h"
#include "pixel_operations.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <err.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>

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

void fillgrid(SDL_Surface* output,int *res, int size){
	SDL_Color c= {0,255,255,0};
	char s[] = "x";
	int tmp;

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			tmp = res[i*size+j];
			s[0] = '0'+tmp;
			
			SDL_Surface* outcube = digitToSdl(s,c);
			SDL_Rect cube = {5+j*54,5+i*54,54, 54};
			//SDL_Rect cube = {i*(1+size),j*(1+size),size,size};
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
}

int main(int argc, char[] argv){

	if(argc!=2){
		printf("display.c : error argument");
		return;
	}

	SDL_Surface *output = SDL_CreateRGBSurface(0,21*54,21*54,32,0,0,0,0);
	int *mat = calloc(21*21,sizeof(int));
	for(int i=0;i<21;i++){
		for(int j=0;j<21;j++){
			mat[i*21+j] = j%3;
		}
	}
	fillgrid(output,mat,21);

	SDL_SaveBMP(output,"fillgrid");
	free(mat);
	free(output);
	return 0;
}
