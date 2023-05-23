#include "gui.h"

// --------------------WINDOWS-------------------------
GtkWidget *mainWindow;
GtkWidget *mainWindowFixed;

GtkWidget *secondWindow;
GtkWidget *secondWindowFixed;

GtkWidget *decWindow;
GtkWidget *decWindowFixed;

GtkWidget *encWindow;
GtkWidget *encWindowFixed;

GtkWidget *terminalWindow;
GtkWidget *terminalWindowFixed;

GtkWidget *testWindow;
GtkWidget *testWindowFixed;
// --------------------MENU MAIN-----------------------

// Main Menu
GtkWidget *mainMenu;
GtkWidget *secondMenu;
GtkWidget *decMenu;
GtkWidget *encMenu;
GtkWidget *terminalMenu;
// Buttons

// mainWindow
GtkWidget *buttonSave;
GtkWidget *buttonLoad;
GtkWidget *buttonExit;
GtkWidget *startButton;

// secondWindow
GtkWidget *buttonExit2;
GtkWidget *genButton;
GtkWidget *decButton;

// decWindow
GtkWidget *buttonLoad1;
GtkWidget *preButton;
char * decImage;

// encWindow
GtkWidget *encButton;

// terminalWindow
GtkWidget *buttonExit4;
GtkWidget *nextButton;
GtkWidget *mat_image;
int size = 21;


// Bakcground image
GtkWidget *bg_image;

// ---------------------ABOUT MENU-----------------------

GtkWidget *aboutMenu;
GtkWidget *aboutMenu2;
GtkWidget *aboutMenuDec;

// Cat 1
GtkWidget *buttonWebsite;
GtkWidget *buttonWebsite2;


// Builder 
GtkBuilder *builder;

void displayimage(char * path){
	bg_image = GTK_WIDGET(gtk_builder_get_object(builder, "decWindowImage"));
	GdkPixbuf *new_image = gdk_pixbuf_new_from_file_at_size(
			path,
			200,
			200,
			NULL);

	gtk_image_set_from_pixbuf(GTK_IMAGE(bg_image),new_image);
	decImage = path;
	g_print("\n\ndecImage maj : %s\n\n",path);
	display_pretraitement_button();

}

void display_mat(char* path){
	mat_image = gtk_image_new_from_file("../image/fillgrid.bmp");

}

void display_secondWindow(){

	g_print("\n display_secondWindow()\n");
	gtk_widget_hide(mainWindow);
	gtk_widget_show(secondWindow);

}

void display_decWindow(){

	g_print("\n display_decWindow()\n");
	gtk_widget_hide(secondWindow);
	gtk_widget_show(decWindow);
}

void goToEncode(){

	g_print("\n Let's encode\n");
	gtk_widget_hide(decWindow);
	gtk_widget_show(encWindow);
}

void goToDecode(){
	g_print("\n Let's decode\n");
	gtk_widget_hide(encWindow);
	gtk_widget_show(decWindow);
}

void display_pretraitement_button(){

	gtk_widget_show(preButton);
}

void display_encWindow(){

	gtk_widget_hide(secondWindow);
	gtk_widget_show(encWindow);
}

void execute_utils(){

	char* request;
	int l = asprintf(&request,"cd ../src/decode && ./utils %s",decImage);

	if(l==-1){
		errx(EXIT_FAILURE,"error while forming request for ./utils");
	}

	system(request);


}

