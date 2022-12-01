#include <stdio.h>
#include <stdlib.h>

#include "fun_stack.h"
#include "alex.h"
#include "parser.h"

int main(int argc, char **argv)
{
    int i = 0;
    // Zdefiniowanie rozmiaru dla struktury functionStack (fun_stack.h)
    // Sprawdzenie działania fun_stack.c

    // sprawdzenie działania alex.c

    // Sprawdzenie działania stworzonej przez Ciebie struktury i funkcji do niej
    // sprawdzenie działania parser.c

    // Wczytanie plików z argv 
    for(i=1; i<argc; i++) {
        analizatorSkladni(argv[i]);
    }
}
