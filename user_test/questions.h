#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <err.h>

struct User{

	char name[100];
	int age, nbv;
	int nx,ny,nz;
};

int init_res(struct User u);
struct User init();
struct User HelloWorld();
struct User HelloTraveler();