void execute_utils_enc(char* word){
	/*
	   char* request;
	   int l = asprintf(&request,"cd ../src/decode && ./utils %s","1");

	   if(l==-1){
	   errx(EXIT_FAILURE,"error while forming request for ./utils");
	   }

	   system(request);
	   */


/*

	//creer une matrice
	int* created = creer_matric();

	//ajouter les neg
	int* negcreated = mat_data(created,21);

	//getting the word as a string
	//printf("enter your word :  ");
	//char* word  = malloc(sizeof(char)*100);
	//scanf("%s",word);

	int c=0;
	while(word[c]!='\0')
	{
		c=c+1;
	}
	int size =21;


	int totals =8 * c + 12;
	//word to binary
	int* res2 = BitStream(word);
	int* county = malloc(sizeof(int));
	*county = 0;
	int* res = pad_codewords(res2,totals,county);
	totals += *county*8;


	parser* toput = malloc(sizeof(parser));
	toput->x=size-1;
	toput->y=size-1;
	toput->resultat = res;
	toput->count=0;
	toput->xs = malloc(totals*sizeof(int));
	toput->ys = malloc(totals*sizeof(int));
	putall(toput , negcreated , totals, size);
	parser* toget = malloc(sizeof(parser));
	toget->x=size-1;
	toget->y=size-1;
	toget->resultat=calloc(totals, sizeof(int));
	toget->count=0;
	toget->xs=malloc(totals*sizeof(int));
	toget->ys=malloc(totals*sizeof(int));
	toget->finalmsg=calloc(totals+1,sizeof(char));
	toget->finalmsg[totals]='\0';
	getall(toget,negcreated,totals-(*county*8),size);

	int* finres = creer_matric();

	RemoveNeg(negcreated , finres,size);


	getchar();
	

	SDL_Surface *output = SDL_CreateRGBSurface(0,size*54,size*54,32,0,0,0,0);
	Uint32 white = SDL_MapRGB(output->format,255,255,255);

	for(int i=0;i<size*54;i++){
		for(int j=0;j<54*size;j++){
			put_pixel(output,i,j,white);
		}
	}

	fillgrid(output,finres,size);

	SDL_SaveBMP(output,"fillgrid.bmp");
	free(mat);
	free(output);

	free(created);
	free(negcreated);
	free(word);
*/
}

void on_submit_button_clicked(GtkButton *button, gpointer *user_data) {
	GtkEntry *entry = GTK_ENTRY(user_data);
	const gchar *sentence = gtk_entry_get_text(entry);
	execute_utils_enc(sentence);
}



