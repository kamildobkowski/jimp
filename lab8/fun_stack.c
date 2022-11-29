#include "fun_stack.h"

// zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
int top_of_funstack(void)
{
    return (*functionStack)->parLevel;
}

// odkłada na stos parę (funame, par_level)
void put_on_fun_stack(int par_level, char *funame)
{
    Node e;
    e->name = funame;
    e->parLevel = par_level;
}
char *get_from_fun_stack(void)
{
}