#include "../include/parser.h"

#include <stdio.h>
#include <stdlib.h>  // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include <string.h>

#include "../include/alex.h"       // analizator leksykalny
#include "../include/fun_stack.h"  // stos funkcji
#include "../include/printAlex.h"
#include "../include/storage.h"

#define MAXINDENTLENGHT 256  // maks długość identyfikatora

listNode_t **listDef;
listNode_t **listProto;
listNode_t **listCall;
listFunctions_t *printFunctions;
int flag = 0;

void analizatorSkladni(char *inpname) {  // przetwarza plik inpname
    FILE *in = fopen(inpname, "r");
    if (in == NULL) {
        fprintf(stderr, "Plik o scierzce: [%s] nie istnieje :(\n", inpname);
        return;
    }

    int nbra = 0;        // bilans nawiasów klamrowych {}
    int npar = 0;        // bilans nawiasów zwykłych ()
    alex_init4file(in);  // ustaw analizator leksykalny, aby czytał in

    lexem_t lex;

    lex = alex_nextLexem();  // pobierz następny leksem

    while (lex != EOFILE) {
        switch (lex) {
            case IDENT: {
                char *iname =
                    alex_ident();  // zapamiętaj identyfikator i patrz co dalej
                lexem_t nlex = alex_nextLexem();
                if (nlex ==
                    OPEPAR) {  // nawias otwierający - to zapewne funkcja
                    npar++;
                    put_on_fun_stack(iname, npar, nbra);
                    store_add_pri(printFunctions, get_from_fun_stack());
                    // printf("[%s %d]\n", iname, npar);
                    flag++;
                    //  odłóż na stos funkcje i bilans
                    //  nawiasów stos f. jest niezbędny,
                    //  aby poprawnie obsłużyć sytuacje
                    //  typu f1( 5, f2( a ), f3( b ) )
                } else {  // nie nawias, czyli nie funkcja
                    lex = nlex;
                    continue;
                }

            } break;
            case OPEPAR:
                npar++;
                break;
            case CLOPAR: {  // zamykający nawias - to może być koniec prototypu,
                            // nagłówka albo wywołania
                // Jeśli nie wykryjemy funkcji to kod się nie wykonuje
                // Zapobiega używaniu bezsensownych nawiasów ()
                if (flag == 0) {
                    npar--;
                    break;
                }
                flag--;
                if (*get_fun_stack() == NULL) {
                    npar--;
                    break;
                }

                // printf("%s, %d, %d, n: %d, f: %s\n", alex_ident(), npar,
                //        alex_getLN(), top_of_funstack(),
                //        get_from_fun_stack());
                if (top_of_funstack() == npar) {
                    // sprawdzamy, czy liczba nawiasów bilansuje się z
                    // wierzchołkiem stosu funkcji jeśli tak, to
                    // właśnie wczytany nawias jest domknięciem nawiasu
                    // otwartego za identyfikatorem znajdującym się na
                    // wierzchołku stosu
                    // ^ Nie powoduje blędów utraty pamięci
                    lexem_t nlex = alex_nextLexem();  // bierzemy nast leksem

                    if (nlex == ERROR) {
                        fprintf(stderr,
                                "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                                "W pliku %s (linia %d) są błędy składni.\n"
                                "Kończę!\n\n",
                                inpname, alex_getLN());
                        // free
                        freeExit(in);
                        return;
                    }
                    // nast. leksem to klamra a więc mamy do czynienia z def.
                    // funkcji
                    if (nlex == OPEBRA) {
                        store_add_fun(get_from_fun_stack(), alex_getLN(),
                                      inpname, listDef);

                        // if (store_add_fun(get_from_fun_stack(),
                        // alex_getLN(),
                        //                   inpname, listDef) == 2) {
                        //     // ^ Poowoduje blędy utraty pamięci
                        //     printf("Może być tylko jedna definicja
                        //     funkcji");
                        //     // return 1;
                        //     freeExit(in);
                        //     return;
                        // }
                    } else if (nbra == 0) {
                        // nast. leksem to nie { i jesteśmy poza
                        // blokami - to musi być prototyp
                        store_add_fun(get_from_fun_stack(), alex_getLN(),
                                      inpname, listProto);
                        // if (store_add_fun(get_from_fun_stack(),
                        // alex_getLN(),
                        //                   inpname, listProto) == 2) {
                        //     printf("Może być tylko jedna definicja
                        //     prototypu");
                        //     // return 1;
                        //     freeExit(in);
                        //     return;
                        // }
                        pop_from_fun_stack();
                    } else {  // nast. leksem to nie { i jesteśmy wewnątrz
                              // bloku
                              // - to zapewne wywołanie

                        store_add_fun(get_from_fun_stack(), alex_getLN(),
                                      inpname, listCall);
                        // printMainStack();
                        // printf("\n");
                        Node tmpStack = *get_fun_stack();
                        tmpStack = tmpStack->next;
                        while (tmpStack != NULL) {
                            store_add_call(get_from_fun_stack(), tmpStack->name,
                                           printFunctions);
                            tmpStack = tmpStack->next;
                        }
                        pop_from_fun_stack();
                    }
                    if (nlex == CLOPAR) {
                        lex = nlex;
                        npar--;
                        continue;
                    }
                    if (nlex == CLOBRA) {
                        lex = nlex;
                        npar--;
                        continue;
                    }
                    if (nlex == OPEBRA) {
                        nbra++;
                    }

                    if (nlex == OPEPAR) {
                        npar++;
                    }
                }
                npar--;
            } break;
            case OPEBRA:
                nbra++;
                break;
            case CLOBRA: {
                nbra--;

                // Printer testowy
                // if (*get_fun_stack() != NULL)
                //     printf(
                //         "Plik: %s [Linia: %d, Nawiasy: %d, Braket: %d, Id: "
                //         "%s, Lex: %d]\n",
                //         inpname, alex_getLN(), npar, nbra,
                //         get_from_fun_stack(), lex);

                if (*get_fun_stack() == NULL) break;
                if ((*get_fun_stack())->braLevel == nbra) {
                    addEndOfDef(listDef, get_from_fun_stack(), alex_getLN());
                    pop_from_fun_stack();
                }
                break;
            }
            case ERROR: {
                fprintf(stderr,
                        "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                        "W pliku %s (linia %d) są błędy składni.\n"
                        "Kończę!\n\n",
                        inpname, alex_getLN());
                // free
                freeExit(in);
                return;
            } break;
            default:
                break;
        }
        lex = alex_nextLexem();
    }
    fclose(in);
}

// zwraca liste definicji
listNode_t **getListDef() { return listDef; }
// zwraca liste wywolan
listNode_t **getListCall() { return listCall; }
// zwrata liste prototypow
listNode_t **getListProto() { return listProto; }
// zwrata liste funkcji
listFunctions_t *getListFun() { return printFunctions; }

void initAllStorage() {
    listDef = malloc(sizeof(*listDef));
    *listDef = NULL;
    listProto = malloc(sizeof(*listProto));
    *listProto = NULL;
    listCall = malloc(sizeof(*listCall));
    *listCall = NULL;
    printFunctions = malloc(sizeof(*printFunctions));
    *printFunctions = NULL;
}