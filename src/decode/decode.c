#include "decode.h"

tuple position_dectection_patterns(SDL_image qr, void* res)
{
	int w=qr->w , h=qr->h, X=0,x1=0,x2=0,x3=0,x4=0,x5=0,x6=0;
	Uint8 r,g,b;
	Uint32 pixel;
	tuple pdp;
	for (int i=0; i<w; i++)
	{
		for(int j=0; j<h: j++)
		{
			pixel=getpixel(qr,i,j);
			SDL_GetRGB(pixel,qr,&r,&g,&b);
			//switch case ?
			//x1-x6 coordonates of modules in pdp
			if (r==0 && X==0 )
				x1=i;
			if (r==125 && X<1)
			{
				x2=i;
				X+=1;
			}
			if (r==0 && X<2)
			{
				x3=i;
				X+=1;
			}
			if (r==125 && X<3)
			{
				x4=i;
				X+=1;
			}
			if (r==0 && X<4)
			{
				x5=i;
				X+=1;
			}
			if (r==125 && X<5)
			{
				x6=i;
				X+=1;
			}
		}
	}
	if (x2-x1==3(x4-x3))
	{
		pdp.x=x1;
		pdp.y=
	




