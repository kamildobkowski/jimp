#ifndef _PARSER_H_IS_INCLUDED
#define _PARSER_H_IS_INCLUDED
#include "../include/storage.h"

void analizatorSkladni(char* inpname);
listNode_t** getListDef();
listNode_t** getListCall();
listNode_t** getListProto();
#endif