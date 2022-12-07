#include "../include/storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

// Funkcja inicjująca element
listFunctions_t initPriElement(char* name) {
    listFunctions_t element = malloc(sizeof(*element));
    element->name = malloc(sizeof(*element->name) * strlen(name) + 1);
    strcpy(element->name, name);
    element->callHead = malloc(sizeof(*element->callHead));
    *(element->callHead) = NULL;
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
    tempFunctions->next = NULL;
    if (*printFunctions == NULL) {
        *printFunctions = tempFunctions;
    } else {
        listFunctions_t temp = *printFunctions;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = tempFunctions;
    }
}

void addListElem(listNode_t** lista, listNode_t* element) {
    element->next = NULL;
    if (*lista == NULL) {
        *lista = element;
    } else {
        listNode_t* temp = *lista;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = element;
    }
}

void addLinesElem(linesNode_t** lines, linesNode_t* element) {
    element->next = NULL;
    if (*lines == NULL) {
        *lines = element;
    } else {
        linesNode_t* temp = *lines;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = element;
    }
}

linesNode_t* initLinesNode(char* inpname, int line_num) {
    linesNode_t* lines = malloc(sizeof(*lines));
    lines->start = line_num;
    lines->end = line_num;
    lines->fileName = malloc(sizeof(*lines->fileName) * strlen(inpname) + 1);
    strcpy(lines->fileName, inpname);
    lines->next = NULL;
    return lines;
}

listNode_t* initListNode(char* top, char* inpname, int line_num) {
    listNode_t* lista = malloc(sizeof(*lista));
    lista->name = malloc(sizeof(*lista->name) * strlen(top) + 1);
    strcpy(lista->name, top);
    lista->linesHead = malloc(sizeof(*lista->linesHead));
    *(lista->linesHead) = NULL;
    addLinesElem(lista->linesHead, initLinesNode(inpname, line_num));
    return lista;
}

int store_add_fun(char* top, int line_num, char* inpname, listNode_t** list) {
    listNode_t* tempFunctionList = *list;
    while (tempFunctionList != NULL) {
        if (strcmp(tempFunctionList->name, top) == 0) {
            addLinesElem(tempFunctionList->linesHead,
                         initLinesNode(inpname, line_num));
            return 2;
        }
        tempFunctionList = tempFunctionList->next;
    }
    listNode_t* lista = initListNode(top, inpname, line_num);
    addListElem(list, lista);
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
}

callNode_t* initCallNode(char* name) {
    callNode_t* tmp = malloc(sizeof(*tmp));
    tmp->name = malloc(sizeof(tmp->name) * strlen(name) + 1);
    strcpy(tmp->name, name);
    tmp->next = NULL;
    return tmp;
}

void addCallElem(callNode_t** call, char* name) {
    callNode_t* tmp = *call;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            tmp->ile++;
            return;
        }
        tmp = tmp->next;
    }
    tmp = initCallNode(name);
    tmp->ile = 1;
    tmp->next = *call;
    *call = tmp;
}

void store_add_call(char* top, char* name, listFunctions_t* lista) {
    listFunctions_t tmp = *lista;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            addCallElem(tmp->callHead, top);
            return;
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
        freeCallList(tmp->callHead);
        free(tmp);
    }
    free(head);
}