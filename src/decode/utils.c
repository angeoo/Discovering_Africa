#include "utils.h"
#include "masking.c"
#include "parse.c"
#include "prints.c"
#include "data_encodation.c"
#include "qr.c"


int GiveVersion(int len)
{
	int version;
	printf("len = %i\n",len);


	if(len<=17)
	{
		return 1;
	}
	if(len<=32)
	{
		return 2;
	}
	if(len<=53)
	{
		return 3;
	}
	if(len<=78)
	{
		return 4;
	}
	if(len<=106)
	{
		return 5;
	}
	if(len<=134)
	{
		return 6;
	}
	if(len<=154)
	{
		return 7;
	}
	if(len<=192)
	{
		return 8;
	}
	if(len<=224)
	{
		return 9;
	}
	if(len<=259)
	{
		return 10;
	}
	else
	{
		printf("Can't give you a version\n");
		return 0;
	}
}



	





typedef struct{
	int* mat;
	int size;
}tuple;

tuple* init_mat(int vers) {

	int size =(4*vers)+17;

	int* ret = calloc(size*size,sizeof(int));


	int find[7][7] = {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0,
		1, 1, 1, 0, 1}, {1, 0, 1, 1, 1, 0, 1}, {1, 0, 1, 1, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1}};

	int alli[5][5]= {{1,1,1,1,1}, {1,0,0,0,1}, {1,0,1,0,1}, {1,0,0,0,1},
		{1,1,1,1,1}};

	//haut-gauche find
	for(int x=0;x<7;x++) 
	{	
		for(int y =0;y<7;y++) 
		{
			ret[y*size+x]=find[y][x];
		}
	}
	// bas-gauche find
	for(int x=0;x<7;x++)
	{
		for(int y=0;y<7;y++)
		{
			ret[((size-y-1)*size) + x]=find[6-y][x];
		}
	}
	//haut-droit
	for(int x=0;x<7;x++) 
	{ 
		for(int y=0;y<7;y++)
		{
			ret[y*size +(size-7+x)] = find[y][x];
		}
	}


	//timing patter
	for(int e =8;e<size-9;e++)
	{
		if(e%2==0)
		{
			ret[6*size + e]=1;
			ret[e*size + 6]=1;
		}
		else
		{
			ret[6*size + e]=0;
			ret[e*size + 6]=0;
		}
	}


	if(vers>=2)
	{
		int init =size-9;
		if(vers<7)
		{
			for(int x=0;x<5;x++)
			{
				for(int y=0;y<5;y++) 
				{
					ret[(init+y)*size + (init+x)]=alli[y][x]; 
				}
			}
		}
		else
		{
			for(int x=0;x<5;x++)
			{
				for(int y=0;y<5;y++) 
				{
					ret[(init+y)*size + (init-16+x)]=alli[y][x];
					ret[(init-16+y)*size + (init+x)]=alli[y][x];
					ret[(init-16+y)*size + (init-16+x)]=alli[y][x];
					ret[(init-32+y)*size + (init+x-16)]=alli[y][x];
					ret[(init-16+y)*size + (init-32+x)]=alli[y][x]; 
				}
			}	

		}
	}


	tuple* retu = malloc(sizeof(tuple));
	retu->mat = ret;
	retu->size=size;
	return retu;


}

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
				if (((x<8)&&(y<8))||((x<8)&&(y>=taille-8))||((x>=taille-8)&&(y<8)))
				{
					res[x*taille+y]=-1;
				}
				if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 )) || (x==taille-8 && y==8))
				{
					res[x*taille+y]=-2;
					count+=1;
				}
				if(((x==8)&&(( y<=8 && y!=6) || (y>=taille-8))) || ((y==8)&&(x>=taille-7 || x<=8)&& x!=6))
				{
					res[x*taille + y]=-3;
				}



			}

		}
	}
	else
	{
		if(taille<44)
		{

			for (size_t x = 0 ; x<taille ; x +=1)
			{
				for (size_t y = 0; y<taille ; y+=1)
				{

					res[x*taille+y]=matrice[x*taille+y];
					if (((x<8)&&(y<8))||((x<8)&&(y>=taille-8))||((x>=taille-8)&&(y<8)))
					{
						res[x*taille+y]=-1;
					}
					if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 ))||(((x>=taille-9)&&(x<taille-4))&&((y>=taille-9)&&(y<taille-4)))|| (x==taille-8 && y==8))
					{
						res[x*taille+y]=-2;
						count+=1;
					}
					if(((x==8)&&(( y<=8 && y!=6) || (y>=taille-8))) || ((y==8)&&(x>=taille-7 || x<=8)&& x!=6))
					{
						res[x*taille + y]=-3;
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
					res[x*taille +y ]=matrice[x*taille+y];
					if (((x<8)&&(y<8))||((x<8)&&(y>=taille-8))||((x>=taille-8)&&(y<8)))
					{
						res[x*taille + y] = -1;

					}
					if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 ))||(((x>=taille-9)&&(x<taille-4))&&((y>=taille-9)&&(y<taille-4)))|| (x==taille-8 && y==8) || ( (x<=taille-21 && x>=taille-25) &&
								((y<=taille-5 && y>=taille-9) || (y<=taille-21 && y>=taille-25) || (y<=taille-37 && y>=taille-41)  )) || ( (y<=taille-21 && y>=taille-25) && ( (x<=taille-37 && x>=taille-41) || (x<=taille-5 && x>=taille-9))  ))
					{
						res[x*taille + y]=-2;
					}
					if(((x==8)&&(( y<=8 && y!=6) || (y>=taille-8))) || ((y==8)&&(x>=taille-7 || x<=8)&& x!=6))
					{
						res[x*taille + y]=-3;

					}

				}
			}

		}
	}

	return res;

}








