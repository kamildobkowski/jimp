#ifndef _STORAGE_H_IS_INCLUDED
#define _STORAGE_H_IS_INCLUDED

// Struktura listy przetrzymująca miejsce występienia CALI innych funkcji
// Jest przechowywana w strukturze przechowującej wystąpienia SELF CALLI
// Stosujemy by móc wypisac plik i linie wystąpienia danej funkcji
typedef struct lines {
    char* fileName;
    int start;
    int end;
    struct lines* next;
} linesNode_t;

// Struktura listy przetrzymująca wywołania
// Jest przechowywana w strukturze przechowującej wystąpienia SELF CALLI
// Stosujemy ją by móc wypisać wywołania wszystkich funkcji które sa wywoływane
// przez tą aktualną
typedef struct call {
    char* name;
    int ile;
    struct call* next;
} callNode_t;

// Struktura listy przetrzymująca nazwe funkcji oraz miejsce wystąpienia
typedef struct e {
    char* name;
    linesNode_t** linesHead;
    callNode_t** callHead;  // lista wywolan
    struct e* next;         // wskaznik na nastepny element
} listNode_t;

// Struktura listy przetrzymująca wyłącznie nazwy funkcji
// Lista nazw funkcji jest stworzona dla ułatwienia wypisań funkcji
// Wykorzystujemy ją by wypisac na raz dane tylko dla funkcji o konkretnej
// nazwie
typedef struct fun {
    char* name;
    struct fun* next;  // wskaznik na nastepny element
}* listFunctions_t;

// Funkcja dodająca calla innych funkcji w funkcji do listy
void addCallElem(callNode_t** call, char* element);

// Funkcja dodająca do listy przechowującej wywołania funkcji
void store_add_call(char* top, char* name, listNode_t** lista);

// Funkcja dodaje elementy listy przechowującej
// SelfCalle | Prototypy | Wywołania
void addListElem(listNode_t** lista, listNode_t* element);

// Funkcja dodająca linie wystąpień do ich listy
void addLinesElem(linesNode_t** lines, linesNode_t* element);

linesNode_t* initLinesNode(char* inpname, int line_num);
listNode_t* initListNode(char* top, char* inpname, int line_num);

// Funkcja dodająca do jednej z list element inicjując elementy listy calli oraz
// listy lini
int store_add_fun(char* top, int line_num, char* inpname, listNode_t** list);

// Funkcja dodająca do listy nazw funkcji wypisywanych element
void store_add_pri(listFunctions_t* printFunctions, char* name);

// Funkcje czysczące listy z pamięci
void freeLinesList(linesNode_t** head);
void freeCallList(callNode_t** head);
void freeList(listNode_t** list);
void freeFunctionList(listFunctions_t* head);

#endif