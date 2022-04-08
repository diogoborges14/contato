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

int id = 0;
USER *headUser; // Where my list start
USER *auxiliarUser;

void showMsgBox(char text[100], char secondary_text[100], char icon_name[100])
{
    g_object_set(msgBox, "text", text, NULL);
    g_object_set(msgBox, "secondary_text", secondary_text, NULL);
    g_object_set(msgBox, "icon_name", icon_name, NULL);

    gtk_widget_show(GTK_WIDGET(msgBox));
    gtk_dialog_run(GTK_DIALOG(msgBox));
    gtk_widget_hide(GTK_WIDGET(msgBox));
}

void on_btnSearch_clicked(){}

void on_btnGoRegister_clicked(){
    gtk_stack_set_visible_child_name(viewStack, "view_register"); // Set "view_register" as visible
}

void on_btnReloadList_clicked(){}

void on_btnAddRegister_clicked()
{
    char txt[50] = "\0";
    const char *nome     = gtk_entry_get_text(inpName);
    const char *telefone = gtk_entry_get_text(inpPhoneNumber);
    const char *email    = gtk_entry_get_text(inpEmail);

    if(g_str_equal(nome, "")){
        showMsgBox("Atenção!", "Nome é obrigatório", "dialog-error");
    }else if(g_str_equal(email, "")){
        showMsgBox("Atenção!", "Email é obrigatório", "dialog-error");
    }else{
        /* save the user */
        id++;
        auxiliarUser->id = id;
        g_strlcpy(auxiliarUser->nome,     nome,    100);
        g_strlcpy(auxiliarUser->telefone, telefone, 15);
        g_strlcpy(auxiliarUser->email,    email,   100);

        g_snprintf(txt, 50, "Usuário %s cadastrado com sucesso.", nome);
        showMsgBox("Aviso", txt, "dialog-emblem-default");

        /* alloc space for next user */
        auxiliarUser->next = (USER*)malloc(sizeof(USER));
        auxiliarUser = auxiliarUser->next; // auxiliarUser become the newlest allocated new_next user
    }
}

void on_btnGoBack_clicked()
{
    gtk_stack_set_visible_child_name(viewStack, "view_initial"); // Set "view_initial" as visible
}


void startApplication(GtkApplication *app, gpointer user_data)
{
    headUser = (USER*)malloc(sizeof(USER));
    auxiliarUser = headUser;

    // Getting widgets from view
    builder          = gtk_builder_new_from_file("include/contatos.ui");
    mainWindow       = GTK_WINDOW(gtk_builder_get_object(builder, "mainWindow"));
    viewStack        = GTK_STACK(gtk_builder_get_object(builder, "viewStack"));
    contactList      = GTK_LIST_STORE(gtk_builder_get_object(builder, "contactList"));
    msgBox           = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "msgBox"));
    inpName          = GTK_ENTRY(gtk_builder_get_object(builder, "inpName"));
    inpPhoneNumber   = GTK_ENTRY(gtk_builder_get_object(builder, "inpPhoneNumber"));
    inpEmail         = GTK_ENTRY(gtk_builder_get_object(builder, "inpEmail"));

    gtk_builder_add_callback_symbols(
        builder,
        "on_btnSearch_clicked",       G_CALLBACK(on_btnSearch_clicked),
        "on_btnGoRegister_clicked",       G_CALLBACK(on_btnGoRegister_clicked),
        "on_btnReloadList_clicked",    G_CALLBACK(on_btnReloadList_clicked),
        "on_btnGoBack_clicked", G_CALLBACK(on_btnGoBack_clicked),
        "on_btnAddRegister_clicked",        G_CALLBACK(on_btnAddRegister_clicked),
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

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
