#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//to get the struct parser

// qrmat  : 1D array representing the QR-Code
// qrsize : lenght or width of the qrcode
// w      : parser containg all the informations

typedef struct
{
        int   x;           //position  X  of the parser
        int   y;           //position  Y  of the parser
        int*  resultat;    //array containg all the value parsed.
        int   count;       //number of cases  parsed
        int*  xs;          //array containing all the x parsed.
        int*  ys;          //array containing all the y parsed.
        int   tot;         //total number of cases that must be parsed. 
        char* finalmsg;    //result of the final message
}parser;
 
void NormalPrint(int* qrmat , int qrsize , parser* w);

void parseprint(parser* w);






#endif
