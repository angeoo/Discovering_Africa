#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "questions.h"

struct User init_(){
	
	struct User u;
	u.name = "";
	u.age = 0;
	u.nx=0;
	u.ny=0;
	u.nz=0;

	return u;
}


struct User  HelloWorld(char* buffer){

	char * w = "Welcome to Discovering Africa\n\nHere's a few questions to help you find a beautiful destination to discover in Africa\n\n";

	int res;
	
	char * q1 = "Tell us your name : \n";
	//while(){ //tant q user ne press pas Entree
	res = write(STDOUT_FILENO, buffer, q1);
	//}

	struct User user = init();
	char * name = read(STDIN_FILENO,q1, res);

	user.name = name;

	return user;
}
