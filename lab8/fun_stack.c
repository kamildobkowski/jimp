#include "fun_stack.h"

// zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
int top_of_funstack(void)
{
    return (*functionStack)->parLevel;
}

// odkłada na stos parę (funame, par_level)
void put_on_fun_stack(char *funame, int par_level, int bra_level)
{
    Node e;
    e->name = funame;
    e->parLevel = par_level;
    e->braLevel = bra_level;
    e->next = *functionStack;
    functionStack = &e;
}
char *get_from_fun_stack(void)
{
    Node e = *functionStack;
    *functionStack = (*functionStack)->next;
    return e;
}