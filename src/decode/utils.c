#include "utils.h"
#include "masking.h"
#include "parse.h"
#include "prints.h"
#include "data_encodation.h"
#include "qr.h"
//#include "../../image/pixel_operations.h"

void putformat(int* mat,int size , int* forinfo)
{
    mat[0*size+8] =forinfo[0];
    mat[1*size+8] =forinfo[1];
    mat[2*size+8] =forinfo[2];
    mat[3*size+8] =forinfo[3];
    mat[4*size+8] =forinfo[4];
    mat[5*size+8] =forinfo[5];
    mat[7*size+8]=forinfo[6];
    mat[8*size+size-1-0] =forinfo[0];
    mat[8*size+size-1-1] =forinfo[1];
    mat[8*size+size-1-2] =forinfo[2];
    mat[8*size+size-1-3] =forinfo[3];
    mat[8*size+size-1-4] =forinfo[4];
    mat[8*size+size-1-5] =forinfo[5];
    mat[8*size+size-1-6] =forinfo[6];
    mat[8*size+size-1-7] =forinfo[7];
    mat[8*size+8] =forinfo[7];
    mat[8*size+7] =forinfo[8];
    mat[8*size+5] =forinfo[9];
    mat[8*size+4] =forinfo[10];
    mat[8*size+3] =forinfo[11];
    mat[8*size+2] =forinfo[12];
    mat[8*size+1] =forinfo[13];
    mat[8*size+0] =forinfo[14];
    mat[(size-7)*size+8] =forinfo[8];
    mat[(size-6)*size+8] =forinfo[9];
    mat[(size-5)*size+8] =forinfo[10];
    mat[(size-4)*size+8] =forinfo[11];
    mat[(size-3)*size+8] =forinfo[12];
    mat[(size-2)*size+8] =forinfo[13];
    mat[(size-1)*size+8] =forinfo[14];
    



}

int GiveVersion(int len)
{
    int version;


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

    ret[(size-8)*size + 8]=1;

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
    for(int e =8;e<=size-9;e++)
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
                    ret[(init+y)*size + (init+x)]=alli[y][x]; //bas droit 
                    ret[(init+y)*size + (size/2 - 2 +x)]=alli[y][x]; //
                    ret[(size/2 -2 +y)*size + (init+x)]=alli[y][x];
                    ret[(size/2 -2+y)*size + (size/2 -2 +x)]=alli[y][x];
                    ret[(4+y)*size + (size/2 -2 +x)]=alli[y][x];
                    ret[(size/2 -2 +y)*size + (4 + x)]=alli[y][x]; 
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
        pixel=get_pixel(surface, 2,j);
        SDL_GetRGB(pixel,surface->format,&r,&g,&b);
        if (r==255)
            break;
    }
    int mod_size=0;
    for(int k=0;k<w;k++)
    {
        pixel=get_pixel(surface,k,j/2);
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
            pixel=get_pixel(surface,i,j);
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
                    if (((((x>7)&&(x<taille-8))&& y==6) ||(((y>7)&&(y<taille-8))&& x==6 ))||(((x>=taille-9)&&(x<taille-4))&&((y>=taille-9)&&(y<taille-4)))|| (x==taille-8 && y==8) || ( (x<=taille/2 +2 && x>=taille/2 -2) &&
                                ((y<=taille-5 && y>=taille-9) || (y<=taille/2 + 2 && y>=taille/2 -2) || (y<9 && y>=4)  )) || ( (y<=taille/2 +2  && y>=taille/2-2) && ( (x<9 && x>=4) || (x<=taille-5 && x>=taille-9))  ))
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

    if (strcmp(argv[1],"1")!=0)
    {
        SDL_Surface *qr=load_image(argv[1]);
        int w=qr->w;
        int size = module_size(qr);
        int* data = QR(qr,size);
        int* data_matrix=mat_data(data,w/size);
        Rmask(data_matrix,w/size,data);
        getQRcode(data_matrix,w/size);
        printf("\n");
    }   
    else
    {
        //creer une matrice
        //int* created = creer_matric();
        //ajouter les neg
        //int* negcreated = mat_data(created,21);

        //getting the word as a string
        
	
	char* word  = argv[2];
	//calculating the len
        int c=0;
        while(word[c]!='\0')
        {
            c=c+1;
        }
        
	//get the version of the QR code
        int version = GiveVersion(c);
        //totals is the len og the string
        int totals =8 * c + 12;

        //create the Qr code matrix according to version

        tuple* cleanmat = init_mat(version);
        //create the negative matrix
        int* negcreated = mat_data(cleanmat->mat,cleanmat->size );

        //qr size is
        int size = cleanmat->size;

        //errorcorrectionlevel
        int ecl;
        //Fill up the bitstream with the word
        int* res2 = BitStream(word);
        int* county = malloc(sizeof(int));
        *county = 0;
        int* res = pad_codewords(res2,totals,county,&ecl);
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
        

        //get format info array
        int* finf = FormatInfo(ecl , 1);
        //put format info in the final matrix without negatives
        //Printing the negative 

        //applying mask to finres into negcreated
        Mask(negcreated,1,size);

  //create matrix to store the final masked mat in it

        tuple* maskqr = init_mat(version);
        putformat(maskqr->mat,size,finf);
        RemoveNeg(negcreated,maskqr->mat,size);





        //**************************************essayer masking



        //**************************************essayer masking
        printf("\nNo masking\n");
        NoParsePrint(finres->mat, size);
        printf("Masking\n");
        NoParsePrint(maskqr->mat, size);
        new_image(maskqr->mat,size,"mask.bmp",size);
        new_image(finres->mat,finres->size,"nomask.bmp",size);


        
        //free(created);
        //free(negcreated);
        //free(word);
        //free(data);
        //free(data_matrix);
    }
    return 0;
}
