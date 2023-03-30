#include "masking.h"




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
			}
			else
				masked_data[x*size+y]=data[x*size+y];
		}
	}
	return masked_data;
}

//RENDRE LES MODULES DE FUNCTIONS PATTERNS ACCESSIBLES A NOUVEAU

int adjacent_row(int i, int j ,int *masked_data,size)
{
	int n1=0, penalty=0;
	for(int x=0;x<size;x++)
	{
		if (masked_data[i*size+j]==masked_data[i*size+x])
		{
			n1++;
		else
		{
			if (n1>=5)
				penalty+=2-n1;
			j+=n1;
			n1==0;
		}
	}
	return penalty;
}
int adjacent_col(int i, int j, int *masked_data,size)
{
	int n1=0, penalty=0;
	for (int y=0;y<size;y++)
	{
		if (masked_data[y*size+j]==masked_data[i*size+j])
			n1++;
		else
		{	if (n1>=5)
				penalty+=2-n1;
			i+=n1;
			n1=0;
		}
	}
	return penalty;
}

int penalty_N1(int *masked_data,size);
{
	int penalty=0;
	for (int i=0;i<size;i++)
		penalty+=adjacent_row(i,0,masked_data,size);
	
	for (int i=0;i<size;i++)
		penalty+=adjacent_col(0,i,masked_data,size);

	return penalty;
}

int penalty_N2(int *masked_data,size)
{
	int penalty=0;
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-1; j++)
		{
			if (masked_data[i*size+j]==masked_data[i*size+(j+1)]
					&& masked_data[(i+1)*size+j]==masked_data[i*size+j]
					&& masked_data[(i+1)*size+(j+1)]==masked_data[i*size+j])
				penalty+=3;
		}
	}
	return penalty;
}
int finder_row(int i, int* masked_data, int size)
{
	int penalty=0;
	for (int x=0; x<size-7; x++)
	{
		int p=0;
		for (int k=0; k<7;k++)
			p+=masked_data[i*size+(x+k)];
		if (p==5)
			penalty+=40;
	}
	return penalty;
}
int finder_col(int j,int *masked_data,int size)
{
	int penalty=0;
	for (int y=0; y<size-7; y++)
	{
		int p=0;
		for (int k=0; k<7; k++)
			p+=masked_data[(y+k)*size+j];
		if (p==5)
			penalty+=40;
	}
	return penalty;
}

int penalty_N3(int *masked_data,size)
{
	int penalty=0;
	for (int i=0; i<size; i++)
		penalty+=finder_row(i,masked_data,size);
	for(int j=0;j<size;j++)
		penalty+=finder_col(j,masked_data,size);
	return penalty;
}

int penalty_N4(int *masked_data,int size)
{
	int tot=size*size, blacks=0;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			blacks+=masked_data[i*size+j];
	}
	float percentage=(blacks*100)/tot;
	int penalty=0, next=55, prev=45;
	for (x=0;x<10;x++)
	{
		if (percentage<prev || percentage>next)
			penalty+=10;
		prev-=5;
		next+=5;
	}
	return penalty;
}



int penalties(int N1,int N2,int N3,int N4);
{
	return N1+N2+N3+N4;
}
