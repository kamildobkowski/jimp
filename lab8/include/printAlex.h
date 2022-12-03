#ifndef _PRINT_ALEX_IS_INCLUDED_
#define _PRINT_ALEX_IS_INCLUDED_
#include "../include/fun_stack.h"
#include "../include/parser.h"

void printInFunctionCall(callNode_t** callInFunction);
void printSomeCall(char* name);
void printFileLocalisation(linesNode_t** linesInFile);
void printThreeType(char* name, char* message, listNode_t* temp);
void printFiles();

#endif