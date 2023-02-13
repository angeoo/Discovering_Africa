#include "questions.h"
#include <stdio.h>
#include <err.h>


int main(){

	char* array[]={
		"https://www.tripadvisor.fr/Tourism-g294201-Cairo_Cairo_Governorate-Vacations.html",
		"https://www.tripadvisor.fr/Tourism-g482884-Zanzibar_Island_Zanzibar_Archipelago-Vacations.html",
		"https://www.tripadvisor.fr/Tourism-g293791-Addis_Ababa-Vacations.html"};

	struct User u = HelloWorld(1);

	init_res(u,array);

	int c = u.nbv;

	struct User p1;
	while(c>0){
		p1 = HelloTraveler();
		c--;
		if(p1.age==0){
			c=0;
		}
		else{
			init_res(p1,array);
		}
	}
	return 0;
}
