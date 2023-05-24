#include "masking.h"

void Mask (int* data, int mask,int size)
{
    for (int x=0; x<size; x++)
    {
        for (int y=0; y<size; y++)
        {
            if (data[x*size+y]>=0)
            {
                if (mask==0)
                {
                    if((x+y)%2==0)
                    {
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==1)
                {
                    if(x%2==0)
                    {
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==2)
                {
                    if(y%3==0)
                    {
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==3)
                {
                    if((x+y)%3==0)
                    {
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==4)
                {
                    if(((x/2)+(y/3))%2==0)
                    {    
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==5)
                {
                    if(((x*y)%2)+((x*y)%3)==0)
                    {
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                if(mask==6)
                {
                    if((((x*y)%2)+((x*y)%3))%2==0)
                    {    
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                
                if(mask==7)
                {
                    if((((x*y)%3)+((x+y)%2))%2==0)
                    {    
                        if(data[x*size+y]==1)
                            data[x*size+y]=0;
                        else
                            data[x*size+y]=1;
                    }
                }
                
            }
        }
    }
}
char * Find_masking(int *data,int size)
{
	char* mask=calloc(3,sizeof(char));
	mask[0]='0'+data[8*size+2];
	mask[1]='0'+data[8*size+3];
	mask[2]='0'+data[8*size+4];
	return mask;
}

void Rmask (int* data, int size,int*data2)
{
	char *mask= Find_masking(data2,size);
	for (int x=0; x<size; x++)
	{
		for (int y=0; y<size; y++)
		{
			if (data[x*size+y]>=0)
			{//xoring masking pattern with 10101
				if (!(strcmp(mask,"101")))
				{
					if((x+y)%2==0)
					{
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"100")))
				{
					if(x%2==0)
					{
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"111")))
				{
					if(y%3==0)
					{
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"110")))
				{
					if((x+y)%3==0)
					{
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"001")))
				{
					if(((x/2)+(y/3))%2==0)
					{	
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"000")))
				{
					if(((x*y)%2)+((x*y)%3)==0)
					{
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"011")))
				{
					if((((x*y)%2)+((x*y)%3))%2==0)
					{	
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				
				if(!(strcmp(mask,"010")))
				{
					if((((x*y)%3)+((x+y)%2))%2==0)
					{	
						if(data[x*size+y]==1)
							data[x*size+y]=0;
						else
							data[x*size+y]=1;
					}
				}
				
				//data[x*size+y]=(data[x*size+y]^mask);
			}
		}
	}
}

