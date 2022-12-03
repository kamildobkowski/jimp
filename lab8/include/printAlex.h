#ifndef _PRINT_ALEX_IS_INCLUDED_
#define _PRINT_ALEX_IS_INCLUDED_
#include <stdio.h>

#include "../include/fun_stack.h"
#include "../include/parser.h"

// Funkcja wypisująca wywołania w funkcji
void printInFunctionCall(callNode_t** callInFunction);

// Funkcja wyszukujaca listy wywołań i wypisująca je
void printSomeCall(char* name);

// Funkcja wypisująca lokalizacje z listy
void printFileLocalisation(linesNode_t** linesInFile);

// Funkcja wypisująca selfcalle | definicje | prototypy oraz ich lokalizacje i
// wywołania innych funkcji dla podanej w parametrze nazwy funkcji
void printThreeType(char* name, char* message, listNode_t* temp);

// Funkcja wypisująca wszystkie dane uzyskane z analizatora
void printFiles();

// funkcja pozwalajaca na wyjście wyjście z programu wcześniej czyszcząc dane
void freeExit(FILE* in);
#endif