int main(int argc, char **argv)
{
	// Init gtk
	gtk_init(&argc, &argv);

	// Load ui configuration into the builder
	builder = gtk_builder_new_from_file("interface/UI.glade");

	// Load the windows
	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));

	secondWindow = GTK_WIDGET(gtk_builder_get_object(builder,"secondWindow"));

	decWindow = GTK_WIDGET(gtk_builder_get_object(builder,"decWindow"));

	encWindow = GTK_WIDGET(gtk_builder_get_object(builder,"encWindow"));

	terminalWindow = GTK_WIDGET(gtk_builder_get_object(builder,"terminalWindow"));


	testWindow =  GTK_WIDGET(gtk_builder_get_object(builder,"testWindow"));

	// Background color
	GdkRGBA white;
	white.red = 0xfff;
	white.green = 0xfff;
	white.blue = 0xfff;
	white.alpha = 1.0;

	gtk_widget_override_background_color(mainWindow,GTK_STATE_NORMAL,&white);
	gtk_widget_override_background_color(secondWindow,GTK_STATE_NORMAL,&white);
	gtk_widget_override_background_color(decWindow,GTK_STATE_NORMAL,&white);
	gtk_widget_override_background_color(encWindow,GTK_STATE_NORMAL,&white);

	// Exit ui when user closed the window
	g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(secondWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(decWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(encWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(terminalWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

	// Load signals from builder
	gtk_builder_connect_signals(builder, NULL);

	// Define all widgets from builder
	mainWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindowFixed"));
	secondWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "secondWindowFixed"));
	decWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "decWindowFixed"));
	encWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "encWindowFixed"));

	terminalWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder,"terminalWindowFixed"));

	testWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder,"testWindowFixed"));

	mainMenu = GTK_WIDGET(gtk_builder_get_object(builder, "mainMenu"));
	secondMenu = GTK_WIDGET(gtk_builder_get_object(builder, "secondMenu"));
	decMenu = GTK_WIDGET(gtk_builder_get_object(builder, "decMenu"));
	encMenu = GTK_WIDGET(gtk_builder_get_object(builder, "encMenu"));

	terminalMenu = GTK_WIDGET(gtk_builder_get_object(builder,"terminalMenu"));

	// Buttons

	// main
	buttonSave = GTK_WIDGET(gtk_builder_get_object(builder, "buttonSave"));
	buttonLoad = GTK_WIDGET(gtk_builder_get_object(builder, "buttonLoad"));
	buttonExit = GTK_WIDGET(gtk_builder_get_object(builder, "buttonExit"));
	startButton = GTK_WIDGET(gtk_builder_get_object(builder, "startButton"));

	// second
	buttonExit2 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonExit2"));
	genButton = GTK_WIDGET(gtk_builder_get_object(builder, "genButton"));
	decButton = GTK_WIDGET(gtk_builder_get_object(builder, "decButton"));

	// dec
	buttonLoad1 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonLoad1"));
	preButton = GTK_WIDGET(gtk_builder_get_object(builder, "preButton"));

	// enc
	encButton = GTK_WIDGET(gtk_builder_get_object(builder, "encButton"));

	// testWindow
	
	GtkWidget* testbox[5];

	char* q[]={"Choose a favourite food :",
		"Your hometown speciality",
		"A sweet dessert",
		"A good sandwich or a burger",
		"Favourite vacation activity :",
		"Visiting and discovering the area",
		"Spend time at the beach",
		"Allnighter downtown",
		"Favourite transportation mode :",
		"Walking",
		"Your car",
		"Your bike",
		"Dream location :",
		"Anything nice and local",
		"Modern loft with 360 view angle over the city",
		"Nice mountain cabin",
		"Where would you go on a sunday afternoon :",
		"Anywhere there is food at",
		"Go shopping",
		"Walk in the newboorhood"};

	GtkWidget *l,*rep1,*rep2,*rep3;
	
	for(int i=0;i<5;i++){

	testbox[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
	if(i%2==0){
	gtk_fixed_put(testWindowFixed,testbox[i],150+i*250,150);
	}
	else{
	gtk_fixed_put(testWindowFixed,testbox[i],150+(i-1)*250,300);
	}
	l =  gtk_label_new(q[i*4]); 
	gtk_box_pack_start(testbox[i],l,TRUE, TRUE, 0);
	rep1 = gtk_check_button_new_with_label(q[i*4+1]);
	rep2 = gtk_check_button_new_with_label(q[i*4+2]);
	rep3 = gtk_check_button_new_with_label(q[i*4+3]);

	gtk_box_pack_start(GTK_BOX(testbox[i]),rep1,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(testbox[i]),rep2,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(testbox[i]),rep3,TRUE,TRUE,0);
	}



	// terminalWindow

	//size = 21;
	nextButton = GTK_WIDGET(gtk_builder_get_object(builder,"nextButton"));

	// Create a vertical box to hold the widgets
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	//gtk_container_add(GTK_CONTAINER(terminalWindowFixed), box);
	gtk_fixed_put(terminalWindowFixed,box,150,150);

	// Create a label
	GtkWidget *label = gtk_label_new("Enter a sentence:");
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

	// Create an entry widget
	GtkWidget *entry = gtk_entry_new();
	//gtk_fixed_put(terminalWindowFixed,entry,150,150);
	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);

	// Create a submit button
	GtkWidget *submit_button = gtk_button_new_with_label("Submit");
	//gtk_fixed_put(terminalWindowFixed,submit_button,250,150);
	g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_clicked), entry);
	gtk_box_pack_start(GTK_BOX(box), submit_button, TRUE, TRUE, 0);

	/*
	   GtkWidget* test[size*size];

	   char name[] = ".";

	   for(int i = 0;i<size;i++){
	//me[0] = '0'+i;
	for(int j =0;j<size;j++){

	test[i*size+j] = gtk_button_new_with_label(name);
	gtk_widget_set_size_request(test[i*size+j],30,30);
	gtk_fixed_put(terminalWindowFixed,test[i*size+j],50+i*55,j*45+50);
	gtk_widget_show(test[i*size+j]);
	}
	}*/
	//k_widget_show(mainWindow);
	gtk_widget_show_all(testWindow);
	// Wait the ui closed
	gtk_main();

	return EXIT_SUCCESS;
}

