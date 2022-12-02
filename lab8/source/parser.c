#include <stdio.h>
#include <stdlib.h>	   // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "../include/alex.h"	   // analizator leksykalny
#include "../include/fun_stack.h" // stos funkcji
#include "../include/parser.h"

#define MAXINDENTLENGHT 256 // maks długość identyfikatora

listNode_t ** listDef;
listNode_t ** listProto;
listNode_t ** listCall;

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
			store_add_fun (get_from_fun_stack (), alex_getLN (), inpname, listDef);
		  else if (nbra == 0){ // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
			store_add_fun (get_from_fun_stack (), alex_getLN (), inpname, listProto);
		  }
		  else{ // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
			store_add_fun (get_from_fun_stack (), alex_getLN (), inpname, listCall);
		  }
		}
		npar--;
	  }
	  break;
	case OPEBRA:
	  nbra++;
	  break;
	case CLOBRA:{
		//TU TRZEBA JESZCZE COŚ ZROBIĆ
		// KONIEC DEFINICJI
		nbra--;
		break;
		
	}
	case ERROR:{
		fprintf (stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
				 "W pliku %s (linia %d) są błędy składni.\n"
				 "Kończę!\n\n", inpname, alex_getNL ());
		//free
		return;
	  }
	  break;
	default:
	  break;
	}
	lex = alex_nextLexem ();
  }
}

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


void store_add_fun(char *top, int line_num, char* inpname, listNode_t ** list){
	linesNode_t* lines = malloc(sizeof(*lines));
	listNode_t* lista = malloc(sizeof(*lista));
	lines->start=line_num;
	lines->end=line_num;
	lines->next=NULL;
	lista->name=top;
	lista->File = inpname;
	lista->linesHead = NULL;
	addLinesElem(lista->linesHead, lines);
	addListElem(listDef, lista);
}