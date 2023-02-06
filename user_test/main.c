#include "questions.h"
#include <stdio.h>
#include <err.h>


int main(){
	
	char buf[32];
	struct User u = HelloWorld(buf);

	printf("%s\n", u.name);

	return 0;
}
