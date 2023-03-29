#include "utils.h"
#include "masking.c"
#include "parse.c"
#include "prints.c"


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

	int ix=0;
	for (int i=mod_size/2; i<h && ix<(w/mod_size) ; i+=mod_size )
	{
		int iy=0;
		for (int j=mod_size/2; j<w && iy<(w/mod_size); j+=mod_size )
		{
			pixel=getpixel(surface,i,j);
			SDL_GetRGB(pixel,surface->format,&r,&g,&b);
			if (r==0){
				*(mat+(iy*(w/mod_size)+ix))=1;
			}
			iy++;
		}
		ix++;
	}

	return mat;
}


int* mat_data (int* matrice , size_t taille )
{
	int count=0;
	int* res = calloc(taille*taille, sizeof(int));
	if (taille<22)
	{
		for (size_t x = 0 ; x<taille ; x +=1)
		{
			for (size_t y = 0; y<taille ; y+=1)
			{
				res[x*taille+y]=matrice[x*taille+y];
				if (((x<7)&&(y<7))||((x<7)&&(y>=taille-7))||((x>=taille-7)&&(y<7)))
				{
					res[x*taille+y]=-1;
				}
				if (((((x>6)&&(x<taille-7))&& y==6) ||(((y>6)&&(y<taille-7))&& x==6 )))
				{
					res[x*taille+y]=-2;
					count+=1;
				}
			}

		}
	}
	else
	{

		for (size_t x = 0 ; x<taille ; x +=1)
		{
			for (size_t y = 0; y<taille ; y+=1)
			{

				res[x*taille+y]=matrice[x*taille+y];
				if (((x<7)&&(y<7))||((x<7)&&(y>=taille-7))||((x>=taille-7)&&(y<7)))
				{
					res[x*taille+y]=-1;
				}
				if (((((x>6)&&(x<taille-7))&& y==6) ||(((y>6)&&(y<taille-7))&& x==6 ))||(((x>=taille-9)&&(x<taille-4))&&((y>=taille-9)&&(y<taille-4))))
				{
					res[x*taille+y]=-2;
					count+=1;
				}


			}

		}
	}
	
	return res;

}








int main (int argc, char *argv[])
{
	if (argc!=2)
	{
		errx(1,"too many arguments");
	}
	init_sdl();
	SDL_Surface *qr=load_image(argv[1]);
	int w=qr->w;
	int size = module_size(qr);
	int* data = QR(qr,size);
	int* data_matrix=mat_data(data,w/size);

	Rmask(data_matrix,w/size,data);



	int tot = 100;
	getall(data_matrix,tot,w/size);

	



	free(data);
	free(data_matrix);

}
