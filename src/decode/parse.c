#include <stdio.h>
#include <stdlib.h>
#include "parse.h"





void getup(parser* w,int* arrd  ,int tot,int qrsize)
{
	while (w->y>0 && arrd[(w->y)*qrsize+ w->x]!=-1 && w->count!=tot)
	{
		int tmp = arrd[(w->y)*qrsize+ w->x];
		getchar();
		if(tmp!=-2)
		{
			printf("x = %i | y = %i  | count = %i  => res = %i\n",w->x , w->y ,w->count, tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			Prettprint(arrd , qrsize , *w);
			w->count = w->count +1 ;
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
			Prettprint(arrd , qrsize , *w );
			w->count = w->count + 1 ;
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


	while (w->y<qrsize && arrd[(w->y * qrsize)+w->x]!=-1 && w->count!=tot)
	{
		int tmp = arrd[(w->y * qrsize) +w->x];
		getchar();
		if(tmp!=-2)
		{
			printf("x = %i | y = %i | count = %i => res = %i\n",w->x , w->y , w->count,tmp);
			w->resultat[w->count]=tmp;
			w->xs[w->count]=w->x;
			w->ys[w->count]=w->y;
			Prettprint(arrd , qrsize , *w );
			w->count = w->count +1 ;
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
			Prettprint(arrd , qrsize , *w );
			w->count = w->count + 1 ;
		}
		w->x=w->x+1;
		w->y = w->y +1;
	}
	w->y = w->y -1;
	w->x = w->x-2;
	return ;

}




void getall( int* arrd , int tot, int qrsize)
{

	//defining everything
	parser mypars;
	mypars.x = qrsize-1;
	mypars.y = qrsize-1;
	mypars.resultat = malloc(tot*sizeof(int));
	mypars.xs = malloc(tot*sizeof(int));
	mypars.ys = malloc(tot*sizeof(int));
	mypars.count = 0 ;
	mypars.tot = tot;

	//printing first
	Prettprint(arrd,qrsize,mypars);


	

	while (mypars.count!=tot)
	{
		getup(&mypars,arrd,tot,qrsize);

		getdown(&mypars,arrd,tot,qrsize);

	}
	printf ("Last x = %i || Last y = %i \n",mypars.x ,mypars.y );


	printf("bin to int %i",bintoint(mypars.resultat,0,4));




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







