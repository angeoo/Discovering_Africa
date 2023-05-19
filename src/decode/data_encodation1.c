#include "data_encodation.h"


int *BitStream(char *input)
{

	int len=strlen(input);
	//if (len >=17)
	//	printf("data input too long for Qr code version 1-L");
	//int k=19;//data capacity of qr 1-L
	int *bitstream=calloc((len*8)+12,sizeof(int));//starting with format info (4bits) and character count (8bits)
	// bitstream to max capacity k of qr-code 1-L
	if (bitstream==NULL)
		errx(1,"unable to malloc()");
	bitstream[1]=1;//8-bit byte mode
	//assuming character count is 8bits (ver 1-9)
	//converting character count to an array of 1 & 0
	for (int i=0;i<8;i++)
		bitstream[11-i]=len>>i & 1;
	int g=11+8;//starting to write the input
	for (int i=0; i<len; i++)
	{
		for (int j=0;j<8;j++)
			bitstream[g-j]=input[i]>>j & 1;
		g+=8;
	}
	//determine the number of pad_codeword to add
	/*int index=0;
	while (((12+(len*8))+index)%8!=0)
		index++;
	index+=12+(len*8);
	

	int tmp=0;//temporary variable to store pad_codewords
	for (int i=index;i<((k*8)+12)-8;i+=8)//adding pad_codewords after terminal 0000
	{
		int pad_codeword1=236;
		int pad_codeword2=17;
		for (int j=0;j<8;j++)
		{
			bitstream[i+j+1]=pad_codeword1>>j & 1;
		}
		if (i%8==0)
		{
			tmp=pad_codeword1;
			pad_codeword1=pad_codeword2;
			pad_codeword2=tmp;
		}
	}
			*/

	return bitstream;
}


int main (int argc, char* argv[])
{
	
	if (argc!=2)
		errx(1,"too many arguments");
	int *bitstream=BitStream(argv[1]);
	int len=strlen(argv[1]);
	//int k=19;
	for (int i=0; i<12+(len*8); i++)
	{
		if (i==12)
			printf("  ");
		/*if (i>=12+(len*8))
			printf("  ");*/
		printf("%d", bitstream[i]);
	}
	printf("\n");
	free(bitstream);
	return 0;
}

