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
				else
				{
					printf("\x1b[34m%i\x1b[0m",res);
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
			if(w.count>=1)
			{
			printf("                ");
			printres(w);
			}
		}
		if(y==1)
		{
			printf("                ");
			if(w.count>=4)
			{
				getencodingmode(bintoint(w.resultat,0,4));
			}

		}
		if(y==3)
		{
			printf("                ");
			printf("count = %i",w.count);
		}

		if(y==4)
		{
			printf("                ");
			if(w.count<12 && w.count>4)
			{
				printf("detecting lenght of the data encoded ... ");

			}
			else
			{
				if(w.count>=12)
				{
					printf("data lenght : %i",bintoint(w.resultat,4,8));
			
				}
			}
		}
		if(y==6)
		{
		
			printf("                ");


			if(w.count>12 && w.count<20)
			{
				printf("starting to decode the message");

			}
			if(w.count>=20 && (w.count-12)%8==0)
			{
		
				int asc = bintoint(w.resultat,w.count-8,8);
				printf("nb : %i    | ",asc);	
				int c = (w.count-12)/8 ;
				printf("charcater %i found! %c",c,(char)asc);
			}

		}	
		printf("\n");
	}
	return ; 

}


