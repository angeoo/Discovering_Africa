#include "utils.h"


int module_size(SDL_Surface * surface)
{
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
	return mod_size;
}

int QR(SDL_Surface *surface, int mod_size)
{
	int h=surface->h, w=surface->w;
	Uint32 pixel;
	Uint8 r,g,b;
	int qr_size=0;
	for (int i=0; i<h ; i+=mod_size)
		qr_size+=i;
	mod mod[qr_size][qr_size];
	qr *qr;
	qr->matrix=mod;
	qr->size=qr_size*qr_size;
	qr->v=(qr_size-21)/4; //arithmetic formulas


	/*r (int i=0; i<h ; i++)
	{
		for (int j=0; j<w; j+=mod_size)
		{
			pixel=getpixel(surface,i,j);
			SDL_GetRGB(pixel,surface->format,&r,&g,&b);
			if (r==0)
			{*/
	return qr->v;
}

int main (int argc, char **argv )
{
	if (argc!=2)
		errx(1,"too many arguments");
	init_sdl();
	SDL_image *qr=load_image(argv[1]);
	int mod_size=module_size(qr);

