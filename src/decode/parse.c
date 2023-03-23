#include <stdio.h>
#include <stdlib.h>



typedef struct
{
	int x; 
	int y;
	int* resultat;
	int count;

}parser;


void printres(int* arrd,int till )
{
	printf("resultat = ");
	for(int e = 0 ; e<=till ; e++ )
	{
		printf(" e= %i -> %i",e,arrd[e]);
	}
	printf("\n");
}




void getup(parser* w,int* arrd  ,int tot,int qrsize)
{
	while (w->y>0 && arrd[(w->y)*qrsize+ w->x]!=-1 && w->count!=tot)
	{
		int tmp = arrd[(w->y)*qrsize+ w->x];
		if(tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i  | count = %i  => res = %i\n",w->x , w->y ,w->count, tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			w->resultat[w->count]=tmp;
			w->count = w->count +1 ;
			arrd[(w->y)*qrsize+(w->x)]= 8;
			if (w->count==tot)
			{
				break;
			}
			w->x=w->x-1;
			tmp = arrd[(w->y)*qrsize+w->x];
			if (tmp!=-2)
			{
				//getchar();
				printf("x = %i | y = %i  | count = %i => res = %i\n",w->x , w->y ,w->count ,  tmp);
				//Prettprint(arrd , qrsize , *x ,*y );
				w->resultat[w->count]=tmp;
				w->count = w->count + 1 ;
				arrd[(w->y)*qrsize+w->x] = 8;
			}
			w->x= w->x + 1;
			w->y = w->y -1;
		}
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
		if(tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i | count = %i => res = %i\n",w->x , w->y , w->count,tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			w->resultat[w->count]=tmp;
			w->count = w->count +1 ;
			arrd[(w->y * qrsize) + w->x] = 8;
			if (w->count==tot)
			{

				break;
			}

		}
		w->x=w->x-1;
		tmp = arrd[(w->y * qrsize)+w->x];

		if (tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i | count = %i => res = %i \n",w->x , w->y ,w->count ,  tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			w->resultat[w->count]=tmp;
			w->count = w->count + 1 ;
			arrd[(w->y * qrsize ) + w->x] = 8;	

		}
		w->x=w->x+1;
		w->y = w->y +1;
	}
	w->y = w->y -1;
	w->x = w->x-2;
	return ;

}


void Prettprint(int* arrd,int qrsize,int i , int j)
{

	for(int y =0 ; y<qrsize; y++)
	{
		for(int x = 0 ;x < qrsize ; x ++)
		{
			int res = arrd[(y*qrsize)+x];
			if(res<0)
			{
			
				if(res == -2)
				{
					printf("\x1b[31m%i\x1b[0m", res);
				}
				else
				{
					printf("\x1b[34m%i\x1b[0m",res);
				}
			}
			else
			{
				if(i ==x && j == y )
				{

					printf("\x1b[32m %i\x1b[0m",res);
				}
				else
				{
					printf(" %i",res);
				}
			}


		}
		printf("\n");
	}
	return ; 

}

int* getall( int* arrd , int tot, int qrsize)
{

	parser mypars;
	mypars.x = qrsize-1;
	mypars.y = qrsize-1;
	mypars.resultat = malloc(tot*sizeof(int));
	mypars.count = 0 ;

	getup(&mypars,arrd,4,qrsize);
	mypars.y=mypars.y-1;
	mypars.x= mypars.x+2;
	

	while (mypars.count!=tot)
	{
		getup(&mypars,arrd,tot,qrsize);

		getdown(&mypars,arrd,tot,qrsize);

	}
	printf ("Last x = %i || Last y = %i \n",mypars.x ,mypars.y );
	return mypars.resultat;





}


int bintoint(int* read , int start , int len )
{
	int c= 1 ;
	int res = 0 ; 

	for(int e =start; e<start+len ; e++)
	{
		res = res + c*read[e];
		c=c+1;

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
	printf("\n");
}







