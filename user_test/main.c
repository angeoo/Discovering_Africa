#include "questions.h"
#include <stdio.h>
#include <err.h>


int main(){
	
	char buf[32];
	struct User u = HelloWorld(buf);
	printf("%s : \n\n", u.name);


	printf("nx = rural : %d\n\nny = playafiesta : %d\n\nnz = aventure : %d\n\n",u.nx,u.ny,u.nz);


	return 0;
}
