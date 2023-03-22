#include <stdio.h>
#include <stdlib.h>


void printres(int* arrd,int till )
{
	printf("resultat = ");
	for(int e = 0 ; e<=till ; e++ )
	{
		printf(" e= %i -> %i",e,arrd[e]);
	}
	printf("\n");
}




void getup(int* x , int* y, int* resultat,int* arrd  ,int* count,int tot,int qrsize)
{
	while (*y>0 && arrd[(*y)*qrsize+ *x]!=-1 && *count!=tot)
	{
		int tmp = arrd[(*y)*qrsize+ *x];
		if(tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i  | count = %i  => res = %i\n",*x , *y ,*count, tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			resultat[*count]=tmp;
			*count = *count +1 ;
			arrd[(*y)*qrsize+(*x)]= 8;
			if (*count==tot)
			{
				break;
			}
			*x=*x-1;
			tmp = arrd[(*y)*qrsize+*x];
			if (tmp!=-2)
			{
				//getchar();
				printf("x = %i | y = %i  | count = %i => res = %i\n",*x , *y ,*count ,  tmp);
				//Prettprint(arrd , qrsize , *x ,*y );
				resultat[*count]=tmp;
				*count = *count + 1 ;
				arrd[(*y)*qrsize+*x] = 8;
			}
			*x= *x + 1;
			*y = *y -1;
		}
	}
	*y = *y +1;
	*x=*x-2;
	return ;

}

void getdown(int* x , int* y, int* resultat,int *arrd  ,int* count, int tot,int qrsize)
{


	while (*y<qrsize && arrd[(*y * qrsize)+*x]!=-1 && *count!=tot)
	{
		int tmp = arrd[(*y * qrsize) +*x];
		if(tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i | count = %i => res = %i\n",*x , *y , *count,tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			resultat[*count]=tmp;
			*count = *count +1 ;
			arrd[(*y * qrsize) + *x] = 8;
			if (*count==tot)
			{

				break;
			}

		}
		*x=*x-1;
		tmp = arrd[(*y * qrsize)+*x];

		if (tmp!=-2)
		{
			//getchar();
			printf("x = %i | y = %i | count = %i => res = %i \n",*x , *y ,*count ,  tmp);
			//Prettprint(arrd , qrsize , *x ,*y );
			resultat[*count]=tmp;
			*count = *count + 1 ;
			arrd[(*y * qrsize ) + *x] = 8;	

		}
		*x=*x+1;
		*y = *y +1;
	}
	*y = *y -1;
	*x = *x-2;
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
	int y = qrsize-1 ;
	int x = qrsize-1 ;

	int* resultat =malloc(sizeof(int)*tot);

	int cou = 0 ;
	getup(&x,&y,resultat,arrd,&cou,4,qrsize);
	

	while (cou!=tot)
	{
		getup(&x,&y,resultat,arrd,&cou,tot,qrsize);

		getdown(&x,&y,resultat,arrd,&cou,tot,qrsize);

	}
	printf ("Last x = %i || Last y = %i \n",x ,y );
	return resultat;





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






