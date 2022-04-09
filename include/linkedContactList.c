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
CONTACT_LIST* contact_list_new_from_file(){
    CONTACT_LIST* list = (CONTACT_LIST*) malloc(sizeof(CONTACT_LIST));
    if(list != NULL){ // was successfully allocated?
        list->start = NULL;
        list->end = NULL;
        list->quantity = 0;
        list->lastId = 0;
    }
    return list;
}

// get list size
int contact_list_get_length(CONTACT_LIST* list){
    if(list == NULL) // does the list not exist?
        return 0;
    else
        return list->quantity;
}

// check if list is empty
int contact_list_is_empty(CONTACT_LIST* list){
    if(list == NULL) // does the list not exist?
        return TRUE;
    else if(list->quantity == 0)
        return TRUE;
    else
        return FALSE; // there is at least one node
}

// add a new contact to list
int contact_list_add(CONTACT_LIST* list, PERSON person){
    if(list == NULL) return 0; // list does not exist

    NODE *personNode = (NODE*) malloc(sizeof(NODE));
    if(personNode == NULL) return 0;

    person.id = list->lastId + 1;
    personNode->person = person;
    personNode->next   = NULL;

    if(contact_list_is_empty(list)){ // first node to add
        list->start = personNode;
        list->end = personNode;
    }else{
        // search for where to add the person
        NODE *previousNode, *auxNode = list->start;
        while(
            (auxNode != NULL) &&
            (strcasecmp(auxNode->person.name, person.name) < 0) // compare names to know where to put int alphabetical order 
        ){
            previousNode = auxNode;
            auxNode = auxNode->next;
        }

        // Check search results
        if(auxNode == list->start){ // we are at the start of the list?
            list->start = personNode; // personNode
            personNode->next = auxNode; // personNode -> auxNode → nextNode ...
        }else{
            previousNode->next = personNode; // ... previousNode → personNode
            personNode->next = auxNode; // ... previousNode → personNode → auxNode ...

            if(auxNode == NULL){ // wa are at the end of the list?
                list->end = personNode;
            }
        }
    }
    list->quantity++;
    list->lastId++;

    return 1; // 1 person successfully added
}

// remove a contact from the list
int contact_list_remove(CONTACT_LIST* list, int id){
    if(list == NULL)
        return FALSE; // list does not exist
    if(contact_list_is_empty(list))
        return FALSE;

    // search for where is the person
    NODE *previousNode, *auxNode = list->start;
    while(
        (auxNode->next != NULL) &&
        (auxNode->person.id != id)
    ){
        previousNode = auxNode;
        auxNode = auxNode->next;
    }

    // Check search results
    if(auxNode->person.id != id)
        return 0; // not found

    // If found
    if(contact_list_get_length(list) == 1){ // remove the only element
        list->start = NULL;
        list->end = NULL;
    }else{
        if(auxNode == list->start){ // we are at the start of the list?
            list->start = auxNode->next;
        }
        else if(auxNode == list->end){ // wa are at the end of the list? ... previousNode → auxNode → NULL
            previousNode->next = auxNode->next; // ... previousNode → NULL
            list->end = previousNode;
        }
        else{ // wa are at the middle of the list? ... previousNode → auxNode → nextNode ...
            previousNode->next = auxNode->next; // ... previousNode → nextNode ...
        }
    }
    free(auxNode);
    list->quantity--;

    return 1; // 1 person successfully removed
}

// get a person from the list by id
PERSON* contact_list_get_person(CONTACT_LIST* list, int id);

// get a person from the list by position
PERSON* contact_list_get_person_by_position(CONTACT_LIST* list, int position);

// save list and free memory
void contact_list_save_and_free(CONTACT_LIST* list);