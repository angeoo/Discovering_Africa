#include "parse.h"
#include "prints.h"
void parseprint(parser* w)
{
	for(int e = 0; e<w->count ; e++)
	{
	}
	for(int e = 0; e<w->count ; e++)
	{
	}
	for(int e = 0; e<w->count ; e++)
	{
	}
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
				}
				if(res== -1)
				{
				}
				if(res==-3)
				{

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
						found=1;
					}
					e=e+1;
				}
				if(!found)
				{
				}
			}
		}

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
				}
				else
				{
					if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 )) || (x==s-8 && y==8) )
					{
					}
					else
					{
						if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
						{
						}
						else
						{
						}
					}
				}
			}
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

					}
					else
					{
						if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 ))||(((x>=s-9)&&(x<s-4))&&((y>=s-9)&&(y<s-4)))|| (x==s-8 && y==8))
						{
						}
						else
						{
							if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
							{
							}
							else
							{
							}
						}
					}
				}
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

					}
					else
					{

                        
						if (((((x>7)&&(x<s-8))&& y==6) ||(((y>7)&&(y<s-8))&& x==6 ))||(((x>=s-9)&&(x<s-4))&&((y>=s-9)&&(y<s-4)))|| (x==s-8 && y==8) || ( (x<=s/2 +2  && x>=s/2-2) &&((y<=s-5 && y>s-10) || (y<=s/2 +2  && y>=s/2 -2) || (y<9 && y>=4)  )) || ( (y<=s/2 +2 && y>=s/2 -2) && ( (x>s-10 && x<=s-5) || (x<9 && x>=4))  ))
						{
						}
						else
						{
							if(((x==8)&&(( y<=8 && y!=6) || (y>=s-8))) || ((y==8)&&(x>=s-7 || x<=8)&& x!=6))
							{
							}
							else
							{
							}
						}
					}
				}
			}

		}
	}



	return;
}



