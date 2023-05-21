//pipi
#include "decode.h"

int convertbittoint(int* seq , int gap) // convert a sequence of gap bits to an int/ sens contraire  
{
        int res=0;   //resultat
        int m=1;     //multiplicatuer
        for(int c=0 ; c<gap ; c++)
        {
                res = res+ seq[gap-1-c]*m;
                m=m*2;
        }
        return res;
}

int GiveECI(char* c)
{
	return 0;
}

