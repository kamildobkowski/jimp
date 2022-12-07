#include <stdlib.h>

#include "../include/fun_stack.h"
// Funckje struktury Stosu

Node *funStack;

void initFunctionStack() {
    funStack = malloc(sizeof(*funStack));
    *funStack = NULL;
}

// zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
int top_of_funstack(void) { return (*funStack)->parLevel; }

// odkłada na stos parę (funame, par_level, bra_level)
void put_on_fun_stack(char *funame, int par_level, int bra_level) {
    Node e = initNode(funame, par_level, bra_level);
    e->next = *funStack;
    (*funStack) = e;
}

// Pobiera ze stosu element zarazem go usuwając
char *get_from_fun_stack(void) { return (*funStack)->name; }

void pop_from_fun_stack() {
    Node temp = (*funStack);
    (*funStack) = (*funStack)->next;
    temp->next = NULL;
    free(temp);
}

// Funkcje struktury Node

// Inicjacja elementu stosu
Node initNode(char *funame, int par_level, int bra_level) {
    Node e = malloc(sizeof(*e));
    e->name = funame;
    e->parLevel = par_level;
    e->braLevel = bra_level;
    e->next = NULL;
    return e;
}

// Zwraca Stos funkcji
Node *get_fun_stack() { return funStack; }

void freeElements() {
    Node elm;
    while ((elm = *funStack) != NULL) {
        *funStack = (*funStack)->next;
        free(elm->name);
        free(elm);
    }
    free(funStack);
}