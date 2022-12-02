#include "fun_stack.h"
#include <stdlib.h>

// Funckje struktury

// zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
int top_of_funstack(void)
{
    return (*functionStack)->parLevel;
}

// odkłada na stos parę (funame, par_level, bra_level)
void put_on_fun_stack(char *funame, int par_level, int bra_level)
{
    Node e = initNode(funame, par_level, bra_level);
    e->next = *functionStack;
    functionStack = &e;
}

// Pobiera ze stosu element zarazem go usuwając
char *get_from_fun_stack(void)
{
    Node e = *functionStack;
    *functionStack = (*functionStack)->next;
    return e;
}

// Funkcje struktury Node

// Inicjacja elementu stosu
Node initNode(char *funame, int par_level, int bra_level)
{
    Node e;
    e->name = funame;
    e->parLevel = par_level;
    e->braLevel = bra_level;
    e->next = NULL;
    return e;
}