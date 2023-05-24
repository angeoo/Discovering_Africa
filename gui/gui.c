#include "gui.h"
#include <unistd.h>
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

GtkWidget *homeWindow;
GtkWidget *homeWindowFixed;

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

GtkBox *answer;

// encWindow
GtkWidget *encButton;

// terminalWindow
GtkWidget *buttonExit4;
GtkWidget *nextButton;
GtkImage *term_image;

int size = 21;

// testWindow teshanini la plus sexy
int nx=0,ny=0,nz=0;


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


void display_secondWindow(){

	g_print("\n display_secondWindow()\n");
	gtk_widget_hide(mainWindow);
	gtk_widget_show(secondWindow);

}

void display_decWindow(){

	gtk_widget_hide(secondWindow);
	gtk_widget_show(decWindow);
}

void goToEncode(){

	gtk_widget_hide(decWindow);
	gtk_widget_show(encWindow);
}

void goToDecode(){
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

void display_termWindow(){

	gtk_widget_hide(encWindow);
	gtk_widget_show_all(terminalWindow);

}

void execute_utils(){

	char* request;
	int l = asprintf(&request,"cd ../src/decode && ./utils %s",decImage);

	if(l==-1){
		errx(EXIT_FAILURE,"error while forming request for ./utils");
	}

	system(request);

	FILE *f = fopen("../src/decode/mymessage.txt","r");

	fseek(f,0,SEEK_END);
	long size = ftell(f);
	fseek(f,0,SEEK_SET);

	char * str = malloc(sizeof(char)*(size+1));
	
	fread(str,sizeof(char),size,f);
	str[size]='\0';

	fclose(f);

	GtkWidget *lulu = gtk_label_new(str);
	g_printf("%s",str);
	gtk_box_pack_start(GTK_BOX(answer), lulu, TRUE, TRUE, 0);

	gtk_widget_show_all(decWindow);
}

void goToTest(){

	gtk_widget_hide(homeWindow);
	gtk_widget_show_all(testWindow);
}


void execute_utils_enc(char* word){

	   char* request;
	   int l = asprintf(&request,"cd ../src/decode && ./utils 1 %s",word);

	   if(l==-1){
	   errx(EXIT_FAILURE,"error while forming request for ./utils");
	   }

	   system(request);

	   update_termWindow();
	   
}


void goToQR(){


	int res=0;
	if(nx>ny){
		if(nx>nz){
			res=0;
		}
		else{
			res=2;
		}
	}
	else{
		if(ny>nz){
			res =1;
		}
		else{
			res =2;
		}
	}

	char* links[3] ={
		"https://www.routard.com/guide_voyage_lieu/1498-le_caire_et_ses_environs.html",
		"https://www.zanzibar-voyage.com/",
		"https://www.canalmonde.fr/r-annuaire-tourisme/monde/guides/info-tourisme.php?o=764"
	};


	execute_utils_enc(links[res]);

	GtkWidget *main_image = GTK_WIDGET(gtk_builder_get_object(builder, "background"));
	GdkPixbuf *p = gdk_pixbuf_new_from_file("../src/decode/mask.bmp",NULL);
    int w =300;
    int h = 300;

    GdkPixbuf *rez = gdk_pixbuf_scale_simple(p,w,h,GDK_INTERP_BILINEAR);
    //GtkWidget *rezim = gtk_image_new_from_pixbuf(rez);

	gtk_image_set_from_pixbuf(main_image,rez);

	gtk_widget_hide(testWindow);
	gtk_widget_show_all(mainWindow);
}

void update_termWindow(){

	   GdkPixbuf *p = gdk_pixbuf_new_from_file("../src/decode/mask.bmp",NULL);
	   gtk_image_set_from_pixbuf(term_image,p);
	   g_object_unref(p);
}


void on_submit_button_clicked(GtkButton *button, gpointer *user_data) {
	GtkEntry *entry = GTK_ENTRY(user_data);
	const gchar *sentence = gtk_entry_get_text(entry);
	execute_utils_enc(sentence);
}

void user_cairo(){
	nx+=1;
}

void user_zanzibar(){
	ny+=1;
}

void user_addis(){
	nz+=1;
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

	homeWindow = GTK_WIDGET(gtk_builder_get_object(builder,"homeWindow"));
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

	gtk_widget_override_background_color(terminalWindow,GTK_STATE_NORMAL,&white);
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

	homeWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder,"homeWindowFixed"));

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

	// Create a vertical box to hold the widgets
	answer = GTK_WIDGET(gtk_builder_get_object(builder,"answer_box")); 

	GtkWidget *lulu = gtk_label_new("Here's your decoded message :");
	gtk_box_pack_start(GTK_BOX(answer), lulu, TRUE, TRUE, 0);

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
		if(i!=4 && i%2==0){
			gtk_fixed_put(testWindowFixed,testbox[i],150+i*250,150);
		}
		if(i==4){
			gtk_fixed_put(testWindowFixed,testbox[i],150,450);
		}
		else{
			gtk_fixed_put(testWindowFixed,testbox[i],150+(i-1)*250,300);
		}
		l =  gtk_label_new(q[i*4]); 
		gtk_box_pack_start(testbox[i],l,TRUE, TRUE, 0);
		rep1 = gtk_check_button_new_with_label(q[i*4+1]);
		rep2 = gtk_check_button_new_with_label(q[i*4+2]);
		rep3 = gtk_check_button_new_with_label(q[i*4+3]);

		g_signal_connect(rep1,"toggled",G_CALLBACK(on_rep1_toggled),NULL);
		g_signal_connect(rep2,"toggled",G_CALLBACK(on_rep2_toggled),NULL);
		g_signal_connect(rep3,"toggled",G_CALLBACK(on_rep3_toggled),NULL);

		gtk_box_pack_start(GTK_BOX(testbox[i]),rep1,TRUE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(testbox[i]),rep2,TRUE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(testbox[i]),rep3,TRUE,TRUE,0);
	}

	GtkWidget * send_test = gtk_button_new_with_label("Send");
	gtk_fixed_put(testWindowFixed,send_test,50,50);

	g_signal_connect(send_test,"clicked",G_CALLBACK(on_send_test),NULL);

	// terminalWindow

	//size = 21;
	nextButton = GTK_WIDGET(gtk_builder_get_object(builder,"nextButton"));
	term_image = GTK_IMAGE(gtk_builder_get_object(builder,"term_image"));

	g_signal_connect(nextButton,"clicked",G_CALLBACK(on_nextButton_clicked),NULL);

	// Create a vertical box to hold the widgets
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	//gtk_container_add(GTK_CONTAINER(terminalWindowFixed), box);
	gtk_fixed_put(GTK_WIDGET(terminalWindowFixed),box,450,450);

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
	gtk_widget_show_all(homeWindow);
	// Wait the ui closed
	gtk_main();

	return EXIT_SUCCESS;
}

