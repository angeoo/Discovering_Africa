#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "questions.h"

void init_res(struct User u, char* arr[]){
	int res=0;
	if(u.nx>=u.ny){
		if(u.nx>=u.nz){
			res = 1;
		}
		res= 3;
	}
	else {
		if(u.ny>=u.nz){
			res = 2;
		}
		else{
		res = 3;
		}
	}
/*
	switch(res){
		case 1:
			printf("https://www.google.com/search?q=cai    re&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjwzP6jjJP9AhVLTaQEHcsdD-IQ_AUoAnoEC    AEQBA&biw=1916&bih=968&dpr=1");
			return ;
		case 2:
			printf("https://www.google.com/search?q=zan    zibar&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi-gYqajJP9AhVRVaQEHVMiDgMQ_AUoAX    oECAIQAw&biw=1916&bih=968&dpr=1");
			return ;
		case 3 :
			printf("https://www.google.com/search?q=add    is+ababa&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi69bjWjJP9AhU3RKQEHTxnARUQ_AU    oAXoECAEQAw&biw=1916&bih=968&dpr=1");
			return ;
		default :
			printf("Error with init_res\n\n");
			return ;
	}

*/
	char * ville;
	switch(res){
		case 1:
			ville = "Le Caire";
			break;
		case 2:
			ville = "Archipel de Zanzibar";
			break;
		case 3:
			ville = "Addis-Abeba";
			break;
		default:
			printf("Error with init_res");
			break;
	}
	printf("\n\n\n\nThe best destination for you is %s\n\n\nYou can found at more about the site here : \n\n%s",ville,arr[res-1]);
}

struct User init(){

	struct User u;
	//u.name = "";
	u.age = 0;
	u.nbv = 0;//nombre de voyageurs u inclus
	u.nx=0;
	u.ny=0;
	u.nz=0;

	return u;
}


struct User  HelloWorld(int i){

	char * w = "\n\n\n\nWelcome to Discovering Africa\n\nHere's a few questions to help you find a beautiful destination to discover in Africa\n\n";

	printf("%s\n",w);

	struct User user = init();
	char* q1;
	char* q2;

	//x = rural/culturel
	//y = playa et cocktail
	//z = sport et paysage




	do{
		q1 = "Tell us your name : ";
		printf("%s",q1);

		scanf("%s",user.name);

		printf("Nice to meet you %s !\n\n",user.name);
		q2 = "Tell us your age : ";

		printf("%s",q2);

		scanf("%d",&user.age);

		if(user.age<0){
			printf("Try again...\n\n");
		}
		else if(user.age<18){
			printf("Maybe ask your parents %s if they can join the vacation !\n\n",user.name);
		}
	}while(user.age<18);

	/*char *q3 = "Are you travelling alone ? (1 = Yes / 0 = No) : ";

	  int res3=-1;
	  int notConform = 1;

	  do{
	  printf("%s",q3);
	  scanf("%d",res3);

	  if(res3 == 0){
	  user.nbv = 2;
	  notConform=0;
	  break;
	  }
	  else{
	  if(res3[0] == 'N' || res3[0]=='n'){
	  user.nbv=1;
	  notConform=0;
	  break;
	  }
	  else{
	  if(res3[0]=='Q'){
	  break;
	  }
	  }
	  }
	  else{
	  printf("Wrong answer... Try again !\n\n\n");
	  }

	  }while(notConform==1);
	  */
	if(i==1){
		char* q4="";
		q4 = "How many travellers are coming with you ? ";
		int notConform=1;

		do{
			printf("%s",q4);
			scanf("%d",&user.nbv);
			if(user.nbv<0){
				printf("\nWrong answer... Try again !");
				continue;
			}
			notConform=0;
		}while(notConform==1);
	}
	char*q5;

	//x = rural/culturel
	//y = playa et cocktail
	//z = sport et paysage

