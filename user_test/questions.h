#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


struct User{

	char* name;
	char* age;
	int nx,ny,nz;
};

struct User init();
struct User HelloWorld();

