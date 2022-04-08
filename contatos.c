/*
 * contatos.c
 * This file is part of contatos
 * 
 * (c) 2022 - Diogo B Silva
 * 
 * Contatos is free software for contact management.
 * You can redistribute it and/or modify.
 * It is licensed under the MIT License.
*/

#include <gtk/gtk.h>
#include "include/dynamicList.h"
#include <stdlib.h>

/*****   Widgets   *****/
GtkBuilder       *builder;
GtkWindow        *mainWindow;
GtkStack         *viewStack;
GtkListStore     *contactList;
GtkMessageDialog *msgBox;
GtkEntry         *inpName;
GtkEntry         *inpPhoneNumber;
GtkEntry         *inpEmail;

void startApplication(GtkApplication *app, gpointer user_data)
{

    // Getting widgets from view
    builder          = gtk_builder_new_from_file("include/contatos.ui");
    mainWindow       = GTK_WINDOW(gtk_builder_get_object(builder, "mainWindow"));
    viewStack        = GTK_STACK(gtk_builder_get_object(builder, "viewStack"));
    contactList      = GTK_LIST_STORE(gtk_builder_get_object(builder, "contactList"));
    msgBox           = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "msgBox"));
    inpName          = GTK_ENTRY(gtk_builder_get_object(builder, "inpName"));
    inpPhoneNumber   = GTK_ENTRY(gtk_builder_get_object(builder, "inpPhoneNumber"));
    inpEmail         = GTK_ENTRY(gtk_builder_get_object(builder, "inpEmail"));


    /* Set the app to show on Window. The application will be kept alive for at least as long as it has
      any windows associated with it (see g_application_hold() for a way to keep it alive without windows). */
    gtk_window_set_application(mainWindow, app);

    gtk_widget_show_all(GTK_WIDGET(mainWindow));
    g_object_unref(builder);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.github.diogoborges14.contatos", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(startApplication), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}
