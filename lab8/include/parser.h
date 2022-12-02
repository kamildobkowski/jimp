#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED

typedef struct lines {
    int start;
    int end;
    struct lines * next;
} linesNode_t;

typedef struct call {
    char name;
    int ile;
    struct call* next;
} callNode_t;

typedef struct e {
    char * name;
    linesNode_t ** linesHead;
    char * File; // Dupa
    callNode_t ** callHead; //lista wywolan
    struct e *next; //wskaznik na nastepny element
} listNode_t;

void analizatorSkladni(char *inpname); 
void store_add_fun(char *top, int line_num, char* inpname, listNode_t ** list); //
void addListElem(listNode_t** lista, listNode_t* element);
void addLinesElem(linesNode_t** lines, linesNode_t* element);
void store_add_call(char* top, char* name, listNode_t** lista);
void addCallElem(callNode_t** call, char* element);
listNode_t** getListDef();
listNode_t** getListCall();
listNode_t** getListProto();
#endif