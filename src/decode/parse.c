#include <stdio.h>
#include <stdlib.h>







void getup(int* x , int* y, int* resultat,int* arrd  ,int* count,int tot,int qrsize)
{


	while (*y>0 && arrd[(*y * 21)+ *x]!=-1 && *count!=tot)
	{
		int tmp = arrd[(*y * 21)+ *x];
		if(tmp!=-2)
		{
			printf("x = %i | y  = %i , count = %i , tot = %i ", *x , *y , *count , tot);

			resultat[*count]=tmp;
			*count = *count +1 ;
			arrd[(*y * 21) + *x]= 8;
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
			if (*count==tot)
			{
				break;
			}
		}
		*x=*x-1;
		tmp = arrd[(*y * 21) + *x];
		printf("x = %i | y  = %i , count = %i , tot = %i ", *x , *y , *count , tot);


		if (tmp!=-2)
		{
			resultat[*count]=tmp;
			*count = *count + 1 ;
			arrd[(*y * 21)+ *x] = 8;
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
		}
		*x= *x + 1;
		*y = *y -1;
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

			resultat[*count]=tmp;
			*count = *count +1 ;
			arrd[(*y * qrsize) + *x] = 8;
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
			if (*count==tot)
			{

				break;
			}

		}
		*x=*x-1;
		tmp = arrd[(*y * qrsize)+*x];

		if (tmp!=-2)
		{
			resultat[*count]=tmp;
			*count = *count + 1 ;
			arrd[(*y * qrsize ) + *x] = 8;	
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);

		}
		*x=*x+1;
		*y = *y +1;
	}
	*y = *y -1;
	*x = *x-2;
	return ;

}


void Prettprint(int* arrd,int qrsize)
{

	for(int y =0 ; y<qrsize; y++)
	{
		for(int x = 0 ;x < qrsize ; x ++)
		{
			int res = arrd[(y*qrsize)+x];
			if(res<0)
			{
				printf("%i",res);
			}
			else
			{
				printf(" %i",res);
			}

		}
		printf("\n");
	}
	return ; 

}

int* getall( int* arrd , int tot, int qrsize)
{
	int y = 21 ;
	int x = 21 ;

	int* resultat =malloc(sizeof(int)*tot);

	int cou = 0 ;

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






