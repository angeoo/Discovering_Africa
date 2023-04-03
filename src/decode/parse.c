#include <stdio.h>
#include <stdlib.h>
#include "parse.h"





void getup(parser* w,int* arrd  ,int tot,int qrsize)
{
	while (w->y>0 && arrd[(w->y)*qrsize+ w->x]!=-1 && arrd[(w->y)*qrsize+ w->x]!=-3 && w->count!=tot)
	{
		int tmp = arrd[(w->y)*qrsize+ w->x];
		getchar();
		if(tmp!=-2)
		{
			printf("x = %i | y = %i  | count = %i  => res = %i\n",w->x , w->y ,w->count, tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			w->count = w->count +1 ;
			Prettprint(arrd , qrsize , *w);
			if (w->count==tot)
			{
				break;
			}
		}
		w->x=w->x-1;
		tmp = arrd[(w->y)*qrsize+w->x];
		getchar();
		if (tmp!=-2)
		{
			
			printf("x = %i | y = %i  | count = %i => res = %i\n",w->x , w->y ,w->count ,  tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			w->count = w->count + 1 ;
			Prettprint(arrd , qrsize , *w );
		}
		w->x= w->x + 1;
		w->y = w->y -1;
		
	}
	w->y = w->y +1;
	w->x=w->x-2;
	return ;

}

void getdown(parser* w ,int *arrd  , int tot,int qrsize)
{


	while (w->y<qrsize && arrd[(w->y * qrsize)+w->x]!=-1 && arrd[(w->y * qrsize)+w->x]!=-3 && w->count!=tot)
	{
		int tmp = arrd[(w->y * qrsize) +w->x];
		getchar();
		if(tmp!=-2)
		{
			printf("x = %i | y = %i | count = %i => res = %i\n",w->x , w->y , w->count,tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			w->count = w->count +1 ;
			Prettprint(arrd , qrsize , *w );



			if (w->count==tot)
			{

				break;
			}
		}
		w->x=w->x-1;
		tmp = arrd[(w->y * qrsize)+w->x];
		getchar();
		
		if(tmp!=-2)
		{
			printf("x = %i | y = %i | count = %i => res = %i \n",w->x , w->y ,w->count ,  tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			w->count = w->count + 1 ;
			Prettprint(arrd , qrsize , *w );
		}
		w->x=w->x+1;
		w->y = w->y +1;
	}
	w->y = w->y -1;
	w->x = w->x-2;
	return ;

}

void fixpos(parser* w)
{
	w->x = w->x+2;
	w->y = w->y-1;

}

void putup(parser* w,int* arrd  ,int tot,int qrsize)
{
    while (w->y>0 && arrd[(w->y)*qrsize+ w->x]!=-1 && arrd[(w->y)*qrsize+ w->x]!=-3 && w->count!=tot)
    {
        int tmp = arrd[(w->y)*qrsize+ w->x];
        getchar();
        if(tmp!=-2)
        {
            arrd[(w->y)*qrsize+w->x]=w->resultat[w->count];
            w->xs[w->count]=w->x;
            w->ys[w->count]=w->y;
            w->count = w->count +1 ;
            Prettprintv2(arrd,qrsize,*w);
            getchar();
            if (w->count==tot)
            {
                break;
            }
        }
        w->x=w->x-1;
        tmp = arrd[(w->y)*qrsize+w->x];
        if (tmp!=-2)
        {
            arrd[(w->y)*qrsize+w->x]=w->resultat[w->count];
            w->xs[w->count]=w->x;
            w->ys[w->count]=w->y;
            w->count = w->count + 1 ;
            Prettprintv2(arrd,qrsize,*w);

        }
        w->x= w->x + 1;
        w->y = w->y -1;

    }
    w->y = w->y +1;
    w->x=w->x-2;
    return ;
}
void putdown(parser* w ,int *arrd  , int tot,int qrsize)
{


    while (w->y<qrsize && arrd[(w->y * qrsize)+w->x]!=-1 && arrd[(w->y * qrsize)+w->x]!=-3 && w->count!=tot)
    {
        int tmp = arrd[(w->y * qrsize) +w->x];
        getchar();
        if(tmp!=-2)
        {
            arrd[(w->y)*qrsize+w->x]=w->resultat[w->count];
            w->xs[w->count]=w->x;
            w->ys[w->count]=w->y;
            w->count = w->count +1 ;
            Prettprintv2(arrd,qrsize,*w);
            getchar();
            if (w->count==tot)
            {

                break;
            }
        }
        w->x=w->x-1;
        tmp = arrd[(w->y * qrsize)+w->x];

        if(tmp!=-2)
        {
            arrd[(w->y)*qrsize+w->x]=w->resultat[w->count];
            w->xs[w->count]=w->x;
            w->ys[w->count]=w->y;
            Prettprintv2(arrd,qrsize,*w);
            w->count = w->count + 1 ;
        }
        w->x=w->x+1;
        w->y = w->y +1;
    }
    w->y = w->y -1;
    w->x = w->x-2;
    return ;

}

void putall(int* arrd , int tot , int qrsize, int* toput)
{
    //defining parse struct
    parser mypars;
    mypars.x = qrsize-1;
    mypars.y = qrsize-1;
    mypars.xs =(int*) malloc(tot*sizeof(int));
    mypars.ys =(int*) malloc(tot*sizeof(int));
    mypars.finalmsg = calloc(50,sizeof(char));
    mypars.resultat = toput;
    mypars.count =0;
    mypars.tot=tot;


    
    //printing first
    Prettprint(arrd,qrsize,mypars);

    while(mypars.count!=tot)
    {
        putup(&mypars,arrd,tot,qrsize);
        putdown(&mypars,arrd,tot,qrsize);
    }
    free(mypars.resultat);
    free(mypars.xs);
    free(mypars.ys);

    return;
}


void getall( int* arrd , int tot, int qrsize)
{
    //defining everything
    parser mypars;
    mypars.x = qrsize-1;
    mypars.y = qrsize-1;
    mypars.resultat =(int*) malloc(tot*sizeof(int));
    mypars.xs =(int*) malloc(tot*sizeof(int));
    mypars.ys =(int*) malloc(tot*sizeof(int));
    mypars.count = 0 ;
    mypars.tot = tot;

    //printing first
    Prettprint(arrd,qrsize,mypars);
    //getting the mode
    getup(&mypars,arrd,4,qrsize);
    fixpos(&mypars);
    //getting the character len
    getup(&mypars,arrd,12,qrsize);
    fixpos(&mypars);
    //calculating len
    int len = bintoint(mypars.resultat,4,8);
    mypars.lens=len;
    mypars.finalmsg = (char*) calloc(((len+1)*8),sizeof(char));
    mypars.finalmsg[len]='\0';
    int total = mypars.count+ 8*len ;
    mypars.ys = (int*) realloc(mypars.ys,total);
    mypars.xs = (int*) realloc(mypars.xs,total);
    mypars.tot=total;

    while (mypars.count!=total)
    {
        getup(&mypars,arrd,total,qrsize);

        getdown(&mypars,arrd,total,qrsize);

    }
    free(mypars.resultat);
    free(mypars.xs);
    free(mypars.ys);
    free(mypars.finalmsg);
    return ;
}




int bintoint(int* read , int start , int len )
{
	int c= 1 ;
	int res = 0 ; 

	for(int e =start+len-1; e>=start ; e--)
	{
		res = res + c*read[e];
		c=c*2;

	}
	return res;


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
	return;
}







