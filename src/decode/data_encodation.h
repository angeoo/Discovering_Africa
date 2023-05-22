
#ifndef DATA_ENCODATION_H
#define DATA_ENCODATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int *BitStream(char *input);

int* appendArray(int* dest, int src[], int destSize, int srcSize);
int* pad_codewords(int* bitstream,size_t len,int* count);



#endif
