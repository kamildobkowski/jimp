#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

// Struktura przetrzymująca element stosu
typedef struct eStack {
    // Nazwa funkcji
    char *name;
    // Zagłębienie nawiasowe
    int parLevel;
    // Zagłębienie klamerkowe
    int braLevel;
    // Wskaźnik na następny element
    struct eStack *next;
} * Node;

// Funkcje dotyczące struktury Node

// Inicjacja elementu stosu
Node initNode(char *name, int parLevel, int braLevel);

// Funkcje dotyczące strukty Stosu

void initFunctionStack();
void freeElements();
int top_of_funstack(void);  // zwraca par_level - "zagłębienie nawiasowe"
                            // przechowywane na szczycie
void put_on_fun_stack(
    char *funame, int par_level,
    int bra_level);  // odkłada na stos parę (funame,par_level)
char *get_from_fun_stack(
    void);  // usuwa z wierzchołka parę (funame,par_level), zwraca zdjętą funame
Node *get_fun_stack(void);
void pop_from_fun_stack();
#endif