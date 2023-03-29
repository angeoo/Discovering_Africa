#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

void printres(parser w , int tot)
{
	for(int e = 0 ; e<=tot; e++ )
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
			printf("                ");
			printres(w,w.count);
		}
		if(y==1)
		{
			printf("                ");
			if(w.count>=3)
			{
				getencodingmode(bintoint(w.resultat,0,4));
			}

		}
		printf("\n");
	}
	return ; 

}


