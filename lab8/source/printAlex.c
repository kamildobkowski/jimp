#include "../include/printAlex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/fun_stack.h"
#include "../include/parser.h"
#include "../include/storage.h"

void printFiles() {
    printf("Analizator składni\n");
    listFunctions_t tempFunctionList = *getListFun();
    while (tempFunctionList != NULL) {
        char* functionName = tempFunctionList->name;
        printf("Funkcja [%s]:\n", functionName);
        printThreeType(functionName, "Prototypy", *getListProto());
        printThreeType(functionName, "Definicje", *getListDef());
        printThreeType(functionName, "Uzycia   ", *getListCall());
        printSomeCall(functionName);
        printf("\n");
        tempFunctionList = tempFunctionList->next;
    }
}

void printThreeType(char* name, char* message, listNode_t* temp) {
    printf("\t%s:\n", message);
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printFileLocalisation(temp->linesHead);
            return;
        }
        temp = temp->next;
    }
}

void printSomeCall(char* name) {
    printf("\tWywoluje:\n");
    listNode_t* temp = *getListCall();
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printInFunctionCall(temp->callHead);
            return;
        }
        temp = temp->next;
    }
}

void printFileLocalisation(linesNode_t** linesInFile) {
    linesNode_t* temp = *linesInFile;
    while (temp != NULL) {
        printf("\t\tplik: [%s] w liniach [%d, %d]\n", temp->fileName,
               temp->start, temp->end);
        temp = temp->next;
    }
}

void printInFunctionCall(callNode_t** callInFunction) {
    callNode_t* temp = *callInFunction;
    while (temp != NULL) {
        printf("\t\t[%s] - [%d razy]\n", temp->name, temp->ile);
        temp = temp->next;
    }
}

void freeExit(FILE* in) {
    freeList(getListCall());
    freeList(getListProto());
    freeList(getListDef());
    freeFunctionList(getListFun());
    freeElements();
    fclose(in);
    exit(1);
}