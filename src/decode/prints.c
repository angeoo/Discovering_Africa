#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

void parseprint(parser* w)
{
	printf(" x  = %i , y  = %i\n",w->x,w->y);
	printf("Xs = ");
	for(int e = 0; e<w->count ; e++)
	{
		printf("%i.",w->xs[e]);
	}
	printf("\n");
	printf("Ys = ");
	for(int e = 0; e<w->count ; e++)
	{
		printf("%i.",w->ys[e]);
	}
	printf("\n");
	printf("count = %i | tot = %i \n",w->count , w->tot);
	printf("resultat= ");
	for(int e = 0; e<w->count ; e++)
	{
		printf("%i.",w->resultat[e]);
	}
	printf("\n");
	return;
}
void NormalPrint(int* qrmat , int qrsize , parser* w) 
{
	//parsing the whole matrix
	for(int y = 0 ; y<qrsize ; y++ )
	{
		for(int x = 0 ; x<qrsize ; x++)
		{
			int res = qrmat[y*qrsize + x];//getting the value of the case
			if(res<0)
			{
				if(res == -2)
				{
					printf("\x1b[31m%i\x1b[0m", res); //format info in light blu
				}
				if(res== -1)
				{
					printf("\x1b[34m%i\x1b[0m",res); // allignment block in blue
				}
				if(res==-3)
				{
					printf("\x1b[36m%i\x1b[0m",res); // allignment pattern in red

				}

			}
			else
			{
				int found = 0 ;
				int e=0;
				//printing elements already done
				while(e<w->count && !found)
				{
					if(w->xs[e]== x && w->ys[e]== y) //if x case and y case found
					{
						printf("\x1b[32m %i\x1b[0m",res); //print in green
						found=1;
					}
					e=e+1;
				}
				if(!found)
				{
					printf(" %i",res);
				}
			}
		}
		printf("\n");

	}
}

void NoParsePrint(int* matrice, int s)
{
	if (s<22)
	{
		for (size_t x = 0 ; x<s ; x +=1)
		{
			for (size_t y = 0; y<s ; y+=1)
			{
				int res=matrice[x*s+y];
				if (((x<8)&&(y<8))||((x<8)&&(y>=s-8))||((x>=s-8)&&(y<8)))
				{
					printf("\x1b[34m %i\x1b[0m",res);
				}
				else
				{
					if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 )) || (x==s-8 && y==8) )
					{
						printf("\x1b[31m %i\x1b[0m",res);
					}
					else
					{
						if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
						{
							printf("\x1b[36m %i\x1b[0m",res);
						}
						else
						{
							printf(" %i",res);
						}
					}
				}
			}
			printf("\n");
		}
	}
	else
	{
		if(s<44)
		{
			for (size_t x = 0 ; x<s ; x +=1)
			{
				for (size_t y = 0; y<s ; y+=1)
				{
					int res=matrice[x*s+y];
					if (((x<8)&&(y<8))||((x<8)&&(y>=s-8))||((x>=s-8)&&(y<8)))
					{
						printf("\x1b[34m %i\x1b[0m",res);

					}
					else
					{
						if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 ))||(((x>=s-9)&&(x<s-4))&&((y>=s-9)&&(y<s-4)))|| (x==s-8 && y==8))
						{
							printf("\x1b[31m %i\x1b[0m",res);
						}
						else
						{
							if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
							{
								printf("\x1b[36m %i\x1b[0m",res);
							}
							else
							{
								printf(" %i",res);
							}
						}
					}
				}
				printf("\n");
			}
		}
		else
		{
			for (size_t x = 0 ; x<s ; x +=1)
			{
				for (size_t y = 0; y<s ; y+=1)
				{
					int res=matrice[x*s+y];
					if (((x<8)&&(y<8))||((x<8)&&(y>=s-8))||((x>=s-8)&&(y<8)))
					{
						printf("\x1b[34m %i\x1b[0m",res);

					}
					else
					{
						if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 ))||(((x>=s-9)&&(x<s-4))&&((y>=s-9)&&(y<s-4)))|| (x==s-8 && y==8) || ( (x<=s-21 && x>=s-25) &&
									((y<=s-5 && y>=s-9) || (y<=s-21 && y>=s-25) || (y<=s-37 && y>=s-41)  )) || ( (y<=s-21 && y>=s-25) && ( (x<=s-37 && x>=s-41) || (x<=s-5 && x>=s-9))  ))
						{
							printf("\x1b[31m %i\x1b[0m",res);
						}
						else
						{
							if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
							{
								printf("\x1b[36m %i\x1b[0m",res);
							}
							else
							{
								printf(" %i",res);
							}
						}
					}
				}
				printf("\n");
			}

		}
	}



	return;
}



