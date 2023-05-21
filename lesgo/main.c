#include "parse.h"
#include "print.h"
#include "qr.h"
#include "decode.h"



int *BitStream(char *input)
{

	int len=strlen(input);
	if (len >=17)
	{
		printf("data input too long for Qr code version 1-L");

	}
	int k=19;//data capacity of qr 1-L
	int *bitstream=calloc((k*8)+12,sizeof(int));//starting with format info (4bits) and character count (8bits)
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
		{
			bitstream[g-j]=input[i]>>j & 1;
		}
		g+=8;
	}
	//determine the number of pad_codeword to add
	int index=0;
	while (((12+(len*8))+index)%8!=0)
		index++;
	index+=12+(len*8);
	int tmp=0;//temporary variable to store pad_codewords
	for (int i=index;i<((k*8)+12)-8;i+=8){
		int pad_codeword1=236;
		int pad_codeword2=17;
		for (int j=0;j<8;j++){
			bitstream[i+j+1]=pad_codeword1>>j & 1;
		}
		if (i%8==0)     {
			tmp=pad_codeword1;
			pad_codeword1=pad_codeword2;
			pad_codeword2=tmp;      
		}
	}
	return bitstream;
}

int main()
{

	//creer une matrice 
	int* created = creer_matric(); //to  free

	//ajouter les neg
	int* negcreated = matdata(created,21);
	getchar();


	printf("enter you word\n");
	char* word = malloc(sizeof(char)*100);
	scanf("%s",word);


	int c=0;

	scanf("%s",word);
	while(word[c]!='\0')
	{
		c=c+1;
	}
	int size =21;

	int* res =BitStream(word);

	int totals =8 * c + 12;


	parser* toput = malloc(sizeof(parser));
	toput->x=size-1;
	toput->y=size-1;
	toput->resultat = res;
	toput->count=0;
	toput->xs = malloc(totals*sizeof(int));
	toput->ys = malloc(totals*sizeof(int));
	toput->tot=  totals;
	putall(toput , negcreated , totals, size);
	parser* toget = malloc(sizeof(parser));
	toget->x=size-1;
	toget->y=size-1;
	toget->resultat=calloc(totals, sizeof(int));
	toget->count=0;
	toget->xs=malloc(totals*sizeof(int));
	toget->ys=malloc(totals*sizeof(int));
	toget->tot=totals;
	toget->finalmsg=calloc(totals+1,sizeof(char));
	toget->finalmsg[totals]='\0';
	getall(toget,negcreated,totals,size);


	printf("finalmsg= %s \n",toget->finalmsg);


	printf("count = %i ",toput->count);





	return 1;
}
