#include <string.h>
#include "../include/storage.h"

void addListElem(listNode_t** lista, listNode_t* element) {
	if(lista == NULL) {
		*lista = element;
		(*lista)->next = NULL;
	}
	else {
		listNode_t* tmp = *lista;
		while(tmp!=NULL) {
			tmp=tmp->next;
		}
		tmp = element;
		tmp->next=NULL;
	}
}

void addLinesElem(linesNode_t** lines, linesNode_t* element) {
	if(lines==NULL) {
		*lines=element;
		(*lines)->next=NULL;
	}
	else {
		linesNode_t* tmp = lines;
		while(tmp!=NULL) {
			tmp=tmp->next;
		}
		tmp=element;
		tmp->next=NULL;
	}
}

void addCallElem(callNode_t** call, char* element) {
	if(call==NULL) {
		(*call)->name=element;
		(*call)->ile=1;
		(*call)->next=NULL;
	}
	else {
		callNode_t* tmp = call;
		while(tmp!=NULL) {
			if(tmp->name==element) {
				tmp->ile++;
				return;
			}
			tmp=tmp->next;
		}
		tmp->name=element;
		tmp->next=NULL;
 	}
}

int store_add_fun(char *top, int line_num, char* inpname, listNode_t ** list){
	listNode_t * tempFunctionList = *list;
	while (tempFunctionList != NULL){
		if(strcmp(tempFunctionList->name, top)){
			linesNode_t* lines = malloc(sizeof(*lines));
			lines->start = line_num;
			lines->end = line_num;
			lines->fileName = inpname;
			addLinesElem(tempFunctionList->linesHead, lines);
			return 2;
		}
		tempFunctionList = tempFunctionList->next;
	}
	linesNode_t* lines = malloc(sizeof(*lines));
	listNode_t* lista = malloc(sizeof(*lista));
	lines->start=line_num;
	lines->end=line_num;
	lines->fileName = inpname;
	lines->next=NULL;
	lista->name=top;
	//lista->File = inpname;
	lista->linesHead = NULL;
	addLinesElem(lista->linesHead, lines);
	addListElem(getListDef(), lista);
	return 1;
}
//dodaje linie konczaca definicje do listy
void addEndOfDef(listNode_t ** list, char* top, int line_num) {
	listNode_t ** tmp = list;
	while(tmp!=NULL && !strcmp((*tmp)->name,top)) {
		tmp = (*tmp)->next;
	}
	if(tmp==NULL) return;
	linesNode_t ** linesTmp = (*tmp)->linesHead;
	(*linesTmp)->end=line_num;
}

void store_add_call(char* top, char* name, listNode_t** lista) {
	listNode_t **tmp = lista;
	while(tmp!=NULL) {
		if(strcmp((*tmp)->name, name)) {
			addCallElem(tmp, top);
		}
	}
}