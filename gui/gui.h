#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <gtk/gtk.h>

void goToTest();

void displayimage(char* path);

void display_secondWindow();

void display_decWindow();

void goToEncode();

void goToDecode();

void display_encWindow();

void display_termWindow();

void display_pretraitement_button();

void execute_utils();

void execute_utils_enc();

void on_rep1_toggled(GtkWidget *widget, gpointer *userdata);

void on_rep2_toggled(GtkWidget *widget, gpointer *userdata);

void on_rep3_toggled(GtkWidget *widget, gpointer *userdata);

void user_cairo();

void user_zanzibar();

void user_addis();

void on_send_test(GtkWidget *widget, gpointer *userdata);

void update_termWindow();

void on_nextButton_clicked(GtkWidget *widget,gpointer *userdata);

void goToQR();

void on_buttonSave_activate(GtkWidget *widget, gpointer *userdata);

void on_buttonReload_activate(GtkWidget *widget, gpointer *userdata);

void on_buttonExit_activate(GtkWidget *widget, gpointer *userdata);


void on_buttonWebsite_activate(GtkWidget *widget, gpointer *userdata);
 

#endif  
