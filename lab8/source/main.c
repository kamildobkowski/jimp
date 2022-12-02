#include <stdio.h>
#include <stdlib.h>

#include "../include/alex.h"
#include "../include/fun_stack.h"
#include "../include/parser.h"
#include "../include/printAlex.h"
#include "../include/storage.h"

int main(int argc, char **argv) {
    int i = 0;
    // Sprawdzenie działania fun_stack.c

    // sprawdzenie działania alex.c

    // Sprawdzenie działania stworzonej przez Ciebie struktury i funkcji do niej
    // sprawdzenie działania parser.c

    // Wczytanie plików z argv
    for (i = 1; i < argc; i++) {
        analizatorSkladni(argv[i]);
    }
    freeList(getListDef());
    freeList(getListCall());
    freeList(getListProto());
}
