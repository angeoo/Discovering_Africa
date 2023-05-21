#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL_rotozoom.h>
#include "fillGrid.h"
#include "pixel_operations.h"

Uint32 ColourToUint(int R, int G, int B)
{
	return (Uint32)((R << 16) + (G << 8) + (B << 0));
}

SDL_Colour UintToColour(Uint32 colour)
{
	SDL_Color tempcol={255,(colour >> 16) & 0xFF,
		(colour >> 8) & 0xFF,colour & 0xFF};
	return tempcol;
}

SDL_Surface* recreate(){
	SDL_Surface *res = SDL_CreateRGBSurface(0,486,503,32,0,0,0,0);
	if(res==NULL){
		printf("SDL_CreateRGBSurface failed");
		return NULL;
	}

	Uint32 blanc = ColourToUint(255,255,255);

	for(int i=0;i<res->w;i+=54){
		for(int j=0;j<res->h;j++){
			put_pixel(res,i,j,blanc);
			if(i%162==0 && i-2>0 && i+2<res->w){
				put_pixel(res,i-2,j,blanc);
				put_pixel(res,i-1,j,blanc);
				put_pixel(res,i+1,j,blanc);
				put_pixel(res,i+2,j,blanc);
			}
		}
	}
	for(int j=0;j<res->h;j++){
		put_pixel(res,-1+res->w,j,blanc);
	}
	for(int i=0;i<res->w;i++){
		for(int j=0;j<res->h;j+=57){
			put_pixel(res,i,j,blanc);
			if(j%171==0 && j-2>0 && j+2<res->w){
					put_pixel(res,i,j-2,blanc);
					put_pixel(res,i,j-1,blanc);
					put_pixel(res,i,j+1,blanc);
					put_pixel(res,i,j+2,blanc);
			}
		}
	}

	for(int i=0;i<res->w;i++){
		put_pixel(res,i,-1+res->h,blanc);
	}



	return res;
}

void loadarray(char *filename, int grid[]){
	FILE *fp;
	fp = fopen(filename,"r");
	int i=0;
	int j=0;
	char charac;
	while((charac=fgetc(fp))!=EOF){
		if(charac != ' '){
			if(charac == '\n'){
				j=0;
				i++;
			}
			else if(charac == '.'){
				grid[9*i+j] = 0;
				j++;
			}
			else{
				grid[9*i+j] = charac - '0';
				j++;
			}
		}
	}
	fclose(fp);
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

void fillgrid(SDL_Surface* output,int *res, int size){
	SDL_Color blanc= {255,255,255,0};
	SDL_Color c=blanc;
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
}



int main(int argc, char* argv[]){
		
		SDL_Surface *output = recreate();
		
		fillgrid(output,mat,21);
		SDL_SaveBMP(output,"sdl_soluce.bmp");
		return 0;

}
