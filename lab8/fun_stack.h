#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

typedef struct e
{
    char *name;
    int parLevel;
    int braLevel;
    struct e *next;

} *Node;

Node *functionStack;

int top_of_funstack(void);                          // zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
void put_on_fun_stack(char *funame, int par_level, int bra_level); // odkłada na stos parę (funame,par_level)
char *get_from_fun_stack(void);                     // usuwa z wierzchołka parę (funame,par_level), zwraca zdjętą funame

#endif
