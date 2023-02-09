#include "utils.h"


SDL_Surface *Rmasking(SDL_Surface surface,QR qr, char *mask)
{
	int w=surface->w , h=surface->h;
	for (int i=0; i<w; i++)
	{
		for (int j=0;j<h;j++)
		{
			if (i<7*qr.modul_size && j<7*q.modul_size)
				continue;
			if (i==7*qr.module_size)
				continue;
			if (j==7*qr.module_size)
				continue;
			if (i<w-7*qr.module_size && j<h-7*qr.module_size)
				continue;
			if (i<7*qr.modul_size && y>h-7*qr.module_size)
				continue;
			if 


