#include "../include/printAlex.h"

#include <stdio.h>

#include "../include/parser.h"

void printFile(char *inputName) {
    printf("Analizator składni dla pliku: [%s]\n", inputName);
    listNode_t *tempList = *getListProto();
    while (tempList != NULL) {
        printf("Funkcja [%s]\n", tempList->name);
        printPrototype(tempList);
        tempList = tempList->next;
    }
}

void printPrototype(listNode_t *function) {
    printf("Prototypy:\n");
    while (1) {
        /* code */
    }
}

void printDefinition(listNode_t *function) { printf("Definicje:\n"); }
void printSelfCall(listNode_t *function) { printf("Użycia:\n"); }

void printSomeCall(listNode_t *function) { printf("Wywołuje:\n"); }
