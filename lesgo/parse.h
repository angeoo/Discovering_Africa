#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "print.h"


void getup(parser* w , int* arrd , int tot , int qrsize);

void getdown(parser* w , int* arrd ,int tot , int qrsize);

void getall(parser* w , int* arrd , int tot , int qrsize);

void putup(parser* w , int* arrd , int tot , int qrsize);

void putdown(parser* w , int* arrd , int tot , int qrsize);

void putall(parser* w , int* arrd , int tot , int qrsize);

void storemsg(parser* w);

#endif
