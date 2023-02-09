#include "utils.h"


int module_size(SDL_Surface * surface)
{
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	int j=0;
	for (j; j<h ; j++)
	{
		pixel=getpixel(surface, j,2);
		SDL_GetRGB(pixel,surface->format,&r,&g,&b);
		if (r==255)
			break;
	}
	int mod_size=0;
	for(int k=0;k<w;k++)
	{
		pixel=getpixel(surface,j/2,k);
		SDL_GetRGB(pixel,surface->format,&r,&g,&b);
		if (r==0)
		{
			mod_size=k;
			break;
		}
	}
	return mod_size;
}

int** QR(SDL_Surface *surface, int mod_size)
{
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	int mat[(int)(w/mod_size)][(int)(w/mod_size)];
	int ix =0;
	int iy =0;
	for (int i=mod_size; i<h ; i+=mod_size && ix++)
	{	
		for(int j=mod_size;j<h;j+=mod_size && iy++){
			pixel = getpixel(surface,i-mod_size/2,j-mod_size/2);
			SDL_GetRGB(pixel,surface->format,&r,&g,&b);
			mat[ix][iy]= r;
		}
	}
	/*qr *qr;
	qr->matrix=mod;
	qr->size=qr_size*qr_size;
	qr->v=(qr_size-21)/4; //arithmetic formulas
*/

	
	/*r (int i=0; i<h ; i++)
	{
		for (int j=0; j<w; j+=mod_size)
		{
			pixel=getpixel(surface,i,j);
			SDL_GetRGB(pixel,surface->format,&r,&g,&b);
			if (r==0)
			{
	return qr->v;*/

	return mat;
}

int main (int argc, char *argv[])
{
	if (argc!=2)
		errx(1,"too many arguments");
	init_sdl();
	SDL_Surface *qr=load_image(argv[1]);
	int size = module_size(qr);

	int** data = QR(qr,size);

	return 0;
}
