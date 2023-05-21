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





   
int bintoint(int* read , int start , int len )
{
    int c= 1 ;
    int res = 0 ; 

    for(int e =start+len-1; e>=start ; e--)
    {
        res = res + c*read[e];
        c=c*2;

    }
    return res;
}


void getencodingmode(int res)
{
    printf("encoding mode is : ");
    if(res==7)
    {
        printf("ECI");
    }
    if(res==1)
    {
        printf("Numeric");
    }
    if(res==2)
    {
        printf("Alphanumeric");
    }
    if(res==4)
    {
        printf("8-bit Byte");
    }
    if(res==8)
    {
        printf("Kanji");
    }
    if(res==3)
    {
        printf("Structured Apped");
    }
    if(res==0)
    {
        printf("end of message");
    }
    return;
}







