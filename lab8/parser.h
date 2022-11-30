#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED

typedef struct e {
    char* name;
    int protLine;
    char* protFile;
    int defLine;
    char* defFile;
    struct e *call;
    struct e *next;
} list_t;

void analizatorSkladni(char *inpname);
void store_add_def (char *top, int lineNum, char* inpname);
void store_add_proto(char *top, int lineNum, char* inpname);
void store_add_call(char *top, int lineNum, char* inpname);
#endif