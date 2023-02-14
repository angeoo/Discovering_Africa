#include "masking.c"


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
				if (((x<9)&&(y<9))||((x<9)&&(y>=taille-8))||((x>=taille-8)&&(y<9)))
				{
					res[x*taille+y]=-1;
				}
				if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 )))
				{
					res[x*taille+y]=-2;
					count+=1;
				}
			}

		}
		printf("%d \n",count);
	}
	else
	{

		for (size_t x = 0 ; x<taille ; x +=1)
		{
			for (size_t y = 0; y<taille ; y+=1)
			{

				res[x*taille+y]=matrice[x*taille+y];
				if (((x<9)&&(y<9))||((x<9)&&(y>=taille-8))||((x>=taille-8)&&(y<9)))
				{
					res[x*taille+y]=-1;
				}
				if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 ))||(((x>=taille-9)&&(x<taille-4))&&((y>=taille-9)&&(y<taille-4))))
				{
					res[x*taille+y]=-2;
					count+=1;
				}


			}

		}
		printf("%d \n",count);
	}
	return res;

}


int calc(int* block,int nb) //donne le decimal dun block decode a partir dun pointerur
{
	int len = 1;
	int res =0;
	int e=0;
	block =block-1;
	while(e<nb-1)
	{
		if( *block ==1)
		{
			res=res+len;
		}
		len=len*2;
		block=block-1;
		e=e+1;
	}


	if(*block ==1 )
	{
		res=res+len;
	}
	return res;
}



int getencode(int taille , int* mat,int nb,int x ,int y)
{
	int res;
	int xcst = x;
	int* form = malloc(4*sizeof(int));
	while(x>xcst-(nb/2))
	{
		*form = mat[x*taille + y];
		form=form+1;
		*form = mat[x*taille + (y-1)];
		form=form+1;
		x=x-1;
	}
	res = calc(form , nb);
	return res;
}




void _getup(int* mat , int* posx , int* posy,int* res, int n)
{
	int c=0;
	while(c<2)
	{
		if(mat[(*posx)*n + *posy]!=-2)
		{
			*res=mat[(*posx)*n + *posy];
			res = res +1;
			c=c+1;
		}
		*posy = *posy-1;

		if(mat[(*posx)*n + *posy]!=-2)
		{
			*res=mat[(*posx)*n+*posy];
			res=res+1;
			c=c+1;
		}
		*posy=*posy+1;
		*posx=*posx-1;
	}
	return;
}

void _getdown(int* mat , int* posx , int* posy , int*res, int n)
{
	int c=0;
	while(c<2)
	{
		if(mat[(*posx)*n + *posy]!=-2)
		{
			*res=mat[(*posx)*n + *posy];
			res=res+1;
			c=c+1;
		}
		*posy=*posy-1;
		if(mat[(*posx)*n + *posy]==-2)
		{
			*res=mat[(*posx)*n+*posy];
			res=res+1;
			c=c+1;
		}
		*posy=*posy+1;
		*posx=*posx+1;
		return;
	}
}


//////// Partie Brian

int getall(int* mat , int n , int totword ,int*  reso)

{
	int posx = n-1-6;
	int posy = n-1-6;

	int c = 0;
	while(c<totword*8)
	{
		while(posx!=0 || (mat[posx*n+(posy-1)]!=-1) && (c<totword*8))
		{
			_getup(mat,&posx,&posy,reso,n);
			c=c+2;
		}
		if(c<=totword*8)
		{
			*reso=mat[posx*n+posy];
			reso=reso+1;
			posy=posy-1;
			c=c+1;
		}
		if(c<=totword*8)
		{
			*reso=mat[posx*n+posy];
			reso=reso+1;
			posy=posy-1;
			c=c+1;
		}

		while(posx!=n-1 && c< totword*8)
		{
			_getdown(mat,&posx,&posy,reso,n);
			c=c+2;
		}
		if(c<=totword*8)
		{
			*reso=mat[posx*n+posy];
			reso=reso+1;
			posy=posy-1;
			c=c+1;
		}
		if(c<=totword*8)
		{
			*reso=mat[posx*n + posy];
			reso=reso+1;
			posy=posy-1;
			c=c+1;
		}
	}

	return 0 ;//calc(reso,8);
}


void getencodingmode(int res)
{
	printf("encoding mode is : ");
	if(res==7)
	{
		printf("ECI");
	}
	if(res==1)
	{
		printf("Numeric");
	}
	if(res==2)
	{
		printf("Alphanumeric");
	}
	if(res==4)
	{
		printf("8-bit Byte");
	}
	if(res==8)
	{
		printf("Kanji");
	}
	if(res==3)
	{
		printf("Structured Apped");
	}
		if(res==0)
	{
		printf("end of message");
	}
	printf("\n");
}
void getmsglen(int res)
{
	printf("The message is coded on %d codewords",res );
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

	//	int* res = getall(data_matrix,(int)w/size,3);
	//	printf("\n================================");
	//	for(int i =0 ; i<3*8;i++)
	//	{
	//		printf("bit %d = %d || \n",i,*res);
	//		res=res-1;
	//
	//
	//


	Rmask(data_matrix,w/size,data);
	int ress = getencode(21,data_matrix,4,(int)(w/size)-1,(int)(w/size)-1);
	getencodingmode(ress);
	int ress2 = getencode(21,data_matrix,8,(int)(w/size)-1-2,(int)(w/size)-1);
	getmsglen(ress2);

//	int* ress2 = (int*) malloc(2*8*sizeof(int));

//	int res = getall(data_matrix , 21 , 2 , ress2 );

//	printf("final resul = %d " , res);
//	for(int sa = 0 ; sa<53 ; sa++)
//	{

//		printf(" case(%d)  = %d ||\n" ,8-sa, *ress2 );
//		ress2=ress2-1;
//	}



	int k=-1;
	for (int i =0; i<w/size; i++)
	{
		for (int j=0; j<w/size;j++)
		{
			k++;
			if (k%21==0)
			{
			
				printf("\n");
				printf("\n");
			}
			if(*(data_matrix+(i*(w/size))+j)<0)
			{
			printf("|%d |", *(data_matrix+(i*(w/size))+j));
			}
			else
			{
			printf("| %d |", *(data_matrix+(i*(w/size))+j));
			}
		}
	}




	free(data);
	free(data_matrix);

}
