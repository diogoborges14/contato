#ifndef _DYNAMIC_LIST_H_
#define _DYNAMIC_LIST_H_

/* datatypes for dynamic list */
struct user{
    int         id;
    char        nome[100];
    char        telefone[15];
    char        email[100];
    struct user *next; // Point to next user
}typedef USER;

#endif
