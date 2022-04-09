/*
 * linkedContactList.c
 * This file is part of contatos
 * 
 * (c) 2022 - Diogo B Silva
 * 
 * Contatos is free software for contact management.
 * You can redistribute it and/or modify.
 * It is licensed under the MIT License.
*/

#include "linkedContactList.h"
#include <stdlib.h>
#include <string.h>
#define FALSE (0)
#define TRUE (1)

// Create a CONTACT_LIST and load from a file
CONTACT_LIST* contact_list_new_from_file();

// get list size
int contact_list_get_length(CONTACT_LIST* list);

// check if list is empty
int contact_list_is_empty(CONTACT_LIST* list);

// add a new contact to list
int contact_list_add(CONTACT_LIST* list, PERSON person);

// remove a contact from the list
int contact_list_remove(CONTACT_LIST* list, int id);

// get a person from the list by id
PERSON* contact_list_get_person(CONTACT_LIST* list, int id);

// get a person from the list by position
PERSON* contact_list_get_person_by_position(CONTACT_LIST* list, int position);

// save list and free memory
void contact_list_save_and_free(CONTACT_LIST* list);