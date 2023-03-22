#include <stdio.h>
#include <stdlib.h>

int arr [20][21]= {
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 0,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 1, 0,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 0, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 0,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-2,-1,-1, 0, 1, 1, 0,-1,-1,-1,-1,-1,-1,-1,-1},
	{ 1, 0, 1, 1, 0, 1,-2, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0},
	{ 1, 1, 1, 0, 0, 1,-2, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
	{ 0, 1, 0, 0, 1, 1,-2, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0},
	{ 1, 0, 1, 1, 0, 1,-2, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1},

};








void getup(int* x , int* y, int* resultat,int arrd[20][21]  ,int* count,int tot)
{


	while (*y>0 && arrd[*y][*x]!=-1 && *count!=tot)
	{
		int tmp = arrd[*y][*x];
		if(tmp!=-2)
		{

			resultat[*count]=tmp;
			*count = *count +1 ;
		        arrd[*y][*x] = 8;	
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
			if (*count==tot)
			{
				break;
			}
		}
		*x=*x-1;
		tmp = arrd[*y][*x];

		if (tmp!=-2)
		{
			resultat[*count]=tmp;
			*count = *count + 1 ;
			arrd[*y][*x] = 8;
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
		}
		*x=*x+1;
		*y = *y -1;
	}
	*y = *y +1;
	*x=*x-2;
	return ;

}

void getdown(int* x , int* y, int* resultat,int arrd[20][21]  ,int* count, int tot)
{


	while (*y<20 && arrd[*y][*x]!=-1 && *count!=tot)
	{
		int tmp = arrd[*y][*x];
		if(tmp!=-2)
		{

			resultat[*count]=tmp;
			*count = *count +1 ;
			arrd[*y][*x] = 8;
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);
			if (*count==tot)
			{

				break;
			}

		}
		*x=*x-1;
		tmp = arrd[*y][*x];

		if (tmp!=-2)
		{
			resultat[*count]=tmp;
			*count = *count + 1 ;
		       	arrd[*y][*x] = 8;	
			printf("| x = %i , y = %i -> tmp = %i |\n",*x,*y,tmp);

		}
		*x=*x+1;
		*y = *y +1;
	}
	*y = *y -1;
	*x = *x-2;
	return ;

}


void Prettprint(int arrd[20][21])
{

	for(int y =0 ; y<20; y++)
	{
		for(int x = 0 ;x < 21 ; x ++)
		{
			int res = arrd[y][x];
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

void getall(int *x , int *y , int *resultat , int arrd[20][21] , int tot)
{

	int cou = 0 ;
	while (cou!=tot)
	{
		getup(x,y,resultat,arrd,&cou,tot);

		getdown(x,y,resultat,arrd,&cou,tot);

	}
	return;





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
 




int main()
{
	Prettprint(arr);
	int tot = 170;
	int y = 19 ; 
	int x = 20;
	int* res = malloc(sizeof(int)*40);


	getall(&x,&y,res,arr,tot);

	printf("x= %i , y= %i ",x,y);

	int mode = bintoint(res,0,4 );
	printf("encoding mode to dec = %i \n",mode);

	getencodingmode(mode);



	for (int i = 0; i < tot; i++)
	{
		printf("%i",res[i]);        
	}
	Prettprint(arr);


	//free(res);

	return 0;

}
