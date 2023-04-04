#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <gtk/gtk.h>

void display_image(char* path);

void display_secondWindow();

void display_decWindow();

void display_pretraitement_button();

void execute_utils();

void on_buttonSave_activate(GtkWidget *widget, gpointer *userdata);

void on_buttonReload_activate(GtkWidget *widget, gpointer *userdata);

void on_buttonExit_activate(GtkWidget *widget, gpointer *userdata);


void on_buttonWebsite_activate(GtkWidget *widget, gpointer *userdata);
 

#endif  
