#include "print.h"
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
                                        if(w->xs[w->count]== x && w->ys[w->count]== y) //if x case and y case found
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

