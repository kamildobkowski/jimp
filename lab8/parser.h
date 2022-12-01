#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED

typedef struct lines{
    int start;
    int end;
    struct lines * next;
} *lines_t;

typedef struct e {
    char* name;
    lines_t linie;
    char* File; //
    char *callName; //lista wywolan
    struct e *next; //wskaznik na nastepny element
} list_t;

void analizatorSkladni(char *inpname);
void store_add_def (char *top, int lineNum, char* inpname);
void store_add_proto(char *top, int lineNum, char* inpname);
void store_add_call(char *top, int lineNum, char* inpname);
#endif