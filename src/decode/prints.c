#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

void printres(parser w )
{
	for(int e = 0 ; e<w.count; e++ )
	{
		printf("%i", w.resultat[e]);
	}
}

void Prettprint(int* arrd,int qrsize,parser w )
{
	printf("\033[2J");
	

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
				if(res== -1)
				{
					printf("\x1b[34m%i\x1b[0m",res);
				}
				if(res==-3)
				{
					printf("\x1b[36m%i\x1b[0m",res);

				}
			}
			else
			{	
				int found = 0 ;
				for (int e = 0; e < w.tot; e++)
				{
					if(w.xs[e] == x && w.ys[e]==y)
					{
						printf("\x1b[32m %i\x1b[0m",res);
						found = 1;
						break;

					}
				}
				if(!found)
				{
					printf(" %i",res);
				}
			}


		}
		if(y==0)
		{
			printf("                __________________________________________________________________________________________________________");
		}
		
		if(y==1)
		{
			
			printf("                |");
			if(w.count>=1)
			{

			printres(w);
			}
		}
		if(y==2)
		{
			printf("                |___________________________________________________________________________________________________________");
		}
		if(y==3)
		{
			printf("                |");
			if(w.count>=4)
			{
				getencodingmode(bintoint(w.resultat,0,4));
			}

		}
		if(y==4)
		{
			printf("                |________________________________________________");
		}
		if(y==5)
		{
			printf("                |count = %i",w.count);
		}
		if(y==6)
		{
			printf("                |________________________________________________");
		}
		if(y==7)
		{
			if(w.count<12 && w.count>4)
			{
				printf("                |detecting lenght of the data encoded ...                    | ");

			}
			else
			{
				if(w.count>=12)
				{
					printf("                |data lenght : %i",bintoint(w.resultat,4,8));
			
				}
			}
		}
		if(y==8)
		{
			printf("                |________________________________________________");
		}
		if(y==9)
		{
			printf("                |");	
			if(w.count>12 && (w.count-12)%8!=0)
			{
				printf("Searching for a letter ... ");

			}
			if(w.count>=20 && (w.count-12)%8==0)
			{
		
				int asc = bintoint(w.resultat,w.count-8,8);
				int c = (w.count-12)/8 ;
				w.finalmsg[c-1]=(char)asc;
				printf("Charcater %i found ! => %c ",c,(char)asc);
			}

		}
		if(y==10)
		{
			printf("                |________________________________________________");
		}
		if(y==11)
		{
			printf("                |Message found : %s    ",w.finalmsg);


		}
		if(y==12)
		{
			printf("                |________________________________________________");

		}	
		printf("\n");
	}
	return ; 

}

void Prettprintv2(int* arrd,int qrsize,parser w )
{
	printf("\033[2J");
	

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
				if(res== -1)
				{
					printf("\x1b[34m%i\x1b[0m",res);
				}
				if(res==-3)
				{
					printf("\x1b[36m%i\x1b[0m",res);

				}
			}
			else
			{	
				int found = 0 ;
				for (int e = 0; e < w.tot; e++)
				{
					if(w.xs[e] == x && w.ys[e]==y)
					{
						printf("\x1b[32m %i\x1b[0m",res);
						found = 1;
						break;

					}
				}
				if(!found)
				{
					printf(" %i",res);
				}
			}


		}
		printf("\n");
	}
	return ; 

}


