#include "../include/fun_stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Funckje struktury Stosu

Node *funStack;

void initFunctionStack() {
    funStack = malloc(sizeof(*funStack));
    *funStack = NULL;
}

// odkłada na stos parę (funame, par_level, bra_level)
void put_on_fun_stack(char *funame, int par_level, int bra_level) {
    Node e = initNode(funame, par_level, bra_level);
    e->next = *funStack;
    (*funStack) = e;
}

// Pobiera ze stosu element zarazem go usuwając
char *get_from_fun_stack(void) {
    if (funStack == NULL) {
        return "";
    } else {
        return (*funStack)->name;
    }
}

// zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
int top_of_funstack(void) {
    if (funStack == NULL) {
        return -1;
    } else {
        return (*funStack)->parLevel;
    }
}

void pop_from_fun_stack() {
    Node temp = (*funStack);
    (*funStack) = (*funStack)->next;
    temp->next = NULL;
    free(temp);
}

// Funkcje struktury Node

// Inicjacja elementu stosu
Node initNode(char *funame, int par_level, int bra_level) {
    Node e = (Node)malloc(sizeof(struct eStack));
    if (e == NULL) {
        printf("Malloc filed [fun_stac.c on initNode()]\n");
        exit(1);
    }
    e->name = malloc(sizeof(*e->name) * strlen(funame) + 1);
    strcpy(e->name, funame);
    e->parLevel = par_level;
    e->braLevel = bra_level;
    e->next = NULL;
    return e;
}

// Zwraca Stos funkcji
Node *get_fun_stack() { return funStack; }

void freeElements() {
    Node temp;
    while ((temp = *funStack) != NULL) {
        *funStack = (*funStack)->next;
        // free(temp->name);
        free(temp);
    }
    free(funStack);
}