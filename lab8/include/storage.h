#ifndef _STORAGE_H_IS_INCLUDED
#define _STORAGE_H_IS_INCLUDED

typedef struct lines {
    char* fileName;
    int start;
    int end;
    struct lines* next;
} linesNode_t;

typedef struct call {
    char* name;
    int ile;
    struct call* next;
} callNode_t;

typedef struct e {
    char* name;
    linesNode_t** linesHead;
    callNode_t** callHead;  // lista wywolan
    struct e* next;         // wskaznik na nastepny element
} listNode_t;

typedef struct fun {
    char* name;
    struct fun* next;  // wskaznik na nastepny element
}* listFunctions_t;

int store_add_fun(char* top, int line_num, char* inpname,
                  listNode_t** list);  //
void addListElem(listNode_t** lista, listNode_t* element);
void addLinesElem(linesNode_t** lines, linesNode_t* element);
void addCallElem(callNode_t** call, char* element);
void store_add_call(char* top, char* name, listNode_t** lista);
void freeLinesList(linesNode_t** head);
void freeCallList(callNode_t** head);
void freeList(listNode_t** list);
void freeFunctionList(listFunctions_t* head);

void store_add_pri(listFunctions_t* printFunctions, char* name);

#endif