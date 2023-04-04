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

// --------------------MENU MAIN-----------------------

// Main Menu
GtkWidget *mainMenu;
GtkWidget *secondMenu;
GtkWidget *decMenu;
GtkWidget *encMenu;

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

void display_image(char * path){
	bg_image = GTK_WIDGET(gtk_builder_get_object(builder, "decWindowImage"));
	GdkPixbuf *new_image = gdk_pixbuf_new_from_file_at_size(
			path,
			200,
			200,
			NULL);

	gtk_image_set_from_pixbuf(bg_image,new_image);
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

void execute_utils_enc(){
	
	char* request;
	int l = asprintf(&request,"cd ../src/decode && ./utils %s","1");

	if(l==-1){
		errx(EXIT_FAILURE,"error while forming request for ./utils");
	}

	system(request);
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

	// Load signals from builder
	gtk_builder_connect_signals(builder, NULL);

	// Define all widgets from builder
	mainWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindowFixed"));
	secondWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "secondWindowFixed"));
	decWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "decWindowFixed"));
	encWindowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "encWindowFixed"));

	mainMenu = GTK_WIDGET(gtk_builder_get_object(builder, "mainMenu"));
	secondMenu = GTK_WIDGET(gtk_builder_get_object(builder, "secondMenu"));
	decMenu = GTK_WIDGET(gtk_builder_get_object(builder, "decMenu"));
	encMenu = GTK_WIDGET(gtk_builder_get_object(builder, "encMenu"));

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

	// Display the ui
	gtk_widget_show(mainWindow);

	// Wait the ui closed
	gtk_main();

	return EXIT_SUCCESS;
}

