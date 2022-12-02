#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED

typedef struct lines
{
    int start;
    int end;
    struct lines *next;
} *linesNode;

typedef struct
{
    struct linesNode head;
    struct linesNode tail;
} *lines_t;

typedef struct e
{
    char *name;
    lines_t lines_t;
    char *File;     //
    char *callName; // lista wywolan
    struct e *next; // wskaznik na nastepny element
} listElem_t;

typedef struct list
{
    struct listElem_t *head;
    struct listElem_t *tail;
} list_t;

void analizatorSkladni(char *inpname);
void store_add_def(char *top, int lineNum, char *inpname);   // dodaje definicje do listy
void store_add_proto(char *top, int lineNum, char *inpname); // dodaje prototyp do listy
void store_add_call(char *top, int lineNum, char *inpname);  // dodaje wywołania do listy
void addListElem();
#endif