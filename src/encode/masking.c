




int*  apply_mask(int* data, int size,char *mask)
{
	int *masked_data=calloc(size*size,sizeof(int));
	for (int x=0; x<size; x++)
	{
		for (int y=0; y<size; y++)
		{
			if (data[x*size+y]>=0)
			{
				if (!(strcmp(mask,"000")))
				{
					if((x+y)%2==0)
					{
						if(data[x*size+y]==1)
							maksed_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"001")))
				{
					if(x%2==0)
					{
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"010")))
				{
					if(y%3==0)
					{
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"011")))
				{
					if((x+y)%3==0)
					{
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"100")))
				{
					if(((x/2)+(y/3))%2==0)
					{	
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"101")))
				{
					if(((x*y)%2)+((x*y)%3)==0)
					{
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				if(!(strcmp(mask,"110")))
				{
					if((((x*y)%2)+((x*y)%3))%2==0)
					{	
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				
				if(!(strcmp(mask,"111")))
				{
					if((((x*y)%3)+((x+y)%2))%2==0)
					{	
						if(data[x*size+y]==1)
							masked_data[x*size+y]=0;
						else
							masked_data[x*size+y]=1;
					}
				}
				
				//data[x*size+y]=(data[x*size+y]^mask);
			}
			else
				masked_data[x*size+y]=data[x*size+y];
		}
	}
	return masked_data;
}
int penalty_N1(int *masked_data);
int penalty_N2(int *masked_data);
int penalty_N3(int *masked_data);
int penalty_N4(int *masked_data);
int penalties(int N1,int N2,int N3,int N4);

