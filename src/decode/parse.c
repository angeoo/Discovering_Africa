#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
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


void storemsg(parser* w)
{
    if(w->count-12 > 0 && (w->count-12)%8==0 )
    {
        int tmpo=convertbittoint(w->resultat+w->count -8 ,8);
        printf("char decoded to int = %i\n",tmpo);
        w->finalmsg[((w->count-12) /8)-1 ] = (char)tmpo;
        printf("char is %c \n", (char)tmpo);
    }
    else
    {
        printf("searching word is not ready");
    }
}


// w      : parseur 
// arrd   : the 1D array containing the QR code
// tot    : number of cases to parse
// qrsize : lenght or width of the QR code 

void getup(parser* w , int* arrd , int tot , int qrsize)
{
    while(w->count<tot)                              //while the parser hasnt done all the cases needed
    {
        int val = arrd[(w->y)*qrsize + w->x];

        if(val!=-2 )                             //if we are not on a case to ignore
        {               
            w->xs[w->count] = w->x;          //store the case'X that we saw
            w->ys[w->count] = w->y;          //store the case'Y that we saw
            w->resultat[w->count] = val;     //store the value in the result array
            w->count = w->count +1;          //we add to count 1;
            storemsg(w);
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
        }
        if(w->count>=tot)                        //break if weve done all the cases
        {
            break;
        }
        w->x = w->x - 1;                        //go 1 case to the left by decrementing x
        val = arrd[(w->y)*qrsize + w->x];       //getting the value of the next case
        if(val!=-2)
        {
            w->xs[w->count] = w->x;        //same as before
            w->ys[w->count] = w->y;
            w->resultat[w->count] = val;
            w->count = w->count + 1;
            storemsg(w);
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
        }
        if(w->y-1<0 || arrd[(w->y -1)*qrsize + w->x]==-3)
        {
            w->x=w->x-1;                                           //if outside , we push to the left (well go down)
            break;
        }
        else                                               
        {
            w->x = w->x +1;                                        //if inside we just update to go up 
            w->y = w->y-1;
            val=arrd[(w->y)*qrsize+w->x];
        }
    }
}

void getdown(parser* w , int* arrd , int tot , int qrsize)
{

    while(w->count<tot)                              //while the parser hasnt done all the cases needed
    {
        int val = arrd[(w->y)*qrsize + w->x];

        if(val!=-2 )                             //if we are not on a case to ignore
        {               
            w->xs[w->count] = w->x;          //store the case'X that we saw
            w->ys[w->count] = w->y;          //store the case'Y that we saw
            w->resultat[w->count] = val;     //store the value in the result array
            w->count = w->count +1;          //we add to count 1;
            storemsg(w);
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
        }
        //getchar();
        if(w->count>=tot)                        //break if weve done all the cases
        {
            break;
        }
        w->x = w->x - 1;                        //go 1 case to the left by decrementing x
        val = arrd[(w->y)*qrsize + w->x];       //getting the value of the next case
        if(val!=-2)
        {
            w->xs[w->count] = w->x;        //same as before
            w->ys[w->count] = w->y;
            w->resultat[w->count] = val;
            w->count = w->count + 1;
            storemsg(w);
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
        }
        //getchar();
        if(w->y + 1 >=qrsize  )         //check that we are not outside the data
        {
            w->x=w->x-1;                                           //if outside , we push to the left (well go down)
            break;
        }
        else                                               
        {
            w->x = w->x +1;                                        //if inside we just update to go down 
            w->y = w->y+1;
            val=arrd[(w->y)*qrsize+w->x];
        }
    }
}

void getall(parser* w , int* arrd , int tot , int qrsize)
{
    while(w->count<tot)
    {
        getup(w,arrd,tot,qrsize);
        getdown(w,arrd,tot,qrsize);
    }
    return;
}

void putup(parser* w , int* arrd , int tot , int qrsize)
{
    while(w->count<tot)                              //while the parser hasnt done all the cases needed
    {
        int val = arrd[(w->y)*qrsize + w->x];

        if(val!=-2 )                             //if we are not on a case to ignore
        {
            w->xs[w->count] = w->x;          //store the case'X that we saw
            w->ys[w->count] = w->y;          //store the case'Y that we saw
            arrd[w->y*qrsize + w->x]=w->resultat[w->count];     //store the value in the qrcode matrix
            w->count = w->count +1;          //we add to count 1;
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
 
        }
        //getchar();
        if(w->count>=tot)                        //break if weve done all the cases
        {
            break;
        }
        w->x = w->x - 1;                        //go 1 case to the left by decrementing x
        val = arrd[(w->y)*qrsize + w->x];       //getting the value of the next case
        if(val!=-2)
        {
            w->xs[w->count] = w->x;        //same as before
            w->ys[w->count] = w->y;
            arrd[w->y*qrsize + w->x]=w->resultat[w->count];
            w->count = w->count + 1;
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
                    }
        //getchar();
        if(w->y - 1 <0 || arrd[(w->y - 1)*qrsize + w->x]==-3 )         //check that we are not outside the data
        {
            w->x=w->x-1;                                           //if outside , we push to the left (well go down)
            break;
        }
        else
        {
            w->x = w->x +1;                                        //if inside we just update to go up 
            w->y = w->y-1;
            val=arrd[(w->y)*qrsize+w->x];
        }
    }
    return;
}




