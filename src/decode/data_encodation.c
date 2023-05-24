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
int * pad_codewords(int* bitstream,size_t len,int* count, int* retecl){

    size_t i=0;
    while (i<40 && len>VE_data_capacity[i]*8)
        i++;
    size_t version=1+i/4, ECL=i%4; 
    *retecl= ECL;
    /*switch (ECL) {
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
    }*/
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

int* binaryRepresentation(int number, int size) {
    int* binaryArray = malloc(size * sizeof(int));
    if (binaryArray==NULL)
        errx(1,"malloc()");

    for (int i = 0; i < size; i++) {
        binaryArray[i] = number & 1;
        number >>= 1;
    }

    return binaryArray;
}

void ArrayShift(int* array,int len, int count){
    for (int i=0; i<count; i++){
        for (int j=1; j<len; j++){
            array[j-1]=array[j];
        }
        array[len-1]=0;
    }
}

int* FormatInfo (int ECL, int MASK){
    int* ecl=binaryRepresentation(ECL, 2);
    int* mask=binaryRepresentation(MASK, 3);
    ecl=appendArray(ecl,mask,2,3);
    //free(ecl);
    //free(mask);
    int* BCH=calloc(10,sizeof(int));
    if (BCH==NULL)
        errx(1,"calloc()");
    ecl=appendArray(ecl,BCH,5,10);
    //free(BCH);
    int Gx[15]={0,0,0,0,1,0,1,0,0,1,1,0,1,1,1};
    int i=0;
    while (i<10 && ecl[i]!=1)
        i++;
    ArrayShift(Gx,15,i);
    int* format_info=calloc(15,sizeof(int));
    if (format_info==NULL)
        errx(1,"calloc()");
    size_t index=0;
    for (int k=0;k<15;k++){
        if (Gx[k]!=ecl[k])
            format_info[k]=1;
        else
            format_info[k]=0;
    }
    for (int k=0;k<15;k++){
        //if (format_info[k]==1)
        //    break;
        index++;
    }
    ecl=appendArray(ecl,format_info+5,5,10);
    int Xor[15]={1,0,1,0,1,0,0,0,0,0,1,0,0,1,0};
    for (int j=0; j<15; j++){
        if (Xor[j]!=ecl[j])
            ecl[j]=1;
        else
            ecl[j]=0;
    }
    return ecl;
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
