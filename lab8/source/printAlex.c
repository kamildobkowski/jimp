#include "../include/printAlex.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/fun_stack.h"
#include "../include/parser.h"
#include "../include/storage.h"

void printFiles() {
    printf("Analizator składni\n");
    listFunctions_t tempFunctionList = *getListFun();
    while (tempFunctionList != NULL) {
        char* functionName = tempFunctionList->name;
        printf("Funkcja [%s]:\n", functionName);
        printf("\t");
        printThreeType(functionName, "Prototypy", *getListProto());
        printf("\t");
        printThreeType(functionName, "Definicje", *getListDef());
        printf("\t");
        printThreeType(functionName, "Uzycia   ", *getListCall());
        printf("\t");
        printSomeCall(functionName);
        printf("\n");
        tempFunctionList = tempFunctionList->next;
    }
}

void printThreeType(char* name, char* message, listNode_t* temp) {
    printf("%s:\n", message);
    while (temp != NULL) {
        printf("[%s]", "DUPA");
        if (temp->name == name) {
            printFileLocalisation(temp->linesHead);
            return;
        }
        temp = temp->next;
    }
}

void printSomeCall(char* name) {
    printf("Wywołuje:\n");
    listNode_t* temp = *getListCall();
    while (temp != NULL) {
        if (temp->name == name) {
            printInFunctionCall(temp->callHead);
            return;
        }
        temp = temp->next;
    }
}

void printFileLocalisation(linesNode_t** linesInFile) {
    linesNode_t* temp = *linesInFile;
    while (temp != NULL) {
        printf("plik: [%s] w liniach [%d, %d]\n", temp->fileName, temp->start,
               temp->end);
        temp = temp->next;
    }
}

void printInFunctionCall(callNode_t** callInFunction) {
    callNode_t* temp = *callInFunction;
    while (temp != NULL) {
        printf("plik: [%s] - [%d razy]\n", temp->name, temp->ile);
        temp = temp->next;
    }
}