	q5 = "Choose a favourite food :\n\n\
	      1) Your hometown speciality\n\
	      2) A sweet dessert\n\
	      3) A good sandwich or a burger\n";

	int res5=0;
	do{
		printf("%s\n\n",q5);
		scanf("%d",&res5);

		switch(res5){

			case 1:
				user.nx +=1;
				break;
			case 2:
				user.ny+=1;
				break;
			case 3:
				user.nz+=1;
				break;

			default:
				printf("Wrong answer... Choose again !\n");
				res5=0;
				break;
		}
	}while(res5==0);

	char *q6;
	q6 = "Favourite vacation activity :\n\n\
	      1) Spend time at the beach\n\
	      2) Allnighter downtown\n\
	      3) Visiting and discovering the area\n";
	int res6;

	do{
		printf("%s\n\n",q6);
		scanf("%d",&res6);
		switch(res6){

			//x = rural/culturel
			//y = playa et cocktail
			//z = sport et paysage


			case 1:
				user.nz+=1;
				break;
			case 2:
				user.ny+=1;
				break;
			case 3:
				user.nx+=1;
				break;

			default:
				printf("Wrong answer... Choose again !\n");
				res6=0;
				break;
		}

	}while(res6==0);

	char *q7;
	q7 = "Favourite transportation mode :\n\n\
	      1) Your bike\n\
	      2) Walking\n\
	      3) Your car\n";
	int res7;

	do{
		printf("%s\n\n",q7);
		scanf("%d",&res7);
		switch(res7){

			//x = rural/culturel
			//y = playa et cocktail
			//z = sport et paysage


			case 1:
				user.nz+=1;
				break;
			case 2:
				user.nx+=1;
				break;
			case 3:
				user.ny+=1;
				break;

			default:
				printf("Wrong answer... Choose again !\n");
				res7=0;
				break;
		}

	}while(res7==0);

	char *q8;
	q8 = "Dream location :\n\n\
	      1) Modern loft with 360 view angle over the city\n\
	      2) Nice mountain cabin\n\
	      3) Anything nice and local\n";
	int res8;

	do{
		printf("%s\n\n",q8);
		scanf("%d",&res8);
		switch(res8){

			//x = rural/culturel
			//y = playa et cocktail
			//z = sport et paysage


			case 1:
				user.ny+=1;
				break;
			case 2:
				user.nz+=1;
				break;
			case 3:
				user.nx+=1;
				break;

			default:
				printf("Wrong answer... Choose again !\n");
				res8=0;
				break;
		}

	}while(res8==0);


	char *q9;
	q9 = "Where would you go on a sunday afternoon :\n\n\
	      1) Go shopping\n\
	      2) Walk in the newboorhood\n\
	      3) Anywhere there is food at\n";
	int res9;

	do{
		printf("%s\n\n",q9);
		scanf("%d",&res9);
		switch(res9){

			//x = rural/culturel
			//y = playa et cocktail
			//z = sport et paysage


			case 1:
				user.ny+=1;
				break;
			case 2:
				user.nz+=1;
				break;
			case 3:
				user.nx+=1;
				break;

			default:
				printf("Wrong answer... Choose again !\n");
				res9=0;
				break;
		}

	}while(res9==0);


	return user;
}



struct User HelloTraveler(){
	char * w = "\n\nSince you are not traveling alone, does your compagny wants to take the test ? (Y/N) ";

	char *res=calloc(5,sizeof(char));

	int l;
	printf("%s",w);
	scanf("%s",res);
	l = strlen(res);

	if(l!=1){
		printf("\nWrong answer... Y or N only valid answer");
		free(res);
		return init();
	}
	switch(res[0]){

		case 'Y':
		case 'y':
			free(res);
			return HelloWorld(0);
			break;
		case 'N':
		case 'n':
			free(res);
			return init();
			break;
		default:
			printf("\nWrong answer...Y or N only valid answer\n\n\n\nQuit()\n\n\n");
			break;
	}


	free(res);
	return init();

}
