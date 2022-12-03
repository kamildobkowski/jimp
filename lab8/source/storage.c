#include "../include/storage.h"

#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

void addListElem(listNode_t** lista, listNode_t* element) {
    if (lista == NULL) {
        *lista = element;
        (*lista)->next = NULL;
    } else {
        listNode_t* tmp = *lista;
        while (tmp != NULL) {
            tmp = tmp->next;
        }
        tmp = element;
        tmp->next = NULL;
        free(tmp);
    }
}

void addLinesElem(linesNode_t** lines, linesNode_t* element) {
    if (lines == NULL) {
        *lines = element;
        (*lines)->next = NULL;
    } else {
        linesNode_t* tmp = *lines;
        while (tmp != NULL) {
            tmp = tmp->next;
        }
        tmp = element;
        tmp->next = NULL;
        free(tmp);
    }
}

void addCallElem(callNode_t** call, char* element) {
    if (call == NULL) {
        call = malloc(sizeof(*call));
        *call = malloc(sizeof(**call));
        (*call)->name = malloc(sizeof(*(*call)->name) * strlen(element) + 1);
        strcpy((*call)->name, element);
        (*call)->ile = 1;
        (*call)->next = NULL;
    } else {
        callNode_t* tmp = *call;
        while (tmp != NULL) {
            if (tmp->name == element) {
                tmp->ile++;
                return;
            }
            tmp = tmp->next;
        }
        (*call)->name = malloc(sizeof(*(*call)->name) * strlen(element) + 1);
        strcpy((*call)->name, element);
        tmp->next = NULL;
        free(tmp);
    }
}

// Funkcja inicjująca element
listFunctions_t initPriElement(char* name) {
    listFunctions_t element = malloc(sizeof(*element));
    element->name = name;
    return element;
}

// funkcja dodająca element do listy
void store_add_pri(listFunctions_t* printFunctions, char* name) {
    listFunctions_t tempFunctions = *printFunctions;
    while (tempFunctions != NULL) {
        if (strcmp(tempFunctions->name, name) == 0) {
            return;
        }
        tempFunctions = tempFunctions->next;
    }
    tempFunctions = initPriElement(name);
    tempFunctions->next = *printFunctions;
    *printFunctions = tempFunctions;
}

int store_add_fun(char* top, int line_num, char* inpname, listNode_t** list) {
    listNode_t* tempFunctionList = *list;
    while (tempFunctionList != NULL) {
        if (strcmp(tempFunctionList->name, top) == 0) {
            linesNode_t* lines = malloc(sizeof(*lines));
            lines->start = line_num;
            lines->end = line_num;
            lines->fileName =
                malloc(sizeof(*lines->fileName) * strlen(inpname) + 1);
            strcpy(lines->fileName, inpname);
            addLinesElem(tempFunctionList->linesHead, lines);
            return 2;
        }
        tempFunctionList = tempFunctionList->next;
    }
    linesNode_t* lines = malloc(sizeof(*lines));
    listNode_t* lista = malloc(sizeof(*lista));
    lines->start = line_num;
    lines->end = line_num;
    lines->fileName = malloc(sizeof(*lines->fileName) * strlen(inpname) + 1);
    strcpy(lines->fileName, inpname);
    lines->next = NULL;
    lista->name = malloc(sizeof(*lista->name) * strlen(top) + 1);
    strcpy(lista->name, top);
    // lista->File = inpname;
    lista->linesHead = malloc(sizeof(*lista->linesHead));
    *(lista->linesHead) = NULL;
    addLinesElem(lista->linesHead, lines);
    addListElem(getListDef(), lista);
    return 1;
}
// dodaje linie konczaca definicje do listy
void addEndOfDef(listNode_t** list, char* top, int line_num) {
    listNode_t* tmp = *list;
    while (tmp != NULL && !(strcmp(tmp->name, top) == 0)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) return;
    (*tmp->linesHead)->end = line_num;
    // free(tmp);
}

void store_add_call(char* top, char* name, listNode_t** lista) {
    listNode_t* tmp = *lista;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            addCallElem(tmp->callHead, top);
        }
        tmp = tmp->next;
    }
}

void freeLinesList(linesNode_t** head) {
    linesNode_t* tmp;
    while ((tmp = *head) != NULL) {
        *head = (*head)->next;
        free(tmp->fileName);
        free(tmp);
    }
    free(head);
}

void freeCallList(callNode_t** head) {
    callNode_t* tmp;
    while ((tmp = *head) != NULL) {
        *head = (*head)->next;
        free(tmp->name);
        free(tmp);
    }
    free(head);
}

void freeList(listNode_t** head) {
    listNode_t* tmp;
    while ((tmp = *head) != NULL) {
        *head = (*head)->next;
        freeLinesList(tmp->linesHead);
        freeCallList(tmp->callHead);
        free(tmp->name);
        free(tmp);
    }
    free(head);
}

void freeFunctionList(listFunctions_t* head) {
    listFunctions_t tmp;
    while ((tmp = *head) != NULL) {
        *head = (*head)->next;
        free(tmp->name);
        free(tmp);
    }
    free(head);
}