int main (int argc, char *argv[])
{

<<<<<<< Updated upstream
	init_sdl();
	if (argc!=2)
	{
		errx(1,"arguments not 2\n");
	}
	if (strcmp(argv[1],"1")!=0)
	{
		SDL_Surface *qr=load_image(argv[1]);
		int w=qr->w;
		int size = module_size(qr);
		int* data = QR(qr,size);
		int* data_matrix=mat_data(data,w/size);
		Rmask(data_matrix,w/size,data);
=======
	FILE *file = freopen("filename.txt","w",stdout);

    init_sdl();
    if (argc!=2)
    {
        errx(1,"arguments not 2\n");
    }
    if (strcmp(argv[1],"1")!=0)
    {
        SDL_Surface *qr=load_image(argv[1]);
        int w=qr->w;
        int size = module_size(qr);
        int* data = QR(qr,size);
        int* data_matrix=mat_data(data,w/size);
        Rmask(data_matrix,w/size,data);
>>>>>>> Stashed changes

		//get QR code
		getQRcode(data_matrix,w/size);
	}
	else
	{

		//creer une matrice
		//int* created = creer_matric();
		//ajouter les neg
		//int* negcreated = mat_data(created,21);

		//getting the word as a string
		printf("enter your word :  ");
		char* word  = malloc(sizeof(char)*100);
		scanf("%s",word);
		printf("calulating len\n");
		getchar();
		//calculating the len
		int c=0;
		while(word[c]!='\0')
		{
			c=c+1;
		}
		printf("getting the version\n");
		getchar();
		//get the version of the QR code
		int version = GiveVersion(c);
		//totals is the len og the string
		printf("getting the total of the len\n");
		getchar();
		int totals =8 * c + 12;
		
		//create the Qr code matrix according to version
		printf("initmat with the version got\n");
			
		printf("version = %i \n",version );
		getchar();
		tuple* cleanmat = init_mat(version);
		//create the negative matrix
		printf("creating the negative matrix\n");
		getchar();
		int* negcreated = mat_data(cleanmat->mat,cleanmat->size );

		//qr size is
		printf("geting the size og the clean mat"); 
		int size = cleanmat->size;


		//Fill up the bitstream with the word
		int* res2 = BitStream(word);
		int* county = malloc(sizeof(int));
		*county = 0;
		int* res = pad_codewords(res2,totals,county);
		//updating the len of the bitstream
		totals += *county*8;

		//Filling the QR code
		putQRcode(negcreated,size,res,totals);

		//Retrieving the info
		getQRcode(negcreated,size);

		//creer matrice vide
		tuple* finres = init_mat(version) ;

		//enlever les negatifs
		RemoveNeg(negcreated , finres->mat,finres->size);

		//imprimer la matrice
		getchar();

		NoParsePrint(finres->mat,size);




<<<<<<< Updated upstream
	//	free(created);
		free(negcreated);
		free(word);
		//free(data);
		//free(data_matrix);
	}

=======
        free(created);
        free(negcreated);
        free(word);
        //free(data);
        //free(data_matrix);
    }
	fclose(file);
>>>>>>> Stashed changes
}
