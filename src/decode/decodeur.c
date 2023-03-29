#include <stdio.h>


int bintoint(int* read , int start , int len)
{
	int c= 1;
	int res = 0;
	for(int e = start ; e<start+len ; e++)
	{
		res = res + c*read[e];
		c=c+1;
	}
	return res;
}
