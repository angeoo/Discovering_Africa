#include "questions.h"
#include <stdio.h>
#include <err.h>


int main(){

	struct User u = HelloWorld();
	printf("%s : \n\n", u.name);

	int res = init_res(u);
	do{
		switch(res){
			case 1:
				printf("https://www.google.com/search?q=caire&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjwzP6jjJP9AhVLTaQEHcsdD-IQ_AUoAnoECAEQBA&biw=1916&bih=968&dpr=1");
				break;
			case 2:
				printf("https://www.google.com/search?q=zanzibar&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi-gYqajJP9AhVRVaQEHVMiDgMQ_AUoAXoECAIQAw&biw=1916&bih=968&dpr=1");
				break;
			case 3:
				printf("https://www.google.com/search?q=addis+ababa&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi69bjWjJP9AhU3RKQEHTxnARUQ_AUoAXoECAEQAw&biw=1916&bih=968&dpr=1");
				break;
			default:
				printf("Error with init_res\n\n");
				return 0;
		}
		if(u.nbv>0){
			struct User p1 = HelloTraveler();


			if(p1.age==0){
				break;
			}}

		u.nbv=u.nbv-1;
	}while(u.nbv>0);


	/*	printf("nx = rural : %d\n\nny = playafiesta : %d\n\nnz = aventure : %d\n\n",u.nx,u.ny,u.nz);
	*/

	return 0;
}
