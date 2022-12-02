#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

// Struktura przetrzymująca element stosu
typedef struct e
{
    // Nazwa funkcji
    char *name;
    // Zagłębienie nawiasowe
    int parLevel;
    // Zagłębienie klamerkoweą
    int braLevel;
    // Wskaźnik na następny element
    struct e *next;
} *Node;

Node *funStack;

// Funkcje dotyczące struktury Node

// Inicjacja elementu stosu
Node initNode(char *name, int parLevel, int braLevel);

// Funkcje dotyczące strukty Stosu

Node *initFunctionStac();
int top_of_funstack(void);                                         // zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
void put_on_fun_stack(char *funame, int par_level, int bra_level); // odkłada na stos parę (funame,par_level)
Node get_from_fun_stack(void);                                     // usuwa z wierzchołka parę (funame,par_level), zwraca zdjętą funame

#endif
