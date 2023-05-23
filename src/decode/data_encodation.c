#include "data_encodation.h"

const size_t VE_data_capacity[40]={7,11,14,17,14,20,26,32,24,32,42,53,34,46,62,
	78,44,60,84,106,58,74,106,134,64,86,122,154,84,108,152,192,98,130,180,230,
    119,151,213,271};

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
	if (((len*8)+12)%8!=0){
		size_t k=(len*8)+12+((len*8)+12)%8;
		int *Bitstream=realloc(bitstream,k*sizeof(int));
		if (Bitstream==NULL)
			errx(1,"realloc()");
		for(size_t i=(len*8)+12; i<k; i++)
			Bitstream[i]=0;
		return Bitstream;
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
int * appendArray(int* dest, int src[], int destSize, int srcSize) {
	int newSize = destSize + srcSize;
	dest = realloc(dest, newSize * sizeof(int));
	if (dest==NULL)
		errx(1,"realloc()");

	for (int i = 0; i < srcSize; i++) {
		dest[destSize + i] = src[i];
	}
	 return dest;
}
int * pad_codewords(int* bitstream,size_t len,int* count){

	size_t i=0;
	while (i<40 && len>VE_data_capacity[i]*8)
		i++;
	size_t version=1+i/4, ECL=i%4;
	switch (ECL) {
		case 0:
			printf("this input can fit in a "
					"%ld-H Qr code\n",version);
			break;
		case 1:
			printf("this input can fit in a "
					"%ld-Q Qr code\n",version);
			break;
		case 2:
			printf("this input can fit in a "
					"%ld-M Qr code\n",version);
			break;
		case 3:
			printf("this input can fit in a "
					"%ld-L Qr code\n",version);
			break;
		default:
			errx(1,"this input is too big\n");
			break;
	}
	int pad_codeword1[8]={1,1,1,0,1,1,0,0};
	int pad_codeword2[8]={0,0,0,1,0,0,0,1};
	int c=0;
	int *Bitstream=bitstream;
	while ( len<(VE_data_capacity[i]*8)+2){
		Bitstream=appendArray(Bitstream,pad_codeword1,len,8);
		len+=8;
		c++;
		if (len>=(VE_data_capacity[i]*8)+2)
			return Bitstream;
		//	break;
		Bitstream=appendArray(Bitstream,pad_codeword2,len,8);
		len+=8;
		c++;
	}
	*count=c;
	return Bitstream;
}




/*
int main (int argc, char* argv[])
{

	if (argc!=2)
		errx(1,"too many arguments");
	int *bitstream=BitStream(argv[1]);
	size_t len=strlen(argv[1]);
	printf("strlen: %ld\n",len);
	size_t k=12+(len*8);
	size_t p=k%8;
	len=k+p;
	for (size_t i=0; i<k+p; i++)
	{
		if (i==12)
			printf("  ");
		if (i==k)
			printf("  ");
		printf("%d", bitstream[i]);

	}
	printf("\n");
	int count;
	int* Bitstream=pad_codewords(bitstream, len, &count);
	printf("added pad_codewords: %d\n",count);
	for (size_t i=0; i<len+count*8; i++){
		if (i==12)
			printf("  ");
		if (i==k)
			printf("  ");
		if (i==k+p)
			printf(" ");
		if (i>k+p && i%8==0)
			printf(" ");
		printf("%d", Bitstream[i]);
	}


	printf("\n");
	free(Bitstream);
	return 0;
}


*/
