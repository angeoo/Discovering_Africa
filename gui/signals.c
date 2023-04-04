#include "gui.h"

// Main menu

void on_buttonSave_activate(GtkWidget *widget, gpointer *userdata)
{
	g_print("Button Save clicked !\n");
}

void on_buttonLoad_activate(GtkWidget *widget,gpointer *userdata)
{
	GtkWidget *p_dialog = NULL;
	p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			"document-cancel", GTK_RESPONSE_CANCEL,
			"document-open", GTK_RESPONSE_ACCEPT,
			NULL);

	gchar *filename = NULL;
	if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
		g_print("%s\n",filename);

		display_image(filename);
	}
	gtk_widget_destroy (p_dialog);

}

void on_startButton_activate(GtkWidget *widget,gpointer *userdata){
	g_print("\non_startButton_activated()\n");
	system("cd .. && make");
	g_print("\nmake all done\n");
	display_secondWindow();
}

void on_buttonExit_activate(GtkWidget *widget,gpointer *userdata)
{
	g_print("Button Exit clicked !\n");
	exit(0);
}

// About menu

void on_buttonWebsite_activate(GtkWidget *widget,gpointer *userdata)
{
	g_print("button Website clisked !\n");
	system("chromium https://fr.wikipedia.org/wiki/Code_QR");
}

// secondWindow

void on_decButton_activate(GtkWidget *widget,gpointer *userdata){
	
	g_print("Decoder clicked !\n");
	display_decWindow();
}
/*
void on_encButton_clicked(GtkWidget *widget,gpointer *userdata){
	g_print("Encoder clicked !\n");
	display_encWindow();
}*/


// decWindow

void on_decodeButton_clicked(GtkWidget *widget,gpointer *userdata){


	execute_utils();

}





















