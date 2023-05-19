#include "../../image/pixel_operations.h"
#include "initQR.h"

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
    if (mat==NULL)
	    errx(1,"malloc()");
    int ix=0;
    for (int i=mod_size/2; i<h  && ix<(w/mod_size) ; i+=mod_size )
    {
        int iy=0;
        for (int j=mod_size/2; j<w && iy<(w/mod_size); j+=mod_size )
        {
            pixel=getpixel(surface,i,j);
            SDL_GetRGB(pixel,surface->format,&r,&g,&b);
            if (r==0){
                *(mat+(ix*(w/mod_size)+iy))=1;
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

    return res;

}

int main (int argc, char *argv[])
{

    init_sdl();
    if (argc!=2)
    {
        errx(1,"arguments not 2\n");
    }
    SDL_Surface *qr=load_image(argv[1]);
    int w=qr->w;
    int size=module_size(qr);
    int *data=QR(qr,size);
    //int *data_matrix=mat_data(data,w/size);
    for (int i=0; i<w/size; i++){
	    for (int j=0;j<w/size;j++){
		    if (data[i*w/size+j]<0)
			    printf("%d |",data[i*w/size+j]);
		    else
			    printf(" %d |",data[i*w/size+j]);
		    /*if (i==25)
			    printf("\n");*/
	    }
	    printf("\n");
    }
    new_image(data,21,"test.bmp",20);
    free(data);
    //free(data_matrix);

    return 0;
}
