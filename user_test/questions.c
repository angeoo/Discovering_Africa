#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "questions.h"

struct User init(){
	
	struct User u;
	u.name = "";
	u.age = 0;
	u.nx=0;
	u.ny=0;
	u.nz=0;

	return u;
}


struct User  HelloWorld(){

	char * w = "Welcome to Discovering Africa\n\nHere's a few questions to help you find a beautiful destination to discover in Africa\n\n";

	printf("%s\n",w);
	char * q1 = "Tell us your name : \n";
	//while(){ //tant q user ne press pas Entree
	printf("%s\n",q1);
	//}

	struct User user = init();
	char name[100];
	scanf("%s",name);

	user.name = name;

	return user;
}
