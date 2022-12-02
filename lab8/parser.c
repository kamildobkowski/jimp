#include <stdio.h>
#include <stdlib.h>	   // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"	   // analizator leksykalny
#include "fun_stack.h" // stos funkcji
#include "parser.h"

#define MAXINDENTLENGHT 256 // maks długość identyfikatora

list_t* listDef;
list_t* listProto;
list_t* listCall;

void analizatorSkladni (char *inpname)
{                               // przetwarza plik inpname

	FILE *in = fopen(inpname, "r");

	int nbra = 0; // bilans nawiasów klamrowych {}
	int npar = 0; // bilans nawiasów zwykłych ()

	alex_init4file(in); // ustaw analizator leksykalny, aby czytał in

	lexem_t lex;

  lex = alex_nextLexem ();      // pobierz następny leksem
  while (lex != EOFILE) {
	switch (lex) {
	case IDENT:{
		char *iname = alex_ident ();   // zapamiętaj identyfikator i patrz co dalej
		lexem_t nlex = alex_nextLexem ();
		if (nlex == OPEPAR) {   // nawias otwierający - to zapewne funkcja
		  npar++;
		  put_on_fun_stack (iname, npar, nbra);	// odłóż na stos funkcje i bilans nawiasów
												// stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
												// f1( 5, f2( a ), f3( b ) )
		}
		else {                  // nie nawias, czyli nie funkcja
		  lex = nlex;
		  continue;
		}
	  }
	  break;
	case OPEPAR:
	  npar++;
	  break;
	case CLOPAR:{              // zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
		if (top_of_funstack () == npar) {       // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
												// jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
												// za identyfikatorem znajdującym się na wierzchołku stosu
		  lexem_t nlex = alex_nextLexem ();     // bierzemy nast leksem
		  if (nlex == OPEBRA)   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
			store_add_def (get_from_fun_stack (), alex_getLN (), inpname);
		  else if (nbra == 0)   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
			store_add_proto (get_from_fun_stack (), alex_getLN (), inpname);
		  else                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
			store_add_call (get_from_fun_stack (), alex_getLN (), inpname);
		}
		npar--;
	  }
	  break;
	case OPEBRA:
	  nbra++;
	  break;
	case CLOBRA:{
		nbra--;
		
	}
		break;
	case ERROR:{
		fprintf (stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
				 "W pliku %s (linia %d) są błędy składni.\n"
				 "Kończę!\n\n", inpname, alex_getNL ());
		exit (1);               // to nie jest najlepsze, ale jest proste ;-)
	  }
	  break;
	default:
	  break;
	}
	lex = alex_nextLexem ();
  }
}

void addListElem(list_t* lista, listNode_t* element) {
	if(lista->head == NULL) {
		lista->head=element;
		lista->head->next=NULL;
		lista->tail=lista->head;
	}
	else {
		list_t* tmp = lista->tail;
		lista->tail->next=element;
		lista->tail=lista->tail->next;
	}
}

void addLinesElem() {

}

void store_add_def(char *top, int line_num, char* inpname)
{
	listNode_t* newElem = malloc(sizeof(listNode_t));
	linesNode* newLinesElem = malloc(sizeof(linesNode));
	newLinesElem->start = line_num;
	newLinesElem->end = line_num;
	newElem->name=top;
	newElem->File=inpname;
	newElem->
	listNode_t* tmp = listDef->head;
	while(tmp!=NULL) {
		if(tmp->name == top) {
			
			return;
		}
		tmp=tmp->next;
	}
	tmp=newElem;
	tmp->next = NULL;
	listDef->tail = tmp;

	
}
void store_add_proto(char *top, int line_num, char* inpname) {

}
void store_add_call(char *top, int line_num, char* inpname) {
	
}


/*FILO

typdef struct element {
	int value;
	struct element * next;
} * node;

node head = NULL;

addElement(node newElement){
	if
}


[] [] */