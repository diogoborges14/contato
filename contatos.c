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
#include "include/linkedContactList.h"
#include <stdlib.h>

CONTACT_LIST* contactListDB;

/*****   Widgets   *****/
GtkBuilder         *builder;
GtkWindow          *mainWindow;
GtkStack           *viewStack;
GtkTreeView        *treeView;
GtkTreeModelFilter *filteredList;
GtkListStore       *contactsModel;
GtkMessageDialog   *msgBox;
GtkSearchEntry     *inpSearch;
GtkEntry           *inpName;
GtkEntry           *inpPhoneNumber;
GtkEntry           *inpEmail;


void showMsgBox(char text[100], char secondary_text[100], char icon_name[100])
{
    g_object_set(msgBox, "text", text, NULL);
    g_object_set(msgBox, "secondary_text", secondary_text, NULL);
    g_object_set(msgBox, "icon_name", icon_name, NULL);

    gtk_widget_show(GTK_WIDGET(msgBox));
    gtk_dialog_run(GTK_DIALOG(msgBox));
    gtk_widget_hide(GTK_WIDGET(msgBox));
}

// Decide if a row should or should not be visible
gboolean shouldBeVisible(GtkTreeModel *model, GtkTreeIter  *iter, gpointer data)
{
    gboolean visible = FALSE;
    char *nameStr;
    char *searchTerm = (char *)gtk_entry_get_text(GTK_ENTRY(inpSearch));

    gtk_tree_model_get(model, iter,
                       1, &nameStr, // from column 1 get data and put on nameStr
                       -1);

    if( (strlen(searchTerm) == 0) ||
        (nameStr && strncasecmp(nameStr, searchTerm, strlen(searchTerm)) == 0)
    ){
        visible = TRUE;
    }

    g_free(nameStr);

    return visible;
}

void on_inpSearch_changed()
{
    // Filter showing results according to the shouldBeVisible() function
    gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(filteredList));
}

void on_btnGoRegister_clicked()
{
    gtk_stack_set_visible_child_name(viewStack, "view_register"); // Set "view_register" as visible
}

void on_btnRemove_clicked()
{
    int              selectedId = 0;
    GtkTreeIter      iter;
    GtkTreeModel     *model;
    GtkTreeSelection *selectionObj = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeView));

    int isValid = gtk_tree_selection_get_selected(selectionObj, &model, &iter);

    if(isValid){
        gtk_tree_model_get(model, &iter,
                           0, &selectedId, // get from column 0
                           -1);
        contact_list_remove(contactListDB, selectedId); // Remove from storage

        gtk_list_store_remove(contactsModel, &iter); // Remove from view
    }
}

void on_btnReloadList_clicked()
{
    PERSON *tmpPerson;
    GtkTreeIter iter;
    gtk_list_store_clear(contactsModel);

    // Populate list_store with data from dynamic list
    for(int i=1; i <= contact_list_get_length(contactListDB); i++){
        tmpPerson = contact_list_get_person_by_position(contactListDB, i);

        // Copy to TreeView model
        //if(tmpPerson){
            gtk_list_store_append(contactsModel, &iter);
            gtk_list_store_set(contactsModel, &iter,
                            0, tmpPerson->id,
                            1, tmpPerson->name,
                            2, tmpPerson->phone,
                            3, tmpPerson->email,
                            -1);
        //}
    }
}

void on_btnAddRegister_clicked()
{
    char txt[50] = "\0";
    PERSON person;
    const char *name     = gtk_entry_get_text(inpName);
    const char *phoneNum = gtk_entry_get_text(inpPhoneNumber);
    const char *email    = gtk_entry_get_text(inpEmail);

    if(g_str_equal(name, "")){
        showMsgBox("Atenção!", "Nome é obrigatório", "dialog-error");
    }else if(g_str_equal(email, "")){
        showMsgBox("Atenção!", "Email é obrigatório", "dialog-error");
    }else{
        /* save the person */
        g_strlcpy(person.name,     name,    100);
        g_strlcpy(person.phone,    phoneNum, 15);
        g_strlcpy(person.email,    email,   100);
        contact_list_add(contactListDB, person);

        g_snprintf(txt, 50, "Contato %s salvo com sucesso.", name);
        showMsgBox("Aviso", txt, "dialog-emblem-default");
    }
}

void on_btnGoBack_clicked()
{
    gtk_stack_set_visible_child_name(viewStack, "view_initial"); // Set "view_initial" as visible

    on_btnReloadList_clicked();
}

void startApplication(GtkApplication *app, gpointer user_data)
{
    contactListDB = contact_list_new_from_file("contatos.ini");

    // Getting widgets from view
    builder          = gtk_builder_new_from_file("include/contatos.ui");
    mainWindow       = GTK_WINDOW(gtk_builder_get_object(builder, "mainWindow"));
    treeView         = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeView"));
    inpSearch        = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "inpSearch"));
    viewStack        = GTK_STACK(gtk_builder_get_object(builder, "viewStack"));
    contactsModel    = GTK_LIST_STORE(gtk_builder_get_object(builder, "contactList"));
    msgBox           = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "msgBox"));
    inpName          = GTK_ENTRY(gtk_builder_get_object(builder, "inpName"));
    inpPhoneNumber   = GTK_ENTRY(gtk_builder_get_object(builder, "inpPhoneNumber"));
    inpEmail         = GTK_ENTRY(gtk_builder_get_object(builder, "inpEmail"));

    gtk_builder_add_callback_symbols(
        builder,
        "on_inpSearch_changed",      G_CALLBACK(on_inpSearch_changed),
        "on_btnGoRegister_clicked",  G_CALLBACK(on_btnGoRegister_clicked),
        "on_btnRemove_clicked",      G_CALLBACK(on_btnRemove_clicked),
        "on_btnReloadList_clicked",  G_CALLBACK(on_btnReloadList_clicked),
        "on_btnGoBack_clicked",      G_CALLBACK(on_btnGoBack_clicked),
        "on_btnAddRegister_clicked", G_CALLBACK(on_btnAddRegister_clicked),
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    // Set a filter to the treeView
    GtkTreeModel *actualModel = gtk_tree_view_get_model(treeView);
    filteredList = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(actualModel, NULL));
    gtk_tree_model_filter_set_visible_func(filteredList, shouldBeVisible, NULL, NULL);

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
