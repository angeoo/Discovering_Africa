#include "utils.h"


int module_size(SDL_Surface * surface)
{
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	int j=0;
	for (; j<h ; j++)
	{
		pixel=getpixel(surface, 2,j);
		SDL_GetRGB(pixel,surface->format,&r,&g,&b);
		if (r==255)
			break;
	}
	printf(" fpl : %d\n",j);
	int mod_size=0;
	for(int k=0;k<w;k++)
	{
		pixel=getpixel(surface,k,j/2);
		SDL_GetRGB(pixel,surface->format,&r,&g,&b);
		if (r==255)
		{
			mod_size=k;
			break;
		}
	}
	return mod_size;
}

int* QR(SDL_Surface *surface, int mod_size)
{
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	int size=(int)(w/mod_size)*(int)(w/mod_size);
	int* mat=calloc(size,sizeof(int));
	
	/*qr *qr;
	qr->matrix=mod;
	qr->size=qr_size*qr_size;
	qr->v=(qr_size-21)/4; //arithmetic formulas
*/

	int ix=0;
	for (int i=0; i<h && ix<w/mod_size ; i+=mod_size && ix++)
	{
		int iy=0;
		for (int j=0; j<w && iy<w/mod_size; j+=mod_size && iy++)
		{
			pixel=getpixel(surface,i/2,j/2);
			SDL_GetRGB(pixel,surface->format,&r,&g,&b);
			if (r==0)
				*(mat+(ix*(w/mod_size)+iy))=1;
		}
	}

	return mat;
}

int main (int argc, char *argv[])
{
	if (argc!=2)
		errx(1,"too many arguments");
	init_sdl();
	SDL_Surface *qr=load_image(argv[1]);
	int w=qr->w;
	int size = module_size(qr);
	printf("mod_size : %d\n", size);
	int* data = QR(qr,size);
	int k=0;
	for (int i =0; i<w/size; i++)
	{
		for (int j=0; j<w/size;j++)
		{
			k++;
			printf("%dth module color: %d\n",k, *(data+(i*(w/size))+j));
		}
	}

	free(data);

	return 0;
}
