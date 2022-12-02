#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED

typedef struct lines{
    int start;
    int end;
    struct lines * next;
} linesNode;

typedef struct {
    linesNode *head;
    linesNode *tail;
} * lines_t;

typedef struct e {
    char* name;
    lines_t lines_t;
    char* File; //
    char* callName; //lista wywolan
    struct e *next; //wskaznik na nastepny element
} listNode_t;

typedef struct list {
    listNode_t* head;
    listNode_t* tail;
} list_t;




void analizatorSkladni(char *inpname); 
void store_add_def (char *top, int lineNum, char* inpname); //dodaje definicje do listy
void store_add_proto(char *top, int lineNum, char* inpname); //dodaje prototyp do listy
void store_add_call(char *top, int lineNum, char* inpname); //dodaje wywołania do listy
void addListElem();
#endif