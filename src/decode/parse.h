#ifndef PARSE_H
#define PARSE_H
typedef struct
{
	int x; 
	int y;
	int* resultat;
	int count;
	int* xs;
	int* ys;
	int tot;
	int lens;
	char* finalmsg;

}parser;


void Prettprint(int* arrd ,int qrsize,parser w);

void getall(parser* w , int* arrd , int tot , int qrsize);

int bintoint(int* read , int start , int len) ;

void getencodingmode(int res);

#endif
