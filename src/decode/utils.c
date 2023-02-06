#include "utils.h"


int module_size(SDL_Surface * surface)
{
	Qr qr;
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	for (int j=0; j<h ; j++)
	{
		pixel=getpixel(surface, j,2);
		SDL_GetRGB(pixel,surface->format,&r,&g,&b);
		if (r==125)
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
	qr.module_size=mod_size;
	qr.Wul=mod_size*7;
	qr.D=(w-Qr.Wul/2)-Wul/2;
	qr.V=((qr.D/mod_size)-10)/4;
	if (qr.V>6)
		qr.V=41;
	/* 1/ determiner version information
	 * 2/ determiner si ereur il y a et corrige
	 * 3/ retirer le masking 
	 *
	