void putdown(parser* w , int* arrd , int tot , int qrsize)
{
    while(w->count<tot)                              //while the parser hasnt done all the cases needed
    {
        int val = arrd[(w->y)*qrsize + w->x];

        if(val!=-2 )                             //if we are not on a case to ignore
        {
            w->xs[w->count] = w->x;          //store the case'X that we saw
            w->ys[w->count] = w->y;          //store the case'Y that we saw
            arrd[w->y*qrsize + w->x]=w->resultat[w->count];     //store the value in the qrcode matrix
            w->count = w->count +1;          //we add to count 1;
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
            
        }
        if(w->count>=tot)                        //break if weve done all the cases
        {
            break;
        }
        w->x = w->x - 1;                        //go 1 case to the left by decrementing x
        val = arrd[(w->y)*qrsize + w->x];       //getting the value of the next case
        if(val!=-2)
        {
            w->xs[w->count] = w->x;        //same as before
            w->ys[w->count] = w->y;
            arrd[w->y*qrsize + w->x]=w->resultat[w->count];
            w->count = w->count + 1;
            getchar();
            NormalPrint(arrd,qrsize,w);
            parseprint(w);
                   }
        if(w->y + 1  >=qrsize )         //check that we are not outside the data
        {
            w->x=w->x-1;                                           //if outside , we push to the left (well go down)
            break;
        }
        else
        {
            w->x = w->x +1;                                        //if inside we just update to go up
            w->y = w->y+1;
            val=arrd[(w->y)*qrsize+w->x];
        }
    }
    return;
}





void putall(parser* w , int*arrd , int tot , int qrsize)
{
    while(w->count<tot)
    {
        putup(w,arrd,tot,qrsize);
        putdown(w,arrd,tot,qrsize);

    }
    return ;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void RemoveNeg(int* init , int* res , int size)
{
	for(int x=0; x<size ; x++)
	{
		for(int y =0 ; y<size; y++)
		{
			if(init[y*size + x]>0)
			{
				res[y*size+x] = init[y*size+x];
			}
		}
	}
	return;
}




void getQRcode(int* QR , int size)
{
	printf("hey\n");	
	//Malloc the parser
	parser* w = malloc(sizeof(parser));

	w->count=0;

	//Inititating the Parser
	
	w->x=size-1;
	w->y=size-1;

	//Everything is set to 12 in order to get the size	

	w->xs=malloc(sizeof(int)*12);
	w->ys=malloc(sizeof(int)*12);
	w->resultat=calloc(12,sizeof(int));

	//get the encoding mode and size
	printf("hey\n");
	getall(w,QR,12,size);
	printf("stopped\n");
	getchar();

	//getting the len
	int len = convertbittoint(w->resultat+4,8)*8 +12;

	//mallocing the msg 
	w->finalmsg=malloc(len*sizeof(char) + 1);
	w->finalmsg[len]='\0';

	//reallocing the resultat array and ys and xs
	w->resultat= realloc(w->resultat,len*sizeof(int));
	w->ys=realloc(w->ys,len*sizeof(int));
	w->xs=realloc(w->xs,len*sizeof(int));
	//getting the rest of the array
	getall(w,QR,len,size);

	printf("final msg is : %s ", w->finalmsg);



	free(w->xs);
	free(w->ys);
	free(w->resultat);
	free(w->finalmsg);
	free(w);

	return;



}


   

void getencodingmode(int res)
{
    printf("encoding mode is : ");
    if(res==7)
    {
        return("ECI");
    }
    if(res==1)
    {
        return("Numeric");
    }
    if(res==2)
    {
        return("Alphanumeric");
    }
    if(res==4)
    {
        return("8-bit Byte");
    }
    if(res==8)
    {
        return("Kanji");
    }
    if(res==3)
    {
        return("Structured Apped");
    }
    if(res==0)
    {
        return("end of message");
    }
    return;